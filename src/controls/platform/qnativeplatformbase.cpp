/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native Controls module of the Qt Toolkit.
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

#include <QtNativeControls/private/qnativeplatformbase_p.h>
#include <QtNativeControls/qnativeplatformbase.h>

QT_BEGIN_NAMESPACE

QNativePlatformBasePrivate::QNativePlatformBasePrivate(int version)
    : QNativeQObjectBasePrivate(version)
{
}

QNativePlatformBasePrivate::~QNativePlatformBasePrivate()
{
}

QNativePlatformBase::QNativePlatformBase(QNativePlatformBase *parent)
    : QNativeQObjectBase(*new QNativePlatformBasePrivate(), parent)
{
}

QNativePlatformBase::QNativePlatformBase(QNativePlatformBasePrivate &dd, QNativePlatformBase *parent)
    : QNativeQObjectBase(dd, parent)
{
}

QNativePlatformBase::~QNativePlatformBase()
{
}

void QNativePlatformBase::setParent(QNativePlatformBase *parent)
{
    QNativeQObjectBase::setParent(parent);
}

void QNativePlatformBase::setParent(QNativeBase *parent)
{
    // For API simplicity, we allow setting a QNativeBase as a child
    // of a QNativePlatformBase. But for it to work, we need to use
    // the QNativePlatformBase that backs the QNativeBase as the actual parent.
    setParent(dynamic_cast<QNativePlatformBase *>(parent->platformHandle()));
}

#include "moc_qnativeplatformbase.cpp"

QT_END_NAMESPACE