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

#include <QtNativeControls/qnativecontrol.h>
#include <QtNativeUIKitControls/qnativeuikitcontrol.h>
#include <QtNativeUIKitControls/private/qnativeuikitcontrol_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitControlPrivate::QNativeUIKitControlPrivate(int version)
    : QNativeUIKitBasePrivate(version)
{
}

QNativeUIKitControlPrivate::~QNativeUIKitControlPrivate()
{
}

void QNativeUIKitControlPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeUIKitControl);
    QNativeUIKitBasePrivate::connectSignals(base);
    q->connect(q, SIGNAL(visibleChanged(bool)), base, SIGNAL(visibleChanged(bool)));
    q->connect(q, SIGNAL(xChanged(qreal)), base, SIGNAL(xChanged(qreal)));
    q->connect(q, SIGNAL(yChanged(qreal)), base, SIGNAL(yChanged(qreal)));
    q->connect(q, SIGNAL(widthChanged(qreal)), base, SIGNAL(widthChanged(qreal)));
    q->connect(q, SIGNAL(heightChanged(qreal)), base, SIGNAL(heightChanged(qreal)));
}

void QNativeUIKitControlPrivate::updateLayout(bool recursive)
{
    if (testAttribute(LayedOut))
        return;
    setAttribute(LayedOut);

    if (!testAttribute(Resized))
        [view() sizeToFit];

    if (recursive) {
        for (QObject *child : q_func()->children())
            static_cast<QNativeUIKitBasePrivate *>(QObjectPrivate::get(child))->updateLayout(recursive);
    }
}

QNativeUIKitControl::QNativeUIKitControl(QNativeUIKitBase *parent)
    : QNativeUIKitBase(*new QNativeUIKitControlPrivate(), parent)
{
    setParent(parent);
}

QNativeUIKitControl::QNativeUIKitControl(QNativeUIKitControlPrivate &dd, QNativeUIKitBase *parent)
    : QNativeUIKitBase(dd, parent)
{
}

QNativeUIKitControl::~QNativeUIKitControl()
{
}

void QNativeUIKitControl::setParent(QNativeUIKitBase *parent)
{
    // Overloading setParent to force client to use
    // QNativeUIKitBase as parent for QNativeUIKitControls
    QNativeUIKitBase::setParent(parent);
}

bool QNativeUIKitControl::visible() const
{
    return !d_func()->view().hidden;
}

void QNativeUIKitControl::setVisible(bool newVisible)
{
    if (newVisible == visible())
        return;

    Q_D(QNativeUIKitControl);
    d->view().hidden = !newVisible;

    emit visibleChanged(newVisible);
}

void QNativeUIKitControl::setGeometry(const QRectF &rect)
{
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

void QNativeUIKitControl::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    setX(posx);
    setY(posy);
    setWidth(w);
    setHeight(h);
}

void QNativeUIKitControl::move(qreal posx, qreal posy)
{
    setX(posx);
    setY(posy);
}

void QNativeUIKitControl::move(const QPointF &pos)
{
    setX(pos.x());
    setY(pos.y());
}

void QNativeUIKitControl::resize(qreal width, qreal height)
{
    setWidth(width);
    setHeight(height);
}

void QNativeUIKitControl::resize(const QSizeF size)
{
    setWidth(size.width());
    setHeight(size.height());
}

QRectF QNativeUIKitControl::geometry() const
{
    return QRectF::fromCGRect(d_func()->view().frame);
}

qreal QNativeUIKitControl::x() const
{
    return d_func()->view().frame.origin.x;
}

void QNativeUIKitControl::setX(qreal newX)
{
    if (newX == x())
        return;

    Q_D(QNativeUIKitControl);
    CGRect frame = d->view().frame;
    frame.origin.x = newX;
    d->view().frame = frame;
    d->setAttribute(QNativeUIKitControlPrivate::Moved);

    emit xChanged(newX);
}

qreal QNativeUIKitControl::y() const
{
    return d_func()->view().frame.origin.y;
}

void QNativeUIKitControl::setY(qreal newY)
{
    if (newY == y())
        return;

    Q_D(QNativeUIKitControl);
    CGRect frame = d->view().frame;
    frame.origin.y = newY;
    d->view().frame = frame;
    d->setAttribute(QNativeUIKitControlPrivate::Moved);

    emit yChanged(newY);
}

qreal QNativeUIKitControl::width() const
{
    return d_func()->view().frame.size.width;
}

void QNativeUIKitControl::setWidth(qreal newWidth)
{
    if (newWidth == width())
        return;

    Q_D(QNativeUIKitControl);
    CGRect frame = d->view().frame;
    frame.size.width = newWidth;
    d->view().frame = frame;
    d->setAttribute(QNativeUIKitControlPrivate::Resized);

    emit widthChanged(newWidth);
}

qreal QNativeUIKitControl::height() const
{
    return d_func()->view().frame.size.height;
}

void QNativeUIKitControl::setHeight(qreal newHeight)
{
    if (newHeight == height())
        return;

    Q_D(QNativeUIKitControl);
    CGRect frame = d->view().frame;
    frame.size.height = newHeight;
    d->view().frame = frame;
    d->setAttribute(QNativeUIKitControlPrivate::Resized);

    emit heightChanged(newHeight);
}

#include "moc_qnativeuikitcontrol.cpp"

QT_END_NAMESPACE
