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

#include <QtNativeControls/qnativeview.h>
#include <QtNativeControls/private/qnativeview_p.h>
#include <QtNativeControls/qnativeplatformview.h>
#include <QtNativeControls/qnativeplatformbase.h>

QT_BEGIN_NAMESPACE

#define PLATFORM_VIEW dynamic_cast<QNativePlatformView *>(d_func()->m_platformBase)

QNativeViewPrivate::QNativeViewPrivate(int version)
    : QNativeBasePrivate(version)
{
}

QNativeViewPrivate::~QNativeViewPrivate()
{
}

QNativeView::QNativeView(QNativeBase *parent)
    : QNativeBase(*new QNativeViewPrivate(), parent)
{
    d_func()->connectToPlatform();
}

QNativeView::QNativeView(QNativeViewPrivate &dd, QNativeBase *parent)
    : QNativeBase(dd, parent)
{
}

QNativeView::~QNativeView()
{
}

QNativeView *QNativeView::parentView()
{
    return qobject_cast<QNativeView *>(parent());
}

bool QNativeView::visible() const
{
    return PLATFORM_VIEW->visible();
}

void QNativeView::setVisible(bool v)
{
    PLATFORM_VIEW->setVisible(v);
}

qreal QNativeView::x() const
{
    return PLATFORM_VIEW->geometry().x();
}

void QNativeView::setX(qreal x)
{
    QRectF g = PLATFORM_VIEW->geometry();
    g.moveLeft(x);
    PLATFORM_VIEW->setGeometry(g);
}

qreal QNativeView::y() const
{
    return PLATFORM_VIEW->geometry().y();
}

void QNativeView::setY(qreal y)
{
    QRectF g = PLATFORM_VIEW->geometry();
    g.moveTop(y);
    PLATFORM_VIEW->setGeometry(g);
}

qreal QNativeView::width() const
{
    return PLATFORM_VIEW->geometry().width();
}

void QNativeView::setWidth(qreal w)
{
    QRectF g = PLATFORM_VIEW->geometry();
    g.setWidth(w);
    PLATFORM_VIEW->setGeometry(g);
}

qreal QNativeView::height() const
{
    return PLATFORM_VIEW->geometry().height();
}

void QNativeView::setHeight(qreal h)
{
    QRectF g = PLATFORM_VIEW->geometry();
    g.setHeight(h);
    PLATFORM_VIEW->setGeometry(g);
}

qreal QNativeView::left() const
{
    return PLATFORM_VIEW->geometry().left();
}

qreal QNativeView::top() const
{
    return PLATFORM_VIEW->geometry().top();
}

qreal QNativeView::right() const
{
    return PLATFORM_VIEW->geometry().right();
}

qreal QNativeView::bottom() const
{
    return PLATFORM_VIEW->geometry().bottom();
}

QSizeF QNativeView::implicitSize() const
{
    return PLATFORM_VIEW->implicitSize();
}

qreal QNativeView::implicitWidth() const
{
    return PLATFORM_VIEW->implicitSize().width();
}

qreal QNativeView::implicitHeight() const
{
    return PLATFORM_VIEW->implicitSize().height();
}

void QNativeView::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    PLATFORM_VIEW->setGeometry(QRectF(posx, posy, w, h));
}

void QNativeView::move(const QPointF &pos)
{
    PLATFORM_VIEW->move(pos);
}

void QNativeView::move(qreal posx, qreal posy)
{
    PLATFORM_VIEW->move(QPointF(posx, posy));
}

void QNativeView::resize(const QSizeF size)
{
    PLATFORM_VIEW->resize(size);
}

void QNativeView::resize(qreal width, qreal height)
{
    PLATFORM_VIEW->resize(QSizeF(width, height));
}

void QNativeView::setGeometry(const QRectF &rect)
{
    PLATFORM_VIEW->setGeometry(rect);
}

QRectF QNativeView::geometry() const
{
    return PLATFORM_VIEW->geometry();
}

#include "moc_qnativeview.cpp"

QT_END_NAMESPACE

