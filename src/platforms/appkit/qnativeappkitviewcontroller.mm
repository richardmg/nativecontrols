/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native AppKit Controls module of the Qt Toolkit.
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

#include <AppKit/AppKit.h>

#include <QtCore>

#include <QtNativeAppKitControls/qnativeappkitviewcontroller.h>
#include <QtNativeAppKitControls/qnativeappkitview.h>
#include <QtNativeAppKitControls/qnativeappkittabviewitem.h>
#include <QtNativeAppKitControls/private/qnativeappkitview_p.h>
#include <QtNativeAppKitControls/private/qnativeappkitviewcontroller_p.h>

QT_BEGIN_NAMESPACE

QNativeAppKitViewControllerPrivate::QNativeAppKitViewControllerPrivate(int version)
    : QNativeAppKitBasePrivate(version)
    , m_tabViewItem(nullptr)
    , m_viewController(nullptr)
    , m_view(nullptr)
{
}

QNativeAppKitViewControllerPrivate::~QNativeAppKitViewControllerPrivate()
{
    [m_viewController release];
}

QNativeAppKitViewController::QNativeAppKitViewController(QNativeAppKitBase *parent)
    : QNativeAppKitBase(*new QNativeAppKitViewControllerPrivate(), parent)
{
}

QNativeAppKitViewController::QNativeAppKitViewController(QNativeAppKitViewControllerPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitBase(dd, parent)
{
}

QNativeAppKitViewController::~QNativeAppKitViewController()
{
}

NSViewController *QNativeAppKitViewControllerPrivate::viewController()
{
    if (!m_viewController) {
        m_viewController = createViewController();
        if (QNativeAppKitViewController *parent = q_func()->parentViewController())
            static_cast<QNativeAppKitViewControllerPrivate *>(QObjectPrivate::get(parent))->addChildViewController(m_viewController);
    }
    return m_viewController;
}

NSViewController *QNativeAppKitViewControllerPrivate::createViewController()
{
    NSViewController *viewController = [NSViewController new];
    viewController.view = [NSView new];
    return viewController;
}

void QNativeAppKitViewControllerPrivate::addChildViewController(NSViewController *child)
{
    [viewController() addChildViewController:child];
}

QNativeAppKitViewController *QNativeAppKitViewController::parentViewController()
{
    return dynamic_cast<QNativeAppKitViewController *>(parent());
}

void QNativeAppKitViewController::setTabViewItem(QNativeAppKitTabViewItem *tabViewItem)
{
    d_func()->m_tabViewItem = tabViewItem;
}

QNativeAppKitTabViewItem *QNativeAppKitViewController::tabViewItem() const
{
    return d_func()->m_tabViewItem;
}

QNativeAppKitView *QNativeAppKitViewController::view() const
{
    Q_D(const QNativeAppKitViewController);
    if (!d->m_view) {
        QNativeAppKitViewController *self = const_cast<QNativeAppKitViewController *>(this);
        self->setView(new QNativeAppKitView());
        // Set parent in the end to ensure we don't get confused when
        // getting a childEvent before having a d->m_view assigned.
        d->m_view->setParent(self);
    }
    return d->m_view;
}

void QNativeAppKitViewController::setView(QNativeAppKitView *view)
{
    Q_D(QNativeAppKitViewController);
    if (d->m_view == view)
        return;

    d->m_view = view;
    nsViewControllerHandle().view = d->m_view->nsViewHandle();
    emit viewChanged(view);
}

NSViewController *QNativeAppKitViewController::nsViewControllerHandle()
{
    return d_func()->viewController();
}

void QNativeAppKitViewController::childEvent(QChildEvent *event)
{
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QNativeAppKitViewPrivate *dptr_child = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    QNativeAppKitViewPrivate *dptr_contentView = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(view()));
    if (event->added()) {
        // QNativeUIKitView added as children of the view controller will
        // have their UIViews added as children of the content view instead.
        // Since you are allowed to set a parentless view explicit as a
        // content view, and then later do the reparenting, we need to ensure
        // that we don't try to make the content view a subview of itself.
        QNativeAppKitView *contentView = d_func()->m_view;
        QNativeAppKitView *subView = dptr_child->q_func();
        if (subView != contentView) {
            // Note: the next call might lazy create the content view, in
            // which case we'll get a recursive call back to childEvent.
            dptr_contentView->addSubView(subView->nsViewHandle());
        }
    } else if (event->removed()) {
        dptr_contentView->removeSubView(dptr_child->view());
    }
}

#include "moc_qnativeappkitviewcontroller.cpp"


QT_END_NAMESPACE
