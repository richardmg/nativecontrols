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

#include <QtNativeAppKitControls/qnativeappkittabviewcontroller.h>
#include <QtNativeAppKitControls/private/qnativeappkittabviewcontroller_p.h>
#include <QtNativeAppKitControls/qnativeappkittabviewitem.h>
#include <QtNativeAppKitControls/private/qnativeappkittabviewitem_p.h>

QT_BEGIN_NAMESPACE

QNativeAppKitTabViewControllerPrivate::QNativeAppKitTabViewControllerPrivate(int version)
    : QNativeAppKitViewControllerPrivate(version)
{
}

QNativeAppKitTabViewControllerPrivate::~QNativeAppKitTabViewControllerPrivate()
{
}

NSViewController *QNativeAppKitTabViewControllerPrivate::createViewController()
{
    return [NSTabViewController new];
}

QNativeAppKitTabViewController::QNativeAppKitTabViewController(QNativeAppKitBase *parent)
    : QNativeAppKitViewController(*new QNativeAppKitTabViewControllerPrivate(), parent)
{
}

QNativeAppKitTabViewController::QNativeAppKitTabViewController(QNativeAppKitTabViewControllerPrivate &dd, QNativeAppKitBase *parent)
    :QNativeAppKitViewController(dd, parent)
{
}

QNativeAppKitTabViewController::~QNativeAppKitTabViewController()
{
}

void QNativeAppKitTabViewController::setTabViewItems(QList<QNativeAppKitTabViewItem *> list)
{
    d_func()->m_tabViewItems = list;
    nsTabViewControllerHandle().tabViewItems = @[];
    for (auto tabViewItem : list) {
        NSTabViewItem *item = tabViewItem->nsTabViewItemHandle();
        if (item.viewController)
            [nsTabViewControllerHandle() addTabViewItem:item];
        else
            qWarning() << "A QNativeAppKitTabViewItem needs a QNativeAppKitViewController set before used with a QNativeAppKitTabViewController";
    }
}

QList<QNativeAppKitTabViewItem *> QNativeAppKitTabViewController::tabViewItems() const
{
    return d_func()->m_tabViewItems;
}

NSTabViewController *QNativeAppKitTabViewController::nsTabViewControllerHandle()
{
    return static_cast<NSTabViewController *>(nsViewControllerHandle());
}

#include "moc_qnativeappkittabviewcontroller.cpp"

QT_END_NAMESPACE
