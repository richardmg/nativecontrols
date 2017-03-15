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

#include <QtNativeAppKitControls/quniappkittabviewitem.h>
#include <QtNativeAppKitControls/private/quniappkittabviewitem_p.h>
#include <QtNativeAppKitControls/quniappkitviewcontroller.h>

QT_BEGIN_NAMESPACE

QNativeAppKitTabViewItemPrivate::QNativeAppKitTabViewItemPrivate(int version)
    : QNativeAppKitBasePrivate(version)
    , m_tabViewItem(nullptr)
    , m_viewController(nullptr)
{
}

QNativeAppKitTabViewItemPrivate::~QNativeAppKitTabViewItemPrivate()
{
}

NSTabViewItem *QNativeAppKitTabViewItemPrivate::tabViewItem()
{
    if (!m_tabViewItem)
        m_tabViewItem = [[NSTabViewItem alloc] initWithIdentifier:nil];
    return m_tabViewItem;
}

NSTabViewItem *QNativeAppKitTabViewItem::nsTabViewItemHandle()
{
    return d_func()->tabViewItem();
}

QNativeAppKitTabViewItem::QNativeAppKitTabViewItem(QNativeAppKitBase *parent)
    : QNativeAppKitBase(*new QNativeAppKitTabViewItemPrivate(), parent)
{
    if (QNativeAppKitViewController *vc = qobject_cast<QNativeAppKitViewController *>(parent))
        setViewController(vc);
}

QNativeAppKitTabViewItem::QNativeAppKitTabViewItem(const QString &title, QNativeAppKitBase *parent)
    : QNativeAppKitBase(*new QNativeAppKitTabViewItemPrivate(), parent)
{
    if (QNativeAppKitViewController *vc = qobject_cast<QNativeAppKitViewController *>(parent))
        setViewController(vc);
    setTitle(title);
}

QNativeAppKitTabViewItem::QNativeAppKitTabViewItem(QNativeAppKitTabViewItemPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitBase(dd, parent)
{
}

QNativeAppKitTabViewItem::~QNativeAppKitTabViewItem()
{
}

QString QNativeAppKitTabViewItem::title() const
{
    return QString::fromNSString(const_cast<QNativeAppKitTabViewItem *>(this)->nsTabViewItemHandle().label);
}

void QNativeAppKitTabViewItem::setTitle(const QString &title)
{
    nsTabViewItemHandle().label = title.toNSString();
}

void QNativeAppKitTabViewItem::setViewController(QNativeAppKitViewController *viewController)
{
    d_func()->m_viewController = viewController;
    nsTabViewItemHandle().viewController = viewController->nsViewControllerHandle();
}

QNativeAppKitViewController *QNativeAppKitTabViewItem::viewController() const
{
    return d_func()->m_viewController;
}

#include "moc_quniappkittabviewitem.cpp"

QT_END_NAMESPACE
