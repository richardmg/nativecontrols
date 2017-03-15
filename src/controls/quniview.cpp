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

#include <QtNativeControls/quniview.h>
#include <QtNativeControls/private/quniview_p.h>
#include <QtNativeControls/quniplatformview.h>
#include <QtNativeControls/quniplatformbase.h>
#include <QtNativeControls/private/quniplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QUniViewPrivate::QUniViewPrivate(int version)
    : QUniBasePrivate(version)
    , m_platformView(nullptr)
{
}

QUniViewPrivate::~QUniViewPrivate()
{
}

void QUniViewPrivate::createPlatformView()
{
    Q_ASSERT(!m_platformView);
    m_platformView = QUniPlatformManager::platformPlugin()->createView(q_func());
    Q_ASSERT(m_platformView);
    setPlatformView(m_platformView);
}

void QUniViewPrivate::setPlatformView(QUniPlatformView *platformView)
{
    m_platformView = platformView;
    setPlatformBase(platformView);
}

QUniView::QUniView(QUniBase *parent)
    : QUniBase(*new QUniViewPrivate(), parent)
{
    d_func()->createPlatformView();
}

QUniView::QUniView(QUniViewPrivate &dd, QUniBase *parent)
    : QUniBase(dd, parent)
{
}

QUniView::~QUniView()
{
}

QUniView *QUniView::parentView()
{
    return qobject_cast<QUniView *>(parent());
}

bool QUniView::visible() const
{
    return d_func()->m_platformView->visible();
}

void QUniView::setVisible(bool v)
{
    d_func()->m_platformView->setVisible(v);
}

qreal QUniView::x() const
{
    return d_func()->m_platformView->geometry().x();
}

void QUniView::setX(qreal x)
{
    Q_D(QUniView);
    QRectF g = d->m_platformView->geometry();
    g.moveLeft(x);
    d->m_platformView->setGeometry(g);
}

qreal QUniView::y() const
{
    return d_func()->m_platformView->geometry().y();
}

void QUniView::setY(qreal y)
{
    Q_D(QUniView);
    QRectF g = d->m_platformView->geometry();
    g.moveTop(y);
    d->m_platformView->setGeometry(g);
}

qreal QUniView::width() const
{
    return d_func()->m_platformView->geometry().width();
}

void QUniView::setWidth(qreal w)
{
    Q_D(QUniView);
    QRectF g = d->m_platformView->geometry();
    g.setWidth(w);
    d->m_platformView->setGeometry(g);
}

qreal QUniView::height() const
{
    return d_func()->m_platformView->geometry().height();
}

void QUniView::setHeight(qreal h)
{
    Q_D(QUniView);
    QRectF g = d->m_platformView->geometry();
    g.setHeight(h);
    d->m_platformView->setGeometry(g);
}

qreal QUniView::left() const
{
    return d_func()->m_platformView->geometry().left();
}

qreal QUniView::top() const
{
    return d_func()->m_platformView->geometry().top();
}

qreal QUniView::right() const
{
    return d_func()->m_platformView->geometry().right();
}

qreal QUniView::bottom() const
{
    return d_func()->m_platformView->geometry().bottom();
}

QSizeF QUniView::implicitSize() const
{
    return d_func()->m_platformView->implicitSize();
}

void QUniView::setImplicitSize(const QSizeF &size)
{
    d_func()->m_platformView->setImplicitSize(size);
}

qreal QUniView::implicitWidth() const
{
    return d_func()->m_platformView->implicitSize().width();
}

void QUniView::setImplicitWidth(qreal width)
{
    Q_D(QUniView);
    QSizeF size = implicitSize();
    size.setWidth(width);
    d->m_platformView->setImplicitSize(size);
}

qreal QUniView::implicitHeight() const
{
    return d_func()->m_platformView->implicitSize().height();
}

void QUniView::setImplicitHeight(qreal height)
{
    Q_D(QUniView);
    QSizeF size = implicitSize();
    size.setHeight(height);
    d->m_platformView->setImplicitSize(size);
}

void QUniView::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    d_func()->m_platformView->setGeometry(QRectF(posx, posy, w, h));
}

void QUniView::move(const QPointF &pos)
{
    d_func()->m_platformView->move(pos);
}

void QUniView::move(qreal posx, qreal posy)
{
    d_func()->m_platformView->move(QPointF(posx, posy));
}

void QUniView::resize(const QSizeF size)
{
    d_func()->m_platformView->resize(size);
}

void QUniView::resize(qreal width, qreal height)
{
    d_func()->m_platformView->resize(QSizeF(width, height));
}

void QUniView::setGeometry(const QRectF &rect)
{
    d_func()->m_platformView->setGeometry(rect);
}

QRectF QUniView::geometry() const
{
    return d_func()->m_platformView->geometry();
}

#include "moc_quniview.cpp"

QT_END_NAMESPACE

