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

#include <QtNativeAppKitControls/quniappkitviewcontroller.h>
#include <QtNativeAppKitControls/quniappkitview.h>
#include <QtNativeAppKitControls/quniappkittabviewitem.h>
#include <QtNativeAppKitControls/private/quniappkitview_p.h>
#include <QtNativeAppKitControls/private/quniappkitviewcontroller_p.h>

QT_BEGIN_NAMESPACE

QUniAppKitViewControllerPrivate::QUniAppKitViewControllerPrivate(int version)
    : QUniAppKitBasePrivate(version)
    , m_viewController(nullptr)
    , m_view(nullptr)
{
}

QUniAppKitViewControllerPrivate::~QUniAppKitViewControllerPrivate()
{
    [m_viewController release];
}

QUniAppKitViewController::QUniAppKitViewController(QUniAppKitBase *parent)
    : QUniAppKitBase(*new QUniAppKitViewControllerPrivate(), parent)
{
}

QUniAppKitViewController::QUniAppKitViewController(QUniAppKitViewControllerPrivate &dd, QUniAppKitBase *parent)
    : QUniAppKitBase(dd, parent)
{
}

QUniAppKitViewController::~QUniAppKitViewController()
{
}

NSViewController *QUniAppKitViewControllerPrivate::viewController()
{
    if (!m_viewController)
        m_viewController = createViewController();
    return m_viewController;
}

NSViewController *QUniAppKitViewControllerPrivate::createViewController()
{
    m_viewController = [NSViewController new];
    m_view = new QUniAppKitView(q_func());
    m_viewController.view = m_view->nsViewHandle();
    return m_viewController;
}

void QUniAppKitViewControllerPrivate::addChildViewController(NSViewController *child)
{
    [viewController() addChildViewController:child];
}

void QUniAppKitViewControllerPrivate::addSubViewToContentView(NSView *uiView)
{
    QUniAppKitView *view = q_func()->view();
    if (!view) {
        qWarning("The view controller doesn't have a content view");
        return;
    }
    QUniAppKitViewPrivate *dptr_contentView = dynamic_cast<QUniAppKitViewPrivate *>(QObjectPrivate::get(view));
    dptr_contentView->addSubView(uiView);
}

QUniAppKitViewController *QUniAppKitViewController::parentViewController()
{
    return qobject_cast<QUniAppKitViewController *>(parent());
}

QUniAppKitView *QUniAppKitViewController::view() const
{
    // Note that a decendant view controller might not use a view
    // (e.g QUniAppKitTabsViewController). In that case, we return nil
    const_cast<QUniAppKitViewController *>(this)->nsViewControllerHandle();
    return d_func()->m_view;
}

void QUniAppKitViewController::setView(QUniAppKitView *view)
{
    Q_D(QUniAppKitViewController);
    if (d->m_view == view)
        return;

    d->m_view = view;
    nsViewControllerHandle().view = view->nsViewHandle();
    emit viewChanged(view);
}

void QUniAppKitViewController::setChildViewControllers(QList<QUniAppKitViewController *> list)
{
    d_func()->m_childViewControllers = list;
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:list.length()];
    for (auto viewController : list)
        [array addObject:viewController->nsViewControllerHandle()];
    nsViewControllerHandle().childViewControllers = array;
}

QList<QUniAppKitViewController *> QUniAppKitViewController::childViewControllers() const
{
    return d_func()->m_childViewControllers;
}

NSViewController *QUniAppKitViewController::nsViewControllerHandle()
{
    return d_func()->viewController();
}

bool QUniAppKitViewController::setNativeParent(QObject *parent)
{
    if (QUniAppKitViewController *p = qobject_cast<QUniAppKitViewController *>(parent))
        setParent(p);
    else
        return QUniAppKitBase::setNativeParent(parent);
    return true;
}

bool QUniAppKitViewController::setNativeParent(const QByteArray &type, void *parent)
{
    if (type == "NSViewController")
        [static_cast<NSViewController *>(parent) addChildViewController:nsViewControllerHandle()];
    else
        return QUniAppKitBase::setNativeParent(type, parent);
    return true;
}

bool QUniAppKitViewController::addNativeChild(QObject *child)
{
    if (QUniAppKitView *c = qobject_cast<QUniAppKitView *>(child))
        c->setParent(this);
    else if (QUniAppKitViewController *c = qobject_cast<QUniAppKitViewController *>(child))
        c->setParent(this);
    else
        return QUniAppKitBase::addNativeChild(child);
    return true;
}

bool QUniAppKitViewController::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "NSView")
        d_func()->addSubViewToContentView(static_cast<NSView *>(child));
    else if (type == "NSViewController")
        [nsViewControllerHandle() addChildViewController:static_cast<NSViewController *>(child)];
    else
        return QUniAppKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QUniAppKitViewController::supportedNativeChildTypes()
{
    return QUniAppKitBase::supportedNativeChildTypes() << "NSView" << "NSViewController";
}

QByteArrayList QUniAppKitViewController::supportedNativeParentTypes()
{
    return QUniAppKitBase::supportedNativeChildTypes() << "NSViewController";
}

void QUniAppKitViewController::childEvent(QChildEvent *event)
{
    Q_D(QUniAppKitViewController);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
     QObjectPrivate *childPrivate = QObjectPrivate::get(event->child());

     if (QUniAppKitViewPrivate *dptr_child = dynamic_cast<QUniAppKitViewPrivate *>(childPrivate)) {
         // QUniAppKitView added as children of a plain QUniAppKitViewController will
         // have their NSViews added as children of the content view instead as a convenience.
         // But we only do this if the view controller is a plain QUniAppKitViewController.
         // Otherwise, if you e.g assign a NSView to UITabBarController.view, it will no longer
         // behave like a tab bar, but instead fall back to act like a normal view controller.
         if (![nsViewControllerHandle() isMemberOfClass:[NSViewController class]])
             return;
         if (event->added()) {
             // QUniAppKitView added as children of the view controller will
             // have their NSViews added as children of the content view instead.
             // Since you are allowed to set a parentless view explicit as a
             // content view, and then later do the reparenting, we need to ensure
             // that we don't try to make the content view a subview of itself.
             QUniAppKitView *contentView = d->m_view;
             QUniAppKitView *subView = dptr_child->q_func();
             if (contentView && subView != contentView)
                 d->addSubViewToContentView(subView->nsViewHandle());
         } else if (event->removed()) {
             [dptr_child->view() removeFromSuperview];
         }
     } else if (QUniAppKitViewControllerPrivate *dptr_child = dynamic_cast<QUniAppKitViewControllerPrivate *>(childPrivate)) {
         if (event->added())
             d->addChildViewController(dptr_child->q_func()->nsViewControllerHandle());
         else
             [dptr_child->m_viewController removeFromParentViewController];
     }
}

#include "moc_quniappkitviewcontroller.cpp"


QT_END_NAMESPACE
