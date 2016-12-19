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

#include <QtNativeControls/qnativecontrol.h>
#include <QtNativeControls/private/qnativecontrol_p.h>
#include <QtNativeControls/qnativeplatformcontrol.h>

QT_BEGIN_NAMESPACE

#define PLATFORM_CONTROL dynamic_cast<QNativePlatformControl *>(d_func()->m_platformBase)

QNativeControlPrivate::QNativeControlPrivate(int version)
    : QNativeBasePrivate(version)
{
}

QNativeControlPrivate::~QNativeControlPrivate()
{
}

QNativeControl::QNativeControl(QNativeBase *parent)
    : QNativeBase(parent)
{
    d_func()->connectToPlatform();
}

QNativeControl::QNativeControl(QNativeControlPrivate &dd, QObject *parent)
    : QNativeBase(dd, parent)
{
}

QNativeControl::~QNativeControl()
{
}

bool QNativeControl::visible() const
{
    return PLATFORM_CONTROL->visible();
}

void QNativeControl::setVisible(bool v)
{
    PLATFORM_CONTROL->setVisible(v);
}

qreal QNativeControl::x() const
{
    return PLATFORM_CONTROL->geometry().x();
}

void QNativeControl::setX(qreal x)
{
    QRectF g = PLATFORM_CONTROL->geometry();
    g.setX(x);
    PLATFORM_CONTROL->setGeometry(g);
}

qreal QNativeControl::y() const
{
    return PLATFORM_CONTROL->geometry().y();
}

void QNativeControl::setY(qreal y)
{
    QRectF g = PLATFORM_CONTROL->geometry();
    g.setY(y);
    PLATFORM_CONTROL->setGeometry(g);
}

qreal QNativeControl::width() const
{
    return PLATFORM_CONTROL->geometry().width();
}

void QNativeControl::setWidth(qreal w)
{
    QRectF g = PLATFORM_CONTROL->geometry();
    g.setWidth(w);
    PLATFORM_CONTROL->setGeometry(g);
}

qreal QNativeControl::height() const
{
    return PLATFORM_CONTROL->geometry().height();
}

void QNativeControl::setHeight(qreal h)
{
    QRectF g = PLATFORM_CONTROL->geometry();
    g.setHeight(h);
    PLATFORM_CONTROL->setGeometry(g);
}

void QNativeControl::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    PLATFORM_CONTROL->setGeometry(QRectF(posx, posy, w, h));
}

void QNativeControl::setGeometry(const QRectF &rect)
{
    PLATFORM_CONTROL->setGeometry(rect);
}

QRectF QNativeControl::geometry() const
{
    return PLATFORM_CONTROL->geometry();
}

#include "moc_qnativecontrol.cpp"

QT_END_NAMESPACE
