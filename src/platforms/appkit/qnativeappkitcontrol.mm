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

#include <AppKit/AppKit.h>

#include <QtCore>

#include <QtNativeControls/qnativecontrol.h>
#include <QtNativeAppKitControls/qnativeappkitcontrol.h>
#include <QtNativeAppKitControls/private/qnativeappkitcontrol_p.h>

QT_BEGIN_NAMESPACE

QRectF qt_mac_flipRect(const NSRect &rect, NSView *view);

static qreal qt_mac_flipYCoordinate(qreal y, qreal height, NSView *view)
{
    if (view.superview && !view.superview.isFlipped)
        return view.superview.frame.size.height - (y + height);
    return y;
}

static NSRect qt_mac_flipRect(const QRectF &rect, NSView *view)
{
    return NSMakeRect(rect.x(),
                      qt_mac_flipYCoordinate(rect.y(), rect.height(), view),
                      rect.width(),
                      rect.height());
}

QRectF qt_mac_flipRect(const NSRect &rect, NSView *view)
{
    return QRectF(rect.origin.x,
                  qt_mac_flipYCoordinate(rect.origin.y, rect.size.height, view),
                  rect.size.width,
                  rect.size.height);
}

QNativeAppKitControlPrivate::QNativeAppKitControlPrivate(int version)
    : QNativeAppKitBasePrivate(version)
{
}

QNativeAppKitControlPrivate::~QNativeAppKitControlPrivate()
{
}

void QNativeAppKitControlPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeAppKitControl);
    QNativeAppKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QNativeControl *>(base);
    q->connect(q, &QNativeAppKitControl::visibleChanged, b, &QNativeControl::visibleChanged);
    q->connect(q, &QNativeAppKitControl::xChanged, b, &QNativeControl::xChanged);
    q->connect(q, &QNativeAppKitControl::xChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeAppKitControl::yChanged, b, &QNativeControl::yChanged);
    q->connect(q, &QNativeAppKitControl::yChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeAppKitControl::widthChanged, b, &QNativeControl::widthChanged);
    q->connect(q, &QNativeAppKitControl::widthChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeAppKitControl::heightChanged, b, &QNativeControl::heightChanged);
    q->connect(q, &QNativeAppKitControl::heightChanged, b, &QNativeControl::bottomChanged);
}

void QNativeAppKitControlPrivate::updateLayout(bool recursive)
{
    if (testAttribute(LayedOut))
        return;
    setAttribute(LayedOut);

    if (!testAttribute(Resized)) {
        NSControl *control = (NSControl *)view();
        if ([control isKindOfClass:[NSControl class]]) {
            const NSRect oldFrame = control.frame;
            [control sizeToFit];
            if (control.superview && !control.superview.isFlipped) {
                NSRect newFrame = control.frame;
                newFrame.origin.y -= newFrame.size.height - oldFrame.size.height;
                control.frame = newFrame;
            }
        }
    }

    if (recursive) {
        for (QObject *child : q_func()->children())
            static_cast<QNativeAppKitBasePrivate *>(QObjectPrivate::get(child))->updateLayout(recursive);
    }
}



QNativeAppKitControl::QNativeAppKitControl(QNativeAppKitBase *parent)
    : QNativeAppKitBase(*new QNativeAppKitControlPrivate(), parent)
{
    setParent(parent);
}

QNativeAppKitControl::QNativeAppKitControl(QNativeAppKitControlPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitBase(dd, parent)
{
}

QNativeAppKitControl::~QNativeAppKitControl()
{
}

void QNativeAppKitControl::setParent(QNativeAppKitBase *parent)
{
    // Overloading setParent to force client to use
    // QNativeAppKitBase as parent for QNativeAppKitControls
    QNativeAppKitBase::setParent(parent);
}

bool QNativeAppKitControl::visible() const
{
    return !d_func()->view().hidden;
}

void QNativeAppKitControl::setVisible(bool newVisible)
{
    if (newVisible == visible())
        return;

    Q_D(QNativeAppKitControl);
    d->view().hidden = !newVisible;

    emit visibleChanged(newVisible);
}

void QNativeAppKitControl::setGeometry(const QRectF &rect)
{
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

void QNativeAppKitControl::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    setX(posx);
    setY(posy);
    setWidth(w);
    setHeight(h);
}

void QNativeAppKitControl::move(qreal posx, qreal posy)
{
    setX(posx);
    setY(posy);
}

void QNativeAppKitControl::move(const QPointF &pos)
{
    setX(pos.x());
    setY(pos.y());
}

void QNativeAppKitControl::resize(qreal width, qreal height)
{
    setWidth(width);
    setHeight(height);
}

void QNativeAppKitControl::resize(const QSizeF size)
{
    setWidth(size.width());
    setHeight(size.height());
}

QRectF QNativeAppKitControl::geometry() const
{
    return qt_mac_flipRect(d_func()->alignmentRect(), d_func()->view());
}

QRectF QNativeAppKitControl::frameGeometry() const
{
    return qt_mac_flipRect(d_func()->view().frame, d_func()->view());
}

void QNativeAppKitControlPrivate::setGeometry(const QRectF &rect)
{
    setAlignmentRect(qt_mac_flipRect(rect, view()));
}

qreal QNativeAppKitControl::x() const
{
    return geometry().x();
}

void QNativeAppKitControl::setX(qreal newX)
{
    if (newX == x())
        return;

    Q_D(QNativeAppKitControl);
    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitControlPrivate::Moved);

    emit xChanged(newX);
}

qreal QNativeAppKitControl::y() const
{
    return geometry().y();
}

void QNativeAppKitControl::setY(qreal newY)
{
    if (newY == y())
        return;

    Q_D(QNativeAppKitControl);
    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitControlPrivate::Moved);

    emit yChanged(newY);
}

qreal QNativeAppKitControl::width() const
{
    return geometry().width();
}

void QNativeAppKitControl::setWidth(qreal newWidth)
{
    if (newWidth == width())
        return;

    Q_D(QNativeAppKitControl);
    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitControlPrivate::Resized);

    emit widthChanged(newWidth);
}

qreal QNativeAppKitControl::height() const
{
    return geometry().height();
}

void QNativeAppKitControl::setHeight(qreal newHeight)
{
    if (newHeight == height())
        return;

    Q_D(QNativeAppKitControl);
    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitControlPrivate::Resized);

    emit heightChanged(newHeight);
}

#include "moc_qnativeappkitcontrol.cpp"

QT_END_NAMESPACE
