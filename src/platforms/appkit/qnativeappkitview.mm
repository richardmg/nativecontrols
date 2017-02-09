/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native AppKit Controls module of the Qt Toolkit.
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
#include <QtNativeAppKitControls/qnativeappkitview.h>
#include <QtNativeAppKitControls/private/qnativeappkitview_p.h>

@interface QtNativeNSView : NSView

@end

QT_BEGIN_NAMESPACE

NSRect qt_mac_flipRect(const QRectF &rect, NSView *view);

static qreal qt_mac_flipYCoordinate(qreal y, qreal height, NSView *view)
{
    if (view.superview && !view.superview.isFlipped)
        return view.superview.frame.size.height - (y + height);
    return y;
}

static QRectF qt_mac_flipRect(const NSRect &rect, NSView *view)
{
    return QRectF(rect.origin.x,
                  qt_mac_flipYCoordinate(rect.origin.y, rect.size.height, view),
                  rect.size.width,
                  rect.size.height);
}

NSRect qt_mac_flipRect(const QRectF &rect, NSView *view)
{
    return NSMakeRect(rect.x(),
                      qt_mac_flipYCoordinate(rect.y(), rect.height(), view),
                      rect.width(),
                      rect.height());
}

QNativeAppKitViewPrivate::QNativeAppKitViewPrivate(int version)
    : QNativeAppKitBasePrivate(version)
    , m_attributes(0)
    , m_view(nil)
{
}

QNativeAppKitViewPrivate::~QNativeAppKitViewPrivate()
{
    [m_view release];
}

void QNativeAppKitViewPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeAppKitView);
    QNativeAppKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QNativeControl *>(base);
    q->connect(q, &QNativeAppKitView::visibleChanged, b, &QNativeControl::visibleChanged);
    q->connect(q, &QNativeAppKitView::xChanged, b, &QNativeControl::xChanged);
    q->connect(q, &QNativeAppKitView::xChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeAppKitView::yChanged, b, &QNativeControl::yChanged);
    q->connect(q, &QNativeAppKitView::yChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeAppKitView::widthChanged, b, &QNativeControl::widthChanged);
    q->connect(q, &QNativeAppKitView::widthChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeAppKitView::heightChanged, b, &QNativeControl::heightChanged);
    q->connect(q, &QNativeAppKitView::heightChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeAppKitView::implicitWidthChanged, b, &QNativeControl::implicitWidthChanged);
    q->connect(q, &QNativeAppKitView::implicitHeightChanged, b, &QNativeControl::implicitHeightChanged);
}

void QNativeAppKitViewPrivate::updateLayout(bool recursive)
{
    Q_Q(QNativeAppKitView);

    if (!testAttribute(Resized)) {
        q->resize(q->implicitSize());
        setAttribute(Resized, false);
    }

    if (recursive) {
        for (QObject *child : q->children()) {
            if (QNativeAppKitViewPrivate *childPrivate = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(child)))
                childPrivate->updateLayout(recursive);
        }
    }
}

void QNativeAppKitViewPrivate::updateImplicitSize()
{
    Q_Q(QNativeAppKitView);
    QSizeF oldSize = m_implicitSize;
    NSControl *control = static_cast<NSControl *>(view());
    const NSSize size = [control isKindOfClass:[NSControl class]]
            ? [control sizeThatFits:NSZeroSize]
            : view().intrinsicContentSize;
    m_implicitSize = QSizeF(size.width, size.height);

    if (m_implicitSize.width() != oldSize.width()) {
        updateLayout(false);
        emit q->implicitWidthChanged(m_implicitSize.width());
    }

    if (m_implicitSize.height() != oldSize.height()) {
        updateLayout(false);
        emit q->implicitHeightChanged(m_implicitSize.height());
    }
}

NSView *QNativeAppKitViewPrivate::view()
{
    return m_view;
}

NSView *QNativeAppKitViewPrivate::view() const
{
    return m_view;
}

void QNativeAppKitViewPrivate::setView(NSView *view)
{
    [m_view release];
    m_view = [view retain];
}

static void qt_mac_removeFromSuperview(NSView *view)
{
    const BOOL hadSuperview = !!view.superview;
    const QRectF rect = qt_mac_flipRect(view.frame, view);
    [view removeFromSuperview];
    if (hadSuperview)
        view.frame = NSMakeRect(rect.x(), rect.y(), rect.width(), rect.height());
}

void QNativeAppKitViewPrivate::addSubView(NSView *subView)
{
    if (subView.superview)
        qt_mac_removeFromSuperview(subView);
    NSRect alignmentRect = [subView alignmentRectForFrame:subView.frame];
    [view() addSubview:subView];
    // Ratio between frame and alignment rect can change depending on whether the view is attached
    // to a superview, so reset it after reparenting
    subView.frame = [subView frameForAlignmentRect:alignmentRect];
    const QRectF rect = qt_mac_flipRect(subView.frame, subView);
    subView.frame = NSMakeRect(rect.x(), rect.y(), rect.width(), rect.height());
    subView.autoresizingMask = NSViewMaxXMargin
            | (subView.superview.isFlipped ? NSViewMaxYMargin : NSViewMinYMargin);
}

NSRect QNativeAppKitViewPrivate::alignmentRect() const
{
    return [m_view alignmentRectForFrame:m_view.frame];
}

