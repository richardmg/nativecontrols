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
    const auto b = static_cast<QNativeControl *>(base);
    q->connect(q, &QNativeUIKitControl::visibleChanged, b, &QNativeControl::visibleChanged);
    q->connect(q, &QNativeUIKitControl::xChanged, b, &QNativeControl::xChanged);
    q->connect(q, &QNativeUIKitControl::xChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeUIKitControl::yChanged, b, &QNativeControl::yChanged);
    q->connect(q, &QNativeUIKitControl::yChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeUIKitControl::widthChanged, b, &QNativeControl::widthChanged);
    q->connect(q, &QNativeUIKitControl::widthChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeUIKitControl::heightChanged, b, &QNativeControl::heightChanged);
    q->connect(q, &QNativeUIKitControl::heightChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeUIKitControl::implicitWidthChanged, b, &QNativeControl::implicitWidthChanged);
    q->connect(q, &QNativeUIKitControl::implicitHeightChanged, b, &QNativeControl::implicitHeightChanged);
}

void QNativeUIKitControlPrivate::updateLayout(bool recursive)
{
    Q_Q(QNativeUIKitControl);

    if (!testAttribute(Resized)) {
        q->resize(m_implicitSize);
        setAttribute(Resized, false);
    }

    if (recursive) {
        for (QObject *child : q->children())
            static_cast<QNativeUIKitBasePrivate *>(QObjectPrivate::get(child))->updateLayout(recursive);
    }
}

void QNativeUIKitControlPrivate::updateImplicitSize()
{
    Q_Q(QNativeUIKitControl);
    QSizeF oldSize = m_implicitSize;
    m_implicitSize = q->implicitSize();

    if (m_implicitSize.width() != oldSize.width()) {
        updateLayout(false);
        emit q->implicitWidthChanged(m_implicitSize.width());
    }

    if (m_implicitSize.height() != oldSize.height()) {
        updateLayout(false);
        emit q->implicitHeightChanged(m_implicitSize.height());
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

QSizeF QNativeUIKitControl::implicitSize() const
{
    return QSizeF::fromCGSize([d_func()->view() sizeThatFits:CGSizeZero]);
}

qreal QNativeUIKitControl::implicitWidth() const
{
    return implicitSize().width();
}

qreal QNativeUIKitControl::implicitHeight() const
{
    return implicitSize().height();
}

QRectF QNativeUIKitControl::geometry() const
{
    return QRectF::fromCGRect(d_func()->alignmentRect());
}

QRectF QNativeUIKitControl::frameGeometry() const
{
    return QRectF::fromCGRect(d_func()->view().frame);
}

void QNativeUIKitControlPrivate::setGeometry(const QRectF &rect)
{
    setAlignmentRect(rect.toCGRect());
}

qreal QNativeUIKitControl::x() const
{
    return geometry().x();
}

void QNativeUIKitControl::setX(qreal newX)
{
    if (newX == x())
        return;

    Q_D(QNativeUIKitControl);
    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitControlPrivate::Moved);

    emit xChanged(newX);
}

qreal QNativeUIKitControl::y() const
{
    return geometry().y();
}

void QNativeUIKitControl::setY(qreal newY)
{
    if (newY == y())
        return;

    Q_D(QNativeUIKitControl);
    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitControlPrivate::Moved);

    emit yChanged(newY);
}

qreal QNativeUIKitControl::width() const
{
    return geometry().width();
}

void QNativeUIKitControl::setWidth(qreal newWidth)
{
    if (newWidth == width())
        return;

    Q_D(QNativeUIKitControl);
    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitControlPrivate::Resized);

    emit widthChanged(newWidth);
}

qreal QNativeUIKitControl::height() const
{
    return geometry().height();
}

void QNativeUIKitControl::setHeight(qreal newHeight)
{
    if (newHeight == height())
        return;

    Q_D(QNativeUIKitControl);
    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitControlPrivate::Resized);

    emit heightChanged(newHeight);
}

#include "moc_qnativeuikitcontrol.cpp"

QT_END_NAMESPACE
