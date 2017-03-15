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

#include <QtNativeUIKitControls/quniuikittabbaritem.h>
#include <QtNativeUIKitControls/private/quniuikittabbaritem_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitTabBarItemPrivate::QNativeUIKitTabBarItemPrivate(int version)
    : QNativeUIKitBasePrivate(version)
    , m_tabBarItem(nullptr)
{
}

QNativeUIKitTabBarItemPrivate::~QNativeUIKitTabBarItemPrivate()
{
}

UITabBarItem *QNativeUIKitTabBarItemPrivate::tabBarItem()
{
    if (!m_tabBarItem)
        m_tabBarItem = [[UITabBarItem alloc] initWithTitle:@"" image:nil tag:1];
    return m_tabBarItem;
}

UITabBarItem *QNativeUIKitTabBarItem::uiTabBarItemHandle()
{
    return d_func()->tabBarItem();
}

QNativeUIKitTabBarItem::QNativeUIKitTabBarItem(QNativeUIKitBase *parent)
    : QNativeUIKitBase(*new QNativeUIKitTabBarItemPrivate(), parent)
{
}

QNativeUIKitTabBarItem::QNativeUIKitTabBarItem(const QString &title, QNativeUIKitBase *parent)
    : QNativeUIKitBase(*new QNativeUIKitTabBarItemPrivate(), parent)
{
    setTitle(title);
}

QNativeUIKitTabBarItem::QNativeUIKitTabBarItem(QNativeUIKitTabBarItemPrivate &dd, QNativeUIKitBase *parent)
    : QNativeUIKitBase(dd, parent)
{
}

QNativeUIKitTabBarItem::~QNativeUIKitTabBarItem()
{
}

QString QNativeUIKitTabBarItem::title() const
{
    return QString::fromNSString(const_cast<QNativeUIKitTabBarItem *>(this)->uiTabBarItemHandle().title);
}

void QNativeUIKitTabBarItem::setTitle(const QString &title)
{
    uiTabBarItemHandle().title = title.toNSString();
}

#include "moc_quniuikittabbaritem.cpp"

QT_END_NAMESPACE
