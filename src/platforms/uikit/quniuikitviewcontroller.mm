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

QT_BEGIN_NAMESPACE

QUniUIKitViewControllerPrivate::QUniUIKitViewControllerPrivate(int version)
    : QUniUIKitBasePrivate(version)
    , m_tabBarItem(nullptr)
    , m_viewController(nullptr)
    , m_view(nullptr)
{
}

QUniUIKitViewControllerPrivate::~QUniUIKitViewControllerPrivate()
{
    [m_viewController release];
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

UIViewController *QUniUIKitViewControllerPrivate::viewController()
{
    if (!m_viewController)
        m_viewController = createViewController();
    return m_viewController;
}

UIViewController *QUniUIKitViewControllerPrivate::createViewController()
{
    m_viewController = [UIViewController new];
    m_view = new QUniUIKitView(q_func());
    m_viewController.view = m_view->uiViewHandle();
    return m_viewController;
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

QUniUIKitViewController *QUniUIKitViewController::parentViewController()
{
    return qobject_cast<QUniUIKitViewController *>(parent());
}

void QUniUIKitViewController::setTabBarItem(QUniUIKitTabBarItem *tabBarItem)
{
    d_func()->m_tabBarItem = tabBarItem;
    uiViewControllerHandle().tabBarItem = tabBarItem->uiTabBarItemHandle();
}

QUniUIKitTabBarItem *QUniUIKitViewController::tabBarItem() const
{
    return d_func()->m_tabBarItem;
}

QUniUIKitView *QUniUIKitViewController::view() const
{
    // Note that a decendant view controller might not use a view
    // (e.g QUniUIKitTabsViewController). In that case, we return nil
    const_cast<QUniUIKitViewController *>(this)->uiViewControllerHandle();
    return d_func()->m_view;
}

void QUniUIKitViewController::setView(QUniUIKitView *view)
{
    Q_D(QUniUIKitViewController);
    if (d->m_view == view)
        return;

    d->m_view = view;
    uiViewControllerHandle().view = view->uiViewHandle();
    emit viewChanged(view);
}

UIViewController *QUniUIKitViewController::uiViewControllerHandle()
{
    return d_func()->viewController();
}

bool QUniUIKitViewController::setNativeParent(QObject *parent)
{
    if (QUniUIKitViewController *p = qobject_cast<QUniUIKitViewController *>(parent))
        setParent(p);
    else
        return QUniUIKitBase::setNativeParent(parent);
    return true;
}

bool QUniUIKitViewController::setNativeParent(const QByteArray &type, void *parent)
{
    if (type == "UIViewController")
        [static_cast<UIViewController *>(parent) addChildViewController:uiViewControllerHandle()];
    else
        return QUniUIKitBase::setNativeParent(type, parent);
    return true;
}

bool QUniUIKitViewController::addNativeChild(QObject *child)
{
    if (QUniUIKitView *c = qobject_cast<QUniUIKitView *>(child))
        c->setParent(this);
    else if (QUniUIKitViewController *c = qobject_cast<QUniUIKitViewController *>(child))
        c->setParent(this);
    else
        return QUniUIKitBase::addNativeChild(child);
    return true;
}

bool QUniUIKitViewController::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "UIView")
        d_func()->addSubViewToContentView(static_cast<UIView *>(child));
    else if (type == "UIViewController")
        [uiViewControllerHandle() addChildViewController:static_cast<UIViewController *>(child)];
    else
        return QUniUIKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QUniUIKitViewController::supportedNativeChildTypes()
{
    return QUniUIKitBase::supportedNativeChildTypes() << "UIView" << "UIViewController";
}

QByteArrayList QUniUIKitViewController::supportedNativeParentTypes()
{
    return QUniUIKitBase::supportedNativeChildTypes() << "UIViewController";
}

void QUniUIKitViewController::childEvent(QChildEvent *event)
{
    Q_D(QUniUIKitViewController);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QObjectPrivate *childPrivate = QObjectPrivate::get(event->child());

    if (QUniUIKitViewPrivate *dptr_child = dynamic_cast<QUniUIKitViewPrivate *>(childPrivate)) {
        // QUniUIKitView added as children of a plain QUniUIKitViewController will
        // have their UIViews added as children of the content view instead as a convenience.
        // But we only do this if the view controller is a plain QUniUIKitViewController.
        // Otherwise, if you e.g assign a UIView to UITabBarController.view, it will no longer
        // behave like a tab bar, but instead fall back to act like a normal view controller.
        if (![uiViewControllerHandle() isMemberOfClass:[UIViewController class]])
            return;
        if (event->added()) {
            // Since you are allowed to set a parentless view explicit as a
            // content view, and then later do the reparenting, we need to ensure
            // that we don't try to make the content view a subview of itself.
            QUniUIKitView *contentView = d->m_view;
            QUniUIKitView *subView = dptr_child->q_func();
            if (contentView && subView != contentView)
                d->addSubViewToContentView(subView->uiViewHandle());
        } else if (event->removed()) {
            [dptr_child->view() removeFromSuperview];
        }
    } else if (QUniUIKitViewControllerPrivate *dptr_child = dynamic_cast<QUniUIKitViewControllerPrivate *>(childPrivate)) {
        if (event->added())
            d->addChildViewController(dptr_child->q_func()->uiViewControllerHandle());
        else
            [dptr_child->m_viewController removeFromParentViewController];
    } else if (QUniUIKitTabBarItemPrivate *dptr_child = dynamic_cast<QUniUIKitTabBarItemPrivate *>(childPrivate)) {
        if (event->added())
            setTabBarItem(dptr_child->q_func());
        else
            setTabBarItem(nullptr);
    }
}

#include "moc_quniuikitviewcontroller.cpp"

QT_END_NAMESPACE
