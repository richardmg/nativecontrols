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

#include <QtNativeUIKitControls/qnativeuikitviewcontroller.h>
#include <QtNativeUIKitControls/qnativeuikitview.h>
#include <QtNativeUIKitControls/qnativeuikittabbaritem.h>
#include <QtNativeUIKitControls/private/qnativeuikitview_p.h>
#include <QtNativeUIKitControls/private/qnativeuikitviewcontroller_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitViewControllerPrivate::QNativeUIKitViewControllerPrivate(int version)
    : QNativeUIKitBasePrivate(version)
    , m_tabBarItem(nullptr)
    , m_viewController(nullptr)
    , m_view(nullptr)
{
}

QNativeUIKitViewControllerPrivate::~QNativeUIKitViewControllerPrivate()
{
    [m_viewController release];
}

QNativeUIKitViewController::QNativeUIKitViewController(QNativeUIKitBase *parent)
    : QNativeUIKitBase(*new QNativeUIKitViewControllerPrivate(), parent)
{
}

QNativeUIKitViewController::QNativeUIKitViewController(QNativeUIKitViewControllerPrivate &dd, QNativeUIKitBase *parent)
    :QNativeUIKitBase(dd, parent)
{
}

QNativeUIKitViewController::~QNativeUIKitViewController()
{
}

UIViewController *QNativeUIKitViewControllerPrivate::viewController()
{
    if (!m_viewController) {
        m_viewController = createViewController();
        if (QNativeUIKitViewController *parent = q_func()->parentViewController())
            static_cast<QNativeUIKitViewControllerPrivate *>(QObjectPrivate::get(parent))->addChildViewController(m_viewController);
    }
    return m_viewController;
}

UIViewController *QNativeUIKitViewControllerPrivate::createViewController()
{
    return [UIViewController new];
}

void QNativeUIKitViewControllerPrivate::addChildViewController(UIViewController *child)
{
    [viewController() addChildViewController:child];
}

QNativeUIKitViewController *QNativeUIKitViewController::parentViewController()
{
    return dynamic_cast<QNativeUIKitViewController *>(parent());
}

void QNativeUIKitViewController::setTabBarItem(QNativeUIKitTabBarItem *tabBarItem)
{
    d_func()->m_tabBarItem = tabBarItem;
    uiViewControllerHandle().tabBarItem = tabBarItem->uiTabBarItemHandle();
}

QNativeUIKitTabBarItem *QNativeUIKitViewController::tabBarItem() const
{
    return d_func()->m_tabBarItem;
}

QNativeUIKitView *QNativeUIKitViewController::view() const
{
    Q_D(const QNativeUIKitViewController);
    if (!d->m_view) {
        QNativeUIKitViewController *self = const_cast<QNativeUIKitViewController *>(this);
        self->setView(new QNativeUIKitView());
        // Set parent in the end to ensure we don't get confused when
        // getting a childEvent before having a d->m_view assigned.
        d->m_view->setParent(self);
    }
    return d->m_view;
}

void QNativeUIKitViewController::setView(QNativeUIKitView *view)
{
    Q_D(QNativeUIKitViewController);
    if (d->m_view == view)
        return;

    d->m_view = view;
    uiViewControllerHandle().view = d->m_view->uiViewHandle();
    emit viewChanged(view);
}

UIViewController *QNativeUIKitViewController::uiViewControllerHandle()
{
    return d_func()->viewController();
}

void QNativeUIKitViewController::childEvent(QChildEvent *event)
{
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QNativeUIKitViewPrivate *dptr_child = dynamic_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    if (event->added()) {
        // QNativeUIKitView added as children of the view controller will
        // have their UIViews added as children of the content view instead.
        // Since you are allowed to set a parentless view explicit as a
        // content view, and then later do the reparenting, we need to ensure
        // that we don't try to make the content view a subview of itself.
        QNativeUIKitView *contentView = d_func()->m_view;
        QNativeUIKitView *subView = dptr_child->q_func();
        if (subView != contentView) {
            // Note: the next call might lazy create the content view, in
            // which case we'll get a recursive call back to childEvent.
            QNativeUIKitViewPrivate *dptr_contentView = dynamic_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(view()));
            dptr_contentView->addSubView(subView->uiViewHandle());
        }
    } else if (event->removed()) {
        [dptr_child->view() removeFromSuperview];
    }
}

#include "moc_qnativeuikitviewcontroller.cpp"

QT_END_NAMESPACE
