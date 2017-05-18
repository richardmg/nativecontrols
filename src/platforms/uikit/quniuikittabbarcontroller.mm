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

#include <QtUniUIKitControls/quniuikittabbarcontroller.h>
#include <QtUniUIKitControls/private/quniuikittabbarcontroller_p.h>
#include <QtUniUIKitControls/quniuikittabbaritem.h>
#include <QtUniUIKitControls/private/quniuikittabbaritem_p.h>

@interface QUniUIKitTabBarControllerDelegate : NSObject <UITabBarControllerDelegate> {
    QT_PREPEND_NAMESPACE(QUniUIKitTabBarControllerPrivate) *_tabBarPrivate;
}
@end

@implementation QUniUIKitTabBarControllerDelegate

-(id)initWithQUniUIKitTabBarControllerPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitTabBarControllerPrivate) *)tabBarPrivate
{
    self = [super init];
    if (self) {
        _tabBarPrivate = tabBarPrivate;
    }

    return self;
}

- (void)tabBarController:(UITabBarController *)tabBarController
    didSelectViewController:(UIViewController *)viewController
{
    Q_UNUSED(tabBarController);
    Q_UNUSED(viewController);
    QUniUIKitTabBarController *qtabBar = _tabBarPrivate->q_func();
    _tabBarPrivate->m_requestedSelectedIndex = qtabBar->selectedIndex();
    if (_tabBarPrivate->m_requestedSelectedViewController) {
        // Only set m_requestedSelectedViewController if already specified
        // by the application, since setting it will override m_requestedSelectedIndex.
        _tabBarPrivate->m_requestedSelectedViewController = qtabBar->selectedViewController();
    }
    emit qtabBar->selectedIndexChanged(_tabBarPrivate->m_requestedSelectedIndex);
    emit qtabBar->selectedViewControllerChanged(_tabBarPrivate->m_requestedSelectedViewController);
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitTabBarControllerPrivate::QUniUIKitTabBarControllerPrivate(int version)
    : QUniUIKitViewControllerPrivate(version)
    , m_requestedSelectedViewController(nullptr)
    , m_requestedSelectedIndex(0)
{
}

QUniUIKitTabBarControllerPrivate::~QUniUIKitTabBarControllerPrivate()
{
    [static_cast<UITabBarController *>(viewController()).delegate release];
}

void QUniUIKitTabBarControllerPrivate::createNSObject()
{
    UITabBarController *tabBarController = [[UITabBarController new] autorelease];
    setNSObject(tabBarController);

    tabBarController.delegate = [[QUniUIKitTabBarControllerDelegate alloc] initWithQUniUIKitTabBarControllerPrivate:this];
}

void QUniUIKitTabBarControllerPrivate::appendChild(QQmlListProperty<QUniUIKitViewController> *list, QUniUIKitViewController *child)
{
    QUniUIKitTabBarController *qq = static_cast<QUniUIKitTabBarController *>(list->object);
    QUniUIKitViewController *vcChild = qobject_cast<QUniUIKitViewController *>(child);
    if (!vcChild)
        return;

    qq->setViewControllers(qq->viewControllers() << vcChild);
}

int QUniUIKitTabBarControllerPrivate::count(QQmlListProperty<QUniUIKitViewController> *list)
{
    QUniUIKitTabBarController *qq = static_cast<QUniUIKitTabBarController *>(list->object);
    return qq->d_func()->m_viewControllers.count();
}

QUniUIKitViewController *QUniUIKitTabBarControllerPrivate::at(QQmlListProperty<QUniUIKitViewController> *list, int index)
{
    QUniUIKitTabBarController *qq = static_cast<QUniUIKitTabBarController *>(list->object);
    return qq->d_func()->m_viewControllers.at(index);
}

void QUniUIKitTabBarControllerPrivate::clear(QQmlListProperty<QUniUIKitViewController> *list)
{
    QUniUIKitTabBarController *qq = static_cast<QUniUIKitTabBarController *>(list->object);
    qq->setViewControllers(QList<QUniUIKitViewController *>());
}

QQmlListProperty<QUniUIKitViewController> QUniUIKitTabBarController::viewControllersAsQmlList()
{
    return QQmlListProperty<QUniUIKitViewController>(this, 0
         , QUniUIKitTabBarControllerPrivate::appendChild
         , QUniUIKitTabBarControllerPrivate::count
         , QUniUIKitTabBarControllerPrivate::at
         , QUniUIKitTabBarControllerPrivate::clear);
}

QUniUIKitTabBarController::QUniUIKitTabBarController(QUniUIKitBase *parent)
    : QUniUIKitViewController(*new QUniUIKitTabBarControllerPrivate(), parent)
{
}

QUniUIKitTabBarController::QUniUIKitTabBarController(QUniUIKitTabBarControllerPrivate &dd, QUniUIKitBase *parent)
    :QUniUIKitViewController(dd, parent)
{
}

QUniUIKitTabBarController::~QUniUIKitTabBarController()
{
}

QUniUIKitView *QUniUIKitTabBarController::view() const
{
    qWarning("Creating a view for a view controller that is not member of class UIViewController. This can make it act as a normal view controller!");
    return QUniUIKitViewController::view();
}

int QUniUIKitTabBarController::selectedIndex() const
{
    return static_cast<UITabBarController *>(d_func()->viewController()).selectedIndex;
}

void QUniUIKitTabBarController::setSelectedIndex(int newSelectedIndex)
{
    Q_D(QUniUIKitTabBarController);
    // Note that it's fully possible to set an invalid index at this
    // point that later becomes valid after assigning viewControllers.
    // As such, we need a helper variable (m_requestedSelectedIndex).
    d->m_requestedSelectedIndex = newSelectedIndex;
    d->m_requestedSelectedViewController = nullptr;
    if (selectedIndex() == newSelectedIndex)
        return;

    uiTabBarControllerHandle().selectedIndex = newSelectedIndex;

    emit selectedIndexChanged(selectedIndex());
    emit selectedViewControllerChanged(selectedViewController());
}

QUniUIKitViewController *QUniUIKitTabBarController::selectedViewController() const
{
    UITabBarController *tabBar = static_cast<UITabBarController *>(d_func()->viewController());
    return static_cast<QUniUIKitViewController *>(qt_getAssociatedQObject(tabBar.selectedViewController));
}

void QUniUIKitTabBarController::setSelectedViewController(QUniUIKitViewController *newSelectedViewController)
{
    Q_D(QUniUIKitTabBarController);
    // Note that it's fully possible to set an invalid viewcontroller at this
    // point that later becomes valid after assigning viewControllers.
    // As such, we need a helper variable (m_requestedSelectedViewController).
    d->m_requestedSelectedViewController = newSelectedViewController;
    if (selectedViewController() == newSelectedViewController)
        return;

    if (!d->m_viewControllers.contains(newSelectedViewController))
        return;

    uiTabBarControllerHandle().selectedViewController = newSelectedViewController->uiViewControllerHandle();

    emit selectedIndexChanged(selectedIndex());
    emit selectedViewControllerChanged(selectedViewController());
}

void QUniUIKitTabBarController::setViewControllers(QList<QUniUIKitViewController *> list)
{
    Q_D(QUniUIKitTabBarController);
    int prevSelectedIndex = selectedIndex();
    QUniUIKitViewController *prevSelectedViewController = selectedViewController();

    d->m_viewControllers = list;
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:list.length()];
    for (auto viewController : list)
        [array addObject:viewController->uiViewControllerHandle()];
    uiTabBarControllerHandle().viewControllers = array;

    if (d->m_requestedSelectedViewController) {
        if (d->m_viewControllers.contains(d->m_requestedSelectedViewController))
            uiTabBarControllerHandle().selectedViewController = d->m_requestedSelectedViewController->uiViewControllerHandle();
    } else {
        uiTabBarControllerHandle().selectedIndex = d->m_requestedSelectedIndex;
    }

    if (prevSelectedIndex != selectedIndex())
        emit selectedIndexChanged(selectedIndex());
    if (prevSelectedViewController != selectedViewController())
        emit selectedViewControllerChanged(selectedViewController());
    emit viewControllersChanged(d->m_viewControllers);
}

QList<QUniUIKitViewController *> QUniUIKitTabBarController::viewControllers() const
{
    return d_func()->m_viewControllers;
}

UITabBarController *QUniUIKitTabBarController::uiTabBarControllerHandle()
{
    return static_cast<UITabBarController *>(uiViewControllerHandle());
}

void QUniUIKitTabBarController::childEvent(QChildEvent *event)
{
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QObjectPrivate *childPrivate = QObjectPrivate::get(event->child());
    // Only support setting tabs using setViewControllers.
    if (!dynamic_cast<QUniUIKitViewControllerPrivate *>(childPrivate))
        QUniUIKitViewController::childEvent(event);
}

#include "moc_quniuikittabbarcontroller.cpp"

QT_END_NAMESPACE
