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

#include <QtUniUIKitControls/quniuikitindexpath.h>
#include <QtUniUIKitControls/private/quniuikitindexpath_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitIndexPathPrivate::QUniUIKitIndexPathPrivate(int version)
    : QObjectPrivate(version)
{
}

QUniUIKitIndexPathPrivate::~QUniUIKitIndexPathPrivate()
{
    [m_indexPath release];
}

QUniUIKitIndexPath::QUniUIKitIndexPath(QObject *parent)
    : QObject(*new QUniUIKitIndexPathPrivate(), parent)
{
}

QUniUIKitIndexPath::QUniUIKitIndexPath(int row, int section, QObject *parent)
    : QObject(*new QUniUIKitIndexPathPrivate(), parent)
{
    d_func()->m_indexPath = [[NSIndexPath indexPathForRow:row inSection:section] retain];
}

QUniUIKitIndexPath::QUniUIKitIndexPath(NSIndexPath *indexPath, QObject *parent)
    : QObject(*new QUniUIKitIndexPathPrivate(), parent)
{
    d_func()->m_indexPath = [indexPath retain];
}

QUniUIKitIndexPath *QUniUIKitIndexPath::create(int row, int section)
{
    return new QUniUIKitIndexPath(row, section);
}

NSIndexPath *QUniUIKitIndexPath::nsIndexPathHandle()
{
    return d_func()->m_indexPath;
}

int QUniUIKitIndexPath::row() const
{
    return d_func()->m_indexPath.row;
}

int QUniUIKitIndexPath::section() const
{
    return d_func()->m_indexPath.section;
}


#include "moc_quniuikitindexpath.cpp"

QT_END_NAMESPACE

