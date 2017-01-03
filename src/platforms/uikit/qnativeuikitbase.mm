/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
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

#include <QtNativeControls/qnativebase.h>
#include <QtNativeUIKitControls/qnativeuikitbase.h>
#include <QtNativeUIKitControls/private/qnativeuikitbase_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitBasePrivate::QNativeUIKitBasePrivate(int version)
    : QObjectPrivate(version)
    , m_attributes(0)
    , m_view(nil)
{
}

QNativeUIKitBasePrivate::~QNativeUIKitBasePrivate()
{
    [m_view release];
}

UIView *QNativeUIKitBasePrivate::view()
{
    return m_view;
}

UIView *QNativeUIKitBasePrivate::view() const
{
    return m_view;
}

void QNativeUIKitBasePrivate::setView(UIView *view)
{
    [m_view release];
    m_view = [view retain];
}

void QNativeUIKitBasePrivate::connectSignals(QNativeBase *)
{
}

QNativeUIKitBase::QNativeUIKitBase(QObject *parent)
    : QObject(*new QNativeUIKitBasePrivate(), parent)
{
}

QNativeUIKitBase::QNativeUIKitBase(QNativeUIKitBasePrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

QNativeUIKitBase::~QNativeUIKitBase()
{
}

void QNativeUIKitBase::setPlatformParent(QNativePlatformBase *parent)
{
    setParent(dynamic_cast<QNativeUIKitBase *>(parent));
}

void QNativeUIKitBase::childEvent(QChildEvent *event)
{
    Q_D(QNativeUIKitBase);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QNativeUIKitBasePrivate *dptr_child = dynamic_cast<QNativeUIKitBasePrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    if (event->added())
        [d->view() addSubview:dptr_child->view()];
    else if (event->removed())
        [dptr_child->view() removeFromSuperview];
}

#include "moc_qnativeuikitbase.cpp"

QT_END_NAMESPACE