void QNativeAppKitViewPrivate::setAlignmentRect(NSRect rect)
{
    m_view.frame = [m_view frameForAlignmentRect:rect];
}

void QNativeAppKitViewPrivate::setGeometry(const QRectF &rect)
{
    setAlignmentRect(qt_mac_flipRect(rect, view()));
}

QNativeAppKitView::QNativeAppKitView(QNativeAppKitBase *parent)
    : QNativeAppKitBase(*new QNativeAppKitViewPrivate(), parent)
{
    Q_D(QNativeAppKitView);
    if (!d->view()) {
        // Since no NSView was set during private construction, we assume that this
        // is just a standalone view. In that case, we create the missing view now.
        d->setView([[QtNativeNSView new] autorelease]);
        if (QNativeAppKitView *parent = parentView())
            static_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(parent))->addSubView(d->view());
    }
}

QNativeAppKitView::QNativeAppKitView(QNativeAppKitViewPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitBase(dd, parent)
{
}

QNativeAppKitView::~QNativeAppKitView()
{
}

bool QNativeAppKitView::visible() const
{
    return !d_func()->view().hidden;
}

void QNativeAppKitView::setVisible(bool newVisible)
{
    if (newVisible == visible())
        return;

    Q_D(QNativeAppKitView);
    d->view().hidden = !newVisible;

    emit visibleChanged(newVisible);
}

void QNativeAppKitView::setGeometry(const QRectF &rect)
{
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

void QNativeAppKitView::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    setX(posx);
    setY(posy);
    setWidth(w);
    setHeight(h);
}

void QNativeAppKitView::move(qreal posx, qreal posy)
{
    setX(posx);
    setY(posy);
}

void QNativeAppKitView::move(const QPointF &pos)
{
    setX(pos.x());
    setY(pos.y());
}

void QNativeAppKitView::resize(qreal width, qreal height)
{
    setWidth(width);
    setHeight(height);
}

void QNativeAppKitView::resize(const QSizeF size)
{
    setWidth(size.width());
    setHeight(size.height());
}

QSizeF QNativeAppKitView::implicitSize() const
{
    Q_D(const QNativeAppKitView);
    if (!d->m_implicitSize.isValid())
        const_cast<QNativeAppKitViewPrivate *>(d)->updateImplicitSize();
    return d->m_implicitSize;
}

qreal QNativeAppKitView::implicitWidth() const
{
    return implicitSize().width();
}

qreal QNativeAppKitView::implicitHeight() const
{
    return implicitSize().height();
}

QRectF QNativeAppKitView::geometry() const
{
    Q_D(const QNativeAppKitView);
    return qt_mac_flipRect(d->alignmentRect(), d->view());
}

QRectF QNativeAppKitView::frameGeometry() const
{
    Q_D(const QNativeAppKitView);
    return qt_mac_flipRect(d->view().frame, d->view());
}

qreal QNativeAppKitView::x() const
{
    return geometry().x();
}

void QNativeAppKitView::setX(qreal newX)
{
    if (newX == x())
        return;

    Q_D(QNativeAppKitView);
    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitViewPrivate::Moved);

    emit xChanged(newX);
}

qreal QNativeAppKitView::y() const
{
    return geometry().y();
}

void QNativeAppKitView::setY(qreal newY)
{
    if (newY == y())
        return;

    Q_D(QNativeAppKitView);
    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitViewPrivate::Moved);

    emit yChanged(newY);
}

qreal QNativeAppKitView::width() const
{
    return geometry().width();
}

void QNativeAppKitView::setWidth(qreal newWidth)
{
    if (newWidth == width())
        return;

    Q_D(QNativeAppKitView);
    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitViewPrivate::Resized);

    emit widthChanged(newWidth);
}

qreal QNativeAppKitView::height() const
{
    return geometry().height();
}

void QNativeAppKitView::setHeight(qreal newHeight)
{
    if (newHeight == height())
        return;

    Q_D(QNativeAppKitView);
    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeAppKitViewPrivate::Resized);

    emit heightChanged(newHeight);
}

QNativeAppKitView *QNativeAppKitView::parentView()
{
   return dynamic_cast<QNativeAppKitView *>(parent());
}

NSView *QNativeAppKitView::nsViewHandle()
{
   return d_func()->view();
}

void QNativeAppKitView::childEvent(QChildEvent *event)
{
    Q_D(QNativeAppKitView);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QNativeAppKitViewPrivate *dptr_child = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    // The flipping machinery here is designed to interop with Cocoa's flipped coordinate system:
    // before we deparent a view, we flip its frame to a top-left origin and then set that as the
    // frame after the control is deparented. Then, when we parent a view, we flip its top-left
    // frame to a bottom-left (AppKit) frame after parenting it. This allows views to always use
    // top-left (Qt) origins while parenting to either flipped or non-flipped views. Note that
    // autoresizing will still interfere with top-left origins so we give fixed-size controls
    // the default AppKit autoresizing mask (NSViewMaxXMargin | NSViewMinYMargin) to compensate.
    if (event->added()) {
        d->addSubView(dptr_child->view());
    } else if (event->removed()) {
        qt_mac_removeFromSuperview(dptr_child->view());
    }
}

#include "moc_qnativeappkitview.cpp"

QT_END_NAMESPACE