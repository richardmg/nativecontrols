/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native UIKit Controls module of the Qt Toolkit.
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

#include <QtCore>

#include <QtUniUIKitControls/quniuikitviewcontroller.h>
#include <QtUniUIKitControls/quniuikitview.h>
#include <QtUniUIKitControls/quniuikittabbaritem.h>
#include <QtUniUIKitControls/private/quniuikitview_p.h>
#include <QtUniUIKitControls/private/quniuikitviewcontroller_p.h>
#include <QtUniUIKitControls/private/quniuikittabbaritem_p.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitViewControllerPrivate::QUniUIKitViewControllerPrivate(int version)
    : QUniUIKitBasePrivate(version)
    , m_tabBarItem(nullptr)
    , m_view(nullptr)
{
}

QUniUIKitViewControllerPrivate::~QUniUIKitViewControllerPrivate()
{
}

UIViewController *QUniUIKitViewControllerPrivate::viewController() const
{
    return static_cast<UIViewController *>(nsObject());
}

void QUniUIKitViewControllerPrivate::createNSObject()
{
    UIViewController *vc = [[UIViewController new] autorelease];

    if (!m_view)
        m_view = new QUniUIKitView(vc.view, q_func());

    setNSObject(vc);
}

void QUniUIKitViewControllerPrivate::setNSObject(NSObject *nsObject)
{
    QUniUIKitBasePrivate::setNSObject(nsObject);

    syncTabBarItem();
    syncView();
}

void QUniUIKitViewControllerPrivate::syncView()
{
    @try {
        viewController().view = m_view ? m_view->uiViewHandle() : nullptr;
    } @catch (NSException *e) {
        // UIKit will throw an exception if trying to move a view from one view controller to
        // another without first removing it from the former viewcontroller explicit. Since it's
        // not in the nature of QML to just crash for such issues, and since we at the same
        // time don't want to add to much logic to work around UIKit, we choose to
        // just catch it, and continue if possible.
        NSLog(@"Exception: %@", e);
    }
}

void QUniUIKitViewControllerPrivate::syncTabBarItem()
{
    viewController().tabBarItem = m_tabBarItem ? m_tabBarItem->uiTabBarItemHandle() : nil;
}

void QUniUIKitViewControllerPrivate::addChildViewController(UIViewController *child)
{
    [viewController() addChildViewController:child];
}

void QUniUIKitViewControllerPrivate::addSubViewToContentView(UIView *uiView)
{
    QUniUIKitView *view = q_func()->view();
    if (!view) {
        qWarning("The view controller doesn't have a content view");
        return;
    }
    QUniUIKitViewPrivate *dptr_contentView = dynamic_cast<QUniUIKitViewPrivate *>(QObjectPrivate::get(view));
    dptr_contentView->addSubView(uiView);
}

QUniUIKitViewController::QUniUIKitViewController(QUniUIKitBase *parent)
    : QUniUIKitBase(*new QUniUIKitViewControllerPrivate(), parent)
{
}

QUniUIKitViewController::QUniUIKitViewController(QUniUIKitViewControllerPrivate &dd, QUniUIKitBase *parent)
    :QUniUIKitBase(dd, parent)
{
}

QUniUIKitViewController::~QUniUIKitViewController()
{
}

IMPLEMENT_GETTER_AND_SETTER_POINTER(tabBarItem, TabBarItem, QUniUIKitTabBarItem, QUniUIKitViewController)
IMPLEMENT_GETTER_AND_SETTER_POINTER(view, View, QUniUIKitView, QUniUIKitViewController)

UIViewController *QUniUIKitViewController::uiViewControllerHandle()
{
    return d_func()->viewController();
}

QUniUIKitViewController *QUniUIKitViewController::parentViewController()
{
    return qobject_cast<QUniUIKitViewController *>(parent());
}

void QUniUIKitViewController::childEvent(QChildEvent *event)
{
    Q_D(QUniUIKitViewController);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QObjectPrivate *childPrivate = QObjectPrivate::get(event->child());

    if (QUniUIKitViewControllerPrivate *dptr_child = dynamic_cast<QUniUIKitViewControllerPrivate *>(childPrivate)) {
        if (event->added())
            d->addChildViewController(dptr_child->q_func()->uiViewControllerHandle());
        else
            [dptr_child->viewController() removeFromParentViewController];
    }
}

#include "moc_quniuikitviewcontroller.cpp"

QT_END_NAMESPACE
