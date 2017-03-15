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

QUniAppKitTabViewItemPrivate::QUniAppKitTabViewItemPrivate(int version)
    : QUniAppKitBasePrivate(version)
    , m_tabViewItem(nullptr)
    , m_viewController(nullptr)
{
}

QUniAppKitTabViewItemPrivate::~QUniAppKitTabViewItemPrivate()
{
}

NSTabViewItem *QUniAppKitTabViewItemPrivate::tabViewItem()
{
    if (!m_tabViewItem)
        m_tabViewItem = [[NSTabViewItem alloc] initWithIdentifier:nil];
    return m_tabViewItem;
}

NSTabViewItem *QUniAppKitTabViewItem::nsTabViewItemHandle()
{
    return d_func()->tabViewItem();
}

QUniAppKitTabViewItem::QUniAppKitTabViewItem(QUniAppKitBase *parent)
    : QUniAppKitBase(*new QUniAppKitTabViewItemPrivate(), parent)
{
    if (QUniAppKitViewController *vc = qobject_cast<QUniAppKitViewController *>(parent))
        setViewController(vc);
}

QUniAppKitTabViewItem::QUniAppKitTabViewItem(const QString &title, QUniAppKitBase *parent)
    : QUniAppKitBase(*new QUniAppKitTabViewItemPrivate(), parent)
{
    if (QUniAppKitViewController *vc = qobject_cast<QUniAppKitViewController *>(parent))
        setViewController(vc);
    setTitle(title);
}

QUniAppKitTabViewItem::QUniAppKitTabViewItem(QUniAppKitTabViewItemPrivate &dd, QUniAppKitBase *parent)
    : QUniAppKitBase(dd, parent)
{
}

QUniAppKitTabViewItem::~QUniAppKitTabViewItem()
{
}

QString QUniAppKitTabViewItem::title() const
{
    return QString::fromNSString(const_cast<QUniAppKitTabViewItem *>(this)->nsTabViewItemHandle().label);
}

void QUniAppKitTabViewItem::setTitle(const QString &title)
{
    nsTabViewItemHandle().label = title.toNSString();
}

void QUniAppKitTabViewItem::setViewController(QUniAppKitViewController *viewController)
{
    d_func()->m_viewController = viewController;
    nsTabViewItemHandle().viewController = viewController->nsViewControllerHandle();
}

QUniAppKitViewController *QUniAppKitTabViewItem::viewController() const
{
    return d_func()->m_viewController;
}

#include "moc_quniappkittabviewitem.cpp"

QT_END_NAMESPACE
