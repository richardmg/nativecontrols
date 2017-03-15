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

#include <QtNativeUIKitControls/quniuikittabbarcontroller.h>
#include <QtNativeUIKitControls/private/quniuikittabbarcontroller_p.h>
#include <QtNativeUIKitControls/quniuikittabbaritem.h>
#include <QtNativeUIKitControls/private/quniuikittabbaritem_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitTabBarControllerPrivate::QNativeUIKitTabBarControllerPrivate(int version)
    : QNativeUIKitViewControllerPrivate(version)
{
}

QNativeUIKitTabBarControllerPrivate::~QNativeUIKitTabBarControllerPrivate()
{
}

UIViewController *QNativeUIKitTabBarControllerPrivate::createViewController()
{
    return [UITabBarController new];
}

QNativeUIKitTabBarController::QNativeUIKitTabBarController(QNativeUIKitBase *parent)
    : QNativeUIKitViewController(*new QNativeUIKitTabBarControllerPrivate(), parent)
{
}

QNativeUIKitTabBarController::QNativeUIKitTabBarController(QNativeUIKitTabBarControllerPrivate &dd, QNativeUIKitBase *parent)
    :QNativeUIKitViewController(dd, parent)
{
}

QNativeUIKitTabBarController::~QNativeUIKitTabBarController()
{
}

QNativeUIKitView *QNativeUIKitTabBarController::view() const
{
    qWarning("Creating a view for a view controller that is not member of class UIViewController. This can make it act as a normal view controller!");
    return QNativeUIKitViewController::view();
}

void QNativeUIKitTabBarController::setViewControllers(QList<QNativeUIKitViewController *> list)
{
    d_func()->m_viewControllers = list;
    NSMutableArray *array = [NSMutableArray arrayWithCapacity:list.length()];
    for (auto viewController : list)
        [array addObject:viewController->uiViewControllerHandle()];
    uiTabBarControllerHandle().viewControllers = array;
}

QList<QNativeUIKitViewController *> QNativeUIKitTabBarController::viewControllers() const
{
    return d_func()->m_viewControllers;
}

UITabBarController *QNativeUIKitTabBarController::uiTabBarControllerHandle()
{
    return static_cast<UITabBarController *>(uiViewControllerHandle());
}

#include "moc_quniuikittabbarcontroller.cpp"

QT_END_NAMESPACE
