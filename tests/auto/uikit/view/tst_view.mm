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

class tst_view : public QObject
{
    Q_OBJECT

private slots:
    void hierarchyCheck();
    void geometery();
    void setGeometery();
    void implicitSize();
    void setImplicitSize();
    void setGeometryWithNaN();
    void reparentChildViews();
    void reparentRootViews();
    void toggleVisibility();
    void setBackgroundColor();
};

void tst_view::hierarchyCheck()
{
    QSharedPointer<QUniUIKitWindow> window = loadQml("app1.qml").dynamicCast<QUniUIKitWindow>();
    QVERIFY(window);

    // Ensure that all properties are set
    QUniUIKitViewController *viewController = qvariant_cast<QUniUIKitViewController *>(window->property("rootViewController"));
    QUniUIKitView *rootView = qvariant_cast<QUniUIKitView *>(window->property("rootView"));
    QUniUIKitView *contentView = qvariant_cast<QUniUIKitView *>(window->property("contentView"));
    QUniUIKitView *childView = qvariant_cast<QUniUIKitView *>(window->property("childView"));
    QVERIFY(viewController);
    QVERIFY(rootView);
    QVERIFY(contentView);
    QVERIFY(childView);

    // Check that the hierarchy that was specified in QML matches
    // the hierarchy that is reported from the platform controls
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
    QSharedPointer<QUniUIKitWindow> window = loadQml("app1.qml").dynamicCast<QUniUIKitWindow>();
    QVERIFY(window);
    QUniUIKitView *rootView = qvariant_cast<QUniUIKitView *>(window->property("rootView"));
    QUniUIKitView *contentView = qvariant_cast<QUniUIKitView *>(window->property("contentView"));
    QUniUIKitView *childView = qvariant_cast<QUniUIKitView *>(window->property("childView"));

    // Check that the views has the geometry we expect
    QCOMPARE(rootView->geometry(), QRectF::fromCGRect(window->uiWindowHandle().frame));

    QCOMPARE(contentView->geometry().x(), 0.);
    QCOMPARE(contentView->geometry().y(), 20.);
    QCOMPARE(contentView->geometry().size(), rootView->geometry().size());
    QCOMPARE(contentView->geometry(), QRectF::fromCGRect(contentView->uiViewHandle().frame));

    QCOMPARE(childView->geometry(), QRectF(0, 0, childView->implicitWidth(), childView->implicitHeight()));
}

void tst_view::setGeometery()
{
    QSharedPointer<QUniUIKitWindow> window = loadQml("app1.qml").dynamicCast<QUniUIKitWindow>();
    QVERIFY(window);
    QUniUIKitView *rootView = qvariant_cast<QUniUIKitView *>(window->property("rootView"));
    QUniUIKitView *contentView = qvariant_cast<QUniUIKitView *>(window->property("contentView"));
    QUniUIKitView *childView = qvariant_cast<QUniUIKitView *>(window->property("childView"));
    QRectF newGeometry(100, 100, 200, 200);

    rootView->setGeometry(newGeometry);
    childView->setGeometry(newGeometry);
    QCOMPARE(rootView->geometry(), newGeometry);
    QCOMPARE(childView->geometry(), newGeometry);

    // contentView has bindings to rootView, so it should update its geometry as well
    QCOMPARE(contentView->geometry().size(), newGeometry.size());
}

void tst_view::implicitSize()
{
}

void tst_view::setImplicitSize()
{
}

void tst_view::setGeometryWithNaN()
{
}

void tst_view::reparentChildViews()
{
    QSharedPointer<QUniUIKitWindow> window = loadQml("app1.qml").dynamicCast<QUniUIKitWindow>();
    QVERIFY(window);
    QUniUIKitView *contentView = qvariant_cast<QUniUIKitView *>(window->property("contentView"));
    QUniUIKitView *orphanView = qvariant_cast<QUniUIKitView *>(window->property("orphanView"));
    QVERIFY(orphanView);

    // Check that initial configuration is as expected
    QVERIFY(orphanView->geometry().isEmpty());
    QCOMPARE(orphanView->parent(), window->rootViewController());
    QCOMPARE(orphanView->uiViewHandle().superview, nullptr);

    // Reparent orphanView in, and check that geometry bindings take effect
    orphanView->setParent(contentView);
    QCOMPARE(orphanView->parent(), contentView);
    QCOMPARE(orphanView->uiViewHandle().superview, contentView->uiViewHandle());
    QCOMPARE(orphanView->geometry().size(), contentView->geometry().size());

    // Reparent orphanView out again where it came from
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
