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
    if (!m_viewController)
        m_viewController = createViewController();
    return m_viewController;
}

NSViewController *QNativeAppKitViewControllerPrivate::createViewController()
{
    m_viewController = [NSViewController new];
    m_view = new QNativeAppKitView(q_func());
    m_viewController.view = m_view->nsViewHandle();
    return m_viewController;
}

void QNativeAppKitViewControllerPrivate::addChildViewController(NSViewController *child)
{
    [viewController() addChildViewController:child];
}

void QNativeAppKitViewControllerPrivate::addSubViewToContentView(NSView *uiView)
{
    QNativeAppKitView *view = q_func()->view();
    if (!view) {
        qWarning("The view controller doesn't have a content view");
        return;
    }
    QNativeAppKitViewPrivate *dptr_contentView = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(view));
    dptr_contentView->addSubView(uiView);
}

QNativeAppKitViewController *QNativeAppKitViewController::parentViewController()
{
    return dynamic_cast<QNativeAppKitViewController *>(parent());
}

QNativeAppKitView *QNativeAppKitViewController::view() const
{
    // Note that a decendant view controller might not use a view
    // (e.g QNativeAppKitTabsViewController). In that case, we return nil
    const_cast<QNativeAppKitViewController *>(this)->nsViewControllerHandle();
    return d_func()->m_view;
}

void QNativeAppKitViewController::setView(QNativeAppKitView *view)
{
    Q_D(QNativeAppKitViewController);
    if (d->m_view == view)
        return;

    d->m_view = view;
    nsViewControllerHandle().view = view->nsViewHandle();
    emit viewChanged(view);
}

void QNativeAppKitViewController::setChildViewControllers(QList<QNativeAppKitViewController *> list)
{
    d_func()->m_childViewControllers = list;
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:list.length()];
    for (auto viewController : list)
        [array addObject:viewController->nsViewControllerHandle()];
    nsViewControllerHandle().childViewControllers = array;
}

QList<QNativeAppKitViewController *> QNativeAppKitViewController::childViewControllers() const
{
    return d_func()->m_childViewControllers;
}

NSViewController *QNativeAppKitViewController::nsViewControllerHandle()
{
    return d_func()->viewController();
}

bool QNativeAppKitViewController::setNativeParent(QObject *parent)
{
    if (QNativeAppKitViewController *p = dynamic_cast<QNativeAppKitViewController *>(parent))
        setParent(p);
    else
        return QNativeAppKitBase::setNativeParent(parent);
    return true;
}

bool QNativeAppKitViewController::setNativeParent(const QByteArray &type, void *parent)
{
    if (type == "NSViewController")
        [static_cast<NSViewController *>(parent) addChildViewController:nsViewControllerHandle()];
    else
        return QNativeAppKitBase::setNativeParent(type, parent);
    return true;
}

bool QNativeAppKitViewController::addNativeChild(QObject *child)
{
    if (QNativeAppKitView *c = dynamic_cast<QNativeAppKitView *>(child))
        c->setParent(this);
    else if (QNativeAppKitViewController *c = dynamic_cast<QNativeAppKitViewController *>(child))
        c->setParent(this);
    else
        return QNativeAppKitBase::addNativeChild(child);
    return true;
}

bool QNativeAppKitViewController::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "NSView")
        d_func()->addSubViewToContentView(static_cast<NSView *>(child));
    else if (type == "NSViewController")
        [nsViewControllerHandle() addChildViewController:static_cast<NSViewController *>(child)];
    else
        return QNativeAppKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QNativeAppKitViewController::supportedNativeChildTypes()
{
    return QNativeAppKitBase::supportedNativeChildTypes() << "NSView" << "NSViewController";
}

QByteArrayList QNativeAppKitViewController::supportedNativeParentTypes()
{
    return QNativeAppKitBase::supportedNativeChildTypes() << "NSViewController";
}

void QNativeAppKitViewController::childEvent(QChildEvent *event)
{
    Q_D(QNativeAppKitViewController);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
     QObjectPrivate *childPrivate = QObjectPrivate::get(event->child());

     if (QNativeAppKitViewPrivate *dptr_child = dynamic_cast<QNativeAppKitViewPrivate *>(childPrivate)) {
         // QNativeAppKitView added as children of a plain QNativeAppKitViewController will
         // have their NSViews added as children of the content view instead as a convenience.
         // But we only do this if the view controller is a plain QNativeAppKitViewController.
         // Otherwise, if you e.g assign a NSView to UITabBarController.view, it will no longer
         // behave like a tab bar, but instead fall back to act like a normal view controller.
         if (![nsViewControllerHandle() isMemberOfClass:[NSViewController class]])
             return;
         if (event->added()) {
             // QNativeAppKitView added as children of the view controller will
             // have their NSViews added as children of the content view instead.
             // Since you are allowed to set a parentless view explicit as a
             // content view, and then later do the reparenting, we need to ensure
             // that we don't try to make the content view a subview of itself.
             QNativeAppKitView *contentView = d->m_view;
             QNativeAppKitView *subView = dptr_child->q_func();
             if (contentView && subView != contentView)
                 d->addSubViewToContentView(subView->nsViewHandle());
         } else if (event->removed()) {
             [dptr_child->view() removeFromSuperview];
         }
     } else if (QNativeAppKitViewControllerPrivate *dptr_child = dynamic_cast<QNativeAppKitViewControllerPrivate *>(childPrivate)) {
         if (event->added())
             d->addChildViewController(dptr_child->q_func()->nsViewControllerHandle());
         else
             [dptr_child->m_viewController removeFromParentViewController];
     }
}

#include "moc_qnativeappkitviewcontroller.cpp"


QT_END_NAMESPACE
