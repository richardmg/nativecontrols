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
    self = [self init];
    if (self) {
        _tabBarPrivate = tabBarPrivate;
    }

    return self;
}

- (void)tabBarController:(UITabBarController *)tabBarController
    didSelectViewController:(UIViewController *)viewController
{
    Q_UNUSED(viewController);
    _tabBarPrivate->m_selectedIndex = tabBarController.selectedIndex;
    emit _tabBarPrivate->q_func()->selectedIndexChanged(_tabBarPrivate->m_selectedIndex);
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitTabBarControllerPrivate::QUniUIKitTabBarControllerPrivate(int version)
    : QUniUIKitViewControllerPrivate(version)
    , m_selectedIndex(0)
{
}

QUniUIKitTabBarControllerPrivate::~QUniUIKitTabBarControllerPrivate()
{
    [static_cast<UITabBarController *>(viewController()).delegate release];
}

UIViewController *QUniUIKitTabBarControllerPrivate::createViewController()
{
    UITabBarController *tabBarController = [UITabBarController new];
    tabBarController.delegate = [[QUniUIKitTabBarControllerDelegate alloc] initWithQUniUIKitTabBarControllerPrivate:this];
    return tabBarController;
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
    return d_func()->m_selectedIndex;
}

void QUniUIKitTabBarController::setSelectedIndex(int newSelectedIndex)
{
    Q_D(QUniUIKitTabBarController);
    if (d->m_selectedIndex == newSelectedIndex)
        return;

    // Note that it's fully possible to set an invalid index at this
    // point that later becomes valid after assigning viewControllers.
    // As such, we need a helper variable (m_selectedIndex).
    d->m_selectedIndex = newSelectedIndex;
    uiTabBarControllerHandle().selectedIndex = newSelectedIndex;
    emit selectedIndexChanged(newSelectedIndex);
}

void QUniUIKitTabBarController::setViewControllers(QList<QUniUIKitViewController *> list)
{
    Q_D(QUniUIKitTabBarController);
    d->m_viewControllers = list;
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:list.length()];
    for (auto viewController : list)
        [array addObject:viewController->uiViewControllerHandle()];
    uiTabBarControllerHandle().viewControllers = array;
    uiTabBarControllerHandle().selectedIndex = d->m_selectedIndex;
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
    QUniUIKitViewController::childEvent(event);
    uiTabBarControllerHandle().selectedIndex = d_func()->m_selectedIndex;
}

#include "moc_quniuikittabbarcontroller.cpp"

QT_END_NAMESPACE
