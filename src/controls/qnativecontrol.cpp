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

#include <QtNativeControls/qnativecontrol.h>
#include <QtNativeControls/private/qnativecontrol_p.h>
#include <QtNativeControls/qnativeplatformcontrol.h>
#include <QtNativeControls/qnativeview.h>

QT_BEGIN_NAMESPACE

#define PLATFORM_CONTROL dynamic_cast<QNativePlatformControl *>(d_func()->m_platformBase)

QNativeControlPrivate::QNativeControlPrivate(int version)
    : QNativeViewPrivate(version)
{
}

QNativeControlPrivate::~QNativeControlPrivate()
{
}

QNativeControl::QNativeControl(QNativeBase *parent)
    : QNativeView(parent)
{
    d_func()->connectToPlatform();
}

QNativeControl::QNativeControl(QNativeControlPrivate &dd, QNativeBase *parent)
    : QNativeView(dd, parent)
{
}

QNativeControl::~QNativeControl()
{
}

QNativeControl *QNativeControl::parentControl()
{
    return qobject_cast<QNativeControl *>(parent());
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
    g.moveLeft(x);
    PLATFORM_CONTROL->setGeometry(g);
}

qreal QNativeControl::y() const
{
    return PLATFORM_CONTROL->geometry().y();
}

void QNativeControl::setY(qreal y)
{
    QRectF g = PLATFORM_CONTROL->geometry();
    g.moveTop(y);
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

qreal QNativeControl::left() const
{
    return PLATFORM_CONTROL->geometry().left();
}

qreal QNativeControl::top() const
{
    return PLATFORM_CONTROL->geometry().top();
}

qreal QNativeControl::right() const
{
    return PLATFORM_CONTROL->geometry().right();
}

qreal QNativeControl::bottom() const
{
    return PLATFORM_CONTROL->geometry().bottom();
}

QSizeF QNativeControl::implicitSize() const
{
    return PLATFORM_CONTROL->implicitSize();
}

qreal QNativeControl::implicitWidth() const
{
    return PLATFORM_CONTROL->implicitSize().width();
}

qreal QNativeControl::implicitHeight() const
{
    return PLATFORM_CONTROL->implicitSize().height();
}

void QNativeControl::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    PLATFORM_CONTROL->setGeometry(QRectF(posx, posy, w, h));
}

void QNativeControl::move(const QPointF &pos)
{
    PLATFORM_CONTROL->move(pos);
}

void QNativeControl::move(qreal posx, qreal posy)
{
    PLATFORM_CONTROL->move(QPointF(posx, posy));
}

void QNativeControl::resize(const QSizeF size)
{
    PLATFORM_CONTROL->resize(size);
}

void QNativeControl::resize(qreal width, qreal height)
{
    PLATFORM_CONTROL->resize(QSizeF(width, height));
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
