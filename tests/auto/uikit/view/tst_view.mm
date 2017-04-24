/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <UIKit/UIKit.h>

#include <QtTest/QtTest>
#include <QtQml/QtQml>
#include <QtUniUIKitControls/QtUniUIKitControls>

#include "../../shared/util.h"

#define LOAD_QML_FILE_APP1 \
    QSharedPointer<QUniUIKitWindow> window = loadQml("app1.qml").dynamicCast<QUniUIKitWindow>(); \
    QVERIFY(window); \
    QUniUIKitViewController *viewController = qvariant_cast<QUniUIKitViewController *>(window->property("rootViewController")); \
    QUniUIKitView *rootView = qvariant_cast<QUniUIKitView *>(window->property("rootView")); \
    QUniUIKitView *contentView = qvariant_cast<QUniUIKitView *>(window->property("contentView")); \
    QUniUIKitView *childView = qvariant_cast<QUniUIKitView *>(window->property("childView")); \
    QUniUIKitView *childView2 = qvariant_cast<QUniUIKitView *>(window->property("childView2")); \
    QUniUIKitView *orphanView = qvariant_cast<QUniUIKitView *>(window->property("orphanView")); \
    QVERIFY(viewController); \
    QVERIFY(rootView); \
    QVERIFY(contentView); \
    QVERIFY(childView); \
    QVERIFY(childView2); \
    QVERIFY(orphanView);

class tst_view : public QObject
{
    Q_OBJECT

private slots:
    void hierarchyCheck();
    void geometery();
    void setGeometery();
    void intrinsicSize();
    void setIntrinsicSize();
    void setGeometryWithNaN();
    void reparentChildViews();
    void reparentRootViews();
    void toggleVisibility();
    void setBackgroundColor();
};

void tst_view::hierarchyCheck()
{
    LOAD_QML_FILE_APP1

    // Check that the hierarchy specified in QML matches
    // the hierarchy reported from the platform controls
    QCOMPARE(viewController->view(), rootView);
    QCOMPARE(contentView->parentView(), rootView);
    QCOMPARE(childView->parentView(), contentView);

    // Check that the hierarchy of the native UIKit controls matches
    // the hierarchy of the platform controls
    QCOMPARE(childView->uiViewHandle().superview, contentView->uiViewHandle());
    QCOMPARE(contentView->uiViewHandle().superview, rootView->uiViewHandle());
    QCOMPARE(viewController->uiViewControllerHandle().view, rootView->uiViewHandle());
}

void tst_view::geometery()
{
    LOAD_QML_FILE_APP1

    // Check that the views has the geometry specified in the QML file
    QCOMPARE(rootView->geometry(), QRectF::fromCGRect(window->uiWindowHandle().frame));

    QCOMPARE(contentView->geometry().x(), 0.);
    QCOMPARE(contentView->geometry().y(), 20.);
    QCOMPARE(contentView->geometry().size(), rootView->geometry().size());
    QCOMPARE(contentView->geometry(), QRectF::fromCGRect(contentView->uiViewHandle().frame));

    QCOMPARE(childView->geometry(), QRectF());
    QCOMPARE(childView2->geometry(), QRectF(0, 0, contentView->width(), 0));
}

void tst_view::setGeometery()
{
    LOAD_QML_FILE_APP1

    QRectF newGeometry(100, 100, 200, 200);

    rootView->setGeometry(newGeometry);
    childView->setGeometry(newGeometry);
    QCOMPARE(rootView->geometry(), newGeometry);
    QCOMPARE(childView->geometry(), newGeometry);

    // contentView has bindings to rootView, so it should update its geometry as well
    QCOMPARE(contentView->geometry().size(), newGeometry.size());
}

void tst_view::intrinsicSize()
{
    LOAD_QML_FILE_APP1

    // Check that the views has the implicit size as (un)specified in the QML file
    QCOMPARE(childView->intrinsicSize(), QSizeF(100, 100));
    QCOMPARE(childView2->intrinsicSize(), QSizeF(contentView->width(), 0));
}

void tst_view::setIntrinsicSize()
{
    LOAD_QML_FILE_APP1

    QSizeF newSize(50, 50);

    childView->setIntrinsicSize(newSize);
    childView2->setIntrinsicSize(newSize);

    QCOMPARE(childView->intrinsicSize(), newSize);
    QCOMPARE(childView2->intrinsicSize(), newSize);
    QCOMPARE(childView2->width(), newSize.width());
}

void tst_view::setGeometryWithNaN()
{
    LOAD_QML_FILE_APP1

    QRectF geometery = childView->geometry();

    // Check that we don't crash in UIKit just because we try to set geometry
    // with NaN, as this can easily happen when using bindings (e.g if binding
    // width to parent.width, and then parent is set to null).
    childView->setX(std::numeric_limits<double>::quiet_NaN());
    childView->setWidth(std::numeric_limits<double>::quiet_NaN());
    QCOMPARE(childView->geometry(), geometery);

    childView->setX(50);
    childView->setWidth(200);
    QCOMPARE(childView->geometry(), QRectF(50, geometery.y(), 200, geometery.height()));
}

void tst_view::reparentChildViews()
{
    LOAD_QML_FILE_APP1

    // Check that initial configuration is as specified in the QML file
    QVERIFY(orphanView->geometry().isEmpty());
    QCOMPARE(orphanView->parent(), window->rootViewController());
    QCOMPARE(orphanView->uiViewHandle().superview, nullptr);

    // Reparent orphanView in, and check that geometry bindings take effect
    orphanView->setParent(contentView);
    QCOMPARE(orphanView->parent(), contentView);
    QCOMPARE(orphanView->uiViewHandle().superview, contentView->uiViewHandle());
    QCOMPARE(orphanView->geometry().size(), contentView->geometry().size());

    // Reparent orphanView out, and check that it ends up without a superview
    orphanView->setParent(window->rootViewController());
    QCOMPARE(orphanView->parent(), window->rootViewController());
    QCOMPARE(orphanView->uiViewHandle().superview, nullptr);
    QVERIFY(orphanView->geometry().isEmpty());
}

void tst_view::reparentRootViews()
{
}

void tst_view::toggleVisibility()
{
}

void tst_view::setBackgroundColor()
{
}


QTEST_MAIN(tst_view)

#include "tst_view.moc"
