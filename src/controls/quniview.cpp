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
#include <QtNativeControls/private/qnativeplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QNativeViewPrivate::QNativeViewPrivate(int version)
    : QNativeBasePrivate(version)
    , m_platformView(nullptr)
{
}

QNativeViewPrivate::~QNativeViewPrivate()
{
}

void QNativeViewPrivate::createPlatformView()
{
    Q_ASSERT(!m_platformView);
    m_platformView = QNativePlatformManager::platformPlugin()->createView(q_func());
    Q_ASSERT(m_platformView);
    setPlatformView(m_platformView);
}

void QNativeViewPrivate::setPlatformView(QNativePlatformView *platformView)
{
    m_platformView = platformView;
    setPlatformBase(platformView);
}

QNativeView::QNativeView(QNativeBase *parent)
    : QNativeBase(*new QNativeViewPrivate(), parent)
{
    d_func()->createPlatformView();
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
    return d_func()->m_platformView->visible();
}

void QNativeView::setVisible(bool v)
{
    d_func()->m_platformView->setVisible(v);
}

qreal QNativeView::x() const
{
    return d_func()->m_platformView->geometry().x();
}

void QNativeView::setX(qreal x)
{
    Q_D(QNativeView);
    QRectF g = d->m_platformView->geometry();
    g.moveLeft(x);
    d->m_platformView->setGeometry(g);
}

qreal QNativeView::y() const
{
    return d_func()->m_platformView->geometry().y();
}

void QNativeView::setY(qreal y)
{
    Q_D(QNativeView);
    QRectF g = d->m_platformView->geometry();
    g.moveTop(y);
    d->m_platformView->setGeometry(g);
}

qreal QNativeView::width() const
{
    return d_func()->m_platformView->geometry().width();
}

void QNativeView::setWidth(qreal w)
{
    Q_D(QNativeView);
    QRectF g = d->m_platformView->geometry();
    g.setWidth(w);
    d->m_platformView->setGeometry(g);
}

qreal QNativeView::height() const
{
    return d_func()->m_platformView->geometry().height();
}

void QNativeView::setHeight(qreal h)
{
    Q_D(QNativeView);
    QRectF g = d->m_platformView->geometry();
    g.setHeight(h);
    d->m_platformView->setGeometry(g);
}

qreal QNativeView::left() const
{
    return d_func()->m_platformView->geometry().left();
}

qreal QNativeView::top() const
{
    return d_func()->m_platformView->geometry().top();
}

qreal QNativeView::right() const
{
    return d_func()->m_platformView->geometry().right();
}

qreal QNativeView::bottom() const
{
    return d_func()->m_platformView->geometry().bottom();
}

QSizeF QNativeView::implicitSize() const
{
    return d_func()->m_platformView->implicitSize();
}

void QNativeView::setImplicitSize(const QSizeF &size)
{
    d_func()->m_platformView->setImplicitSize(size);
}

qreal QNativeView::implicitWidth() const
{
    return d_func()->m_platformView->implicitSize().width();
}

void QNativeView::setImplicitWidth(qreal width)
{
    Q_D(QNativeView);
    QSizeF size = implicitSize();
    size.setWidth(width);
    d->m_platformView->setImplicitSize(size);
}

qreal QNativeView::implicitHeight() const
{
    return d_func()->m_platformView->implicitSize().height();
}

void QNativeView::setImplicitHeight(qreal height)
{
    Q_D(QNativeView);
    QSizeF size = implicitSize();
    size.setHeight(height);
    d->m_platformView->setImplicitSize(size);
}

void QNativeView::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    d_func()->m_platformView->setGeometry(QRectF(posx, posy, w, h));
}

void QNativeView::move(const QPointF &pos)
{
    d_func()->m_platformView->move(pos);
}

void QNativeView::move(qreal posx, qreal posy)
{
    d_func()->m_platformView->move(QPointF(posx, posy));
}

void QNativeView::resize(const QSizeF size)
{
    d_func()->m_platformView->resize(size);
}

void QNativeView::resize(qreal width, qreal height)
{
    d_func()->m_platformView->resize(QSizeF(width, height));
}

void QNativeView::setGeometry(const QRectF &rect)
{
    d_func()->m_platformView->setGeometry(rect);
}

QRectF QNativeView::geometry() const
{
    return d_func()->m_platformView->geometry();
}

#include "moc_qnativeview.cpp"

QT_END_NAMESPACE

