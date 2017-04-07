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
    void defaultGeometery();
    void setGeometery();
    void defaultImplicitSize();
    void setImplicitSize();
    void setGeometryWithNaN();
    void reparentChildViews();
    void reparentRootViews();
    void toggleVisibility();
    void setBackgroundColor();
};

void tst_view::hierarchyCheck()
{
    QSharedPointer<QObject> root = loadQml("app1.qml");
    QVERIFY(root);

    // Ensure that all properties are set
    QUniUIKitViewController *viewController = qvariant_cast<QUniUIKitViewController *>(root->property("rootViewController"));
    QUniUIKitView *rootView = qvariant_cast<QUniUIKitView *>(root->property("rootView"));
    QUniUIKitView *contentView = qvariant_cast<QUniUIKitView *>(root->property("contentView"));
    QUniUIKitButton *button = qvariant_cast<QUniUIKitButton *>(root->property("button"));
    QVERIFY(viewController);
    QVERIFY(rootView);
    QVERIFY(contentView);
    QVERIFY(button);

    // Check that the hierarchy that was specified in QML matches
    // the hierarchy that is reported from the platform controls
    QVERIFY(viewController->view() == rootView);
    QVERIFY(contentView->parentView() == rootView);
    QVERIFY(button->parentView() == contentView);

    // Check that the hierarchy of the native UIKit controls matches
    // the hierarchy of the platform controls
    QVERIFY(button->uiButtonHandle().superview == contentView->uiViewHandle());
    QVERIFY(contentView->uiViewHandle().superview == rootView->uiViewHandle());
    QVERIFY(viewController->uiViewControllerHandle().view == rootView->uiViewHandle());
}

void tst_view::defaultGeometery()
{
}

void tst_view::setGeometery()
{
}

void tst_view::defaultImplicitSize()
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
