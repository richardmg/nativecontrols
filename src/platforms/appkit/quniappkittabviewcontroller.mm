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

#include <QtNativeAppKitControls/quniappkittabviewcontroller.h>
#include <QtNativeAppKitControls/private/quniappkittabviewcontroller_p.h>
#include <QtNativeAppKitControls/quniappkittabviewitem.h>
#include <QtNativeAppKitControls/private/quniappkittabviewitem_p.h>

QT_BEGIN_NAMESPACE

QUniAppKitTabViewControllerPrivate::QUniAppKitTabViewControllerPrivate(int version)
    : QUniAppKitViewControllerPrivate(version)
{
}

QUniAppKitTabViewControllerPrivate::~QUniAppKitTabViewControllerPrivate()
{
}

NSViewController *QUniAppKitTabViewControllerPrivate::createViewController()
{
    return [NSTabViewController new];
}

QUniAppKitTabViewController::QUniAppKitTabViewController(QUniAppKitBase *parent)
    : QUniAppKitViewController(*new QUniAppKitTabViewControllerPrivate(), parent)
{
}

QUniAppKitTabViewController::QUniAppKitTabViewController(QUniAppKitTabViewControllerPrivate &dd, QUniAppKitBase *parent)
    :QUniAppKitViewController(dd, parent)
{
}

QUniAppKitTabViewController::~QUniAppKitTabViewController()
{
}

QUniAppKitView *QUniAppKitTabViewController::view() const
{
    qWarning("NSTabViewController doesn't use a view. Calling QUniAppKitTabViewController::view() will not work for a NSTabViewController!");
    return QUniAppKitViewController::view();
}

void QUniAppKitTabViewController::setTabViewItems(QList<QUniAppKitTabViewItem *> list)
{
    d_func()->m_tabViewItems = list;
    nsTabViewControllerHandle().childViewControllers = @[];
    nsTabViewControllerHandle().tabViewItems = @[];
    for (auto tabViewItem : list) {
        NSTabViewItem *item = tabViewItem->nsTabViewItemHandle();
        if (item.viewController)
            [nsTabViewControllerHandle() addTabViewItem:item];
        else
            qWarning() << "A QUniAppKitTabViewItem needs a QUniAppKitViewController set before used with a QUniAppKitTabViewController";
    }
}

QList<QUniAppKitTabViewItem *> QUniAppKitTabViewController::tabViewItems() const
{
    return d_func()->m_tabViewItems;
}

NSTabViewController *QUniAppKitTabViewController::nsTabViewControllerHandle()
{
    return static_cast<NSTabViewController *>(nsViewControllerHandle());
}

#include "moc_quniappkittabviewcontroller.cpp"

QT_END_NAMESPACE
