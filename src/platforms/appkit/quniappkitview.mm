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

#include <QtNativeControls/qunicontrol.h>
#include <QtNativeAppKitControls/quniappkitview.h>
#include <QtNativeAppKitControls/private/quniappkitview_p.h>

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

QUniAppKitViewPrivate::QUniAppKitViewPrivate(int version)
    : QUniAppKitBasePrivate(version)
    , m_attributes(0)
    , m_view(nil)
{
}

QUniAppKitViewPrivate::~QUniAppKitViewPrivate()
{
    [m_view release];
}

void QUniAppKitViewPrivate::connectSignals(QUniBase *base)
{
    Q_Q(QUniAppKitView);
    QUniAppKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QUniControl *>(base);
    q->connect(q, &QUniAppKitView::visibleChanged, b, &QUniControl::visibleChanged);
    q->connect(q, &QUniAppKitView::xChanged, b, &QUniControl::xChanged);
    q->connect(q, &QUniAppKitView::rightChanged, b, &QUniControl::rightChanged);
    q->connect(q, &QUniAppKitView::yChanged, b, &QUniControl::yChanged);
    q->connect(q, &QUniAppKitView::bottomChanged, b, &QUniControl::bottomChanged);
    q->connect(q, &QUniAppKitView::widthChanged, b, &QUniControl::widthChanged);
    q->connect(q, &QUniAppKitView::rightChanged, b, &QUniControl::rightChanged);
    q->connect(q, &QUniAppKitView::heightChanged, b, &QUniControl::heightChanged);
    q->connect(q, &QUniAppKitView::bottomChanged, b, &QUniControl::bottomChanged);
    q->connect(q, &QUniAppKitView::implicitWidthChanged, b, &QUniControl::implicitWidthChanged);
    q->connect(q, &QUniAppKitView::implicitHeightChanged, b, &QUniControl::implicitHeightChanged);
}

void QUniAppKitViewPrivate::initConnections()
{
    Q_Q(QUniAppKitView);
    q->connect(q, &QUniAppKitView::xChanged, q, &QUniAppKitView::rightChanged);
    q->connect(q, &QUniAppKitView::yChanged, q, &QUniAppKitView::bottomChanged);
    q->connect(q, &QUniAppKitView::widthChanged, q, &QUniAppKitView::rightChanged);
    q->connect(q, &QUniAppKitView::heightChanged, q, &QUniAppKitView::bottomChanged);
}

void QUniAppKitViewPrivate::updateLayout(bool recursive)
{
    Q_Q(QUniAppKitView);

    if (!testAttribute(ResizedWidth)) {
        q->setWidth(q->implicitWidth());
        setAttribute(ResizedWidth, false);
    }

    if (!testAttribute(ResizedHeight)) {
        q->setHeight(q->implicitHeight());
        setAttribute(ResizedHeight, false);
    }

    if (recursive) {
        for (QObject *child : q->children()) {
            if (QUniAppKitViewPrivate *childPrivate = dynamic_cast<QUniAppKitViewPrivate *>(QObjectPrivate::get(child)))
                childPrivate->updateLayout(recursive);
        }
    }
}

void QUniAppKitViewPrivate::updateImplicitSize()
{
    Q_Q(QUniAppKitView);
     // This function should be called whenever the view changes properties
     // that can affect implicit size. But if the app has set an implicit
     // size explicit, that size should always be kept, and if we can just return.
     // Otherwise, we ask AppKit for the best size that fits the view.
     const bool resizedImplicitWidth = testAttribute(ResizedImplicitWidth);
     const bool resizedImplicitHeight = testAttribute(ResizedImplicitHeight);
     if (resizedImplicitWidth && resizedImplicitHeight)
         return;

     QSizeF oldSize = m_implicitSize;
     NSControl *control = static_cast<NSControl *>(view());
     const NSSize sizeThatFits = [control isKindOfClass:[NSControl class]]
             ? [control sizeThatFits:NSZeroSize]
             : view().intrinsicContentSize;
     bool layoutNeeded = false;

     if (!resizedImplicitWidth && sizeThatFits.width != oldSize.width()) {
         m_implicitSize.setWidth(sizeThatFits.width);
         emit q->implicitWidthChanged(sizeThatFits.width);
         layoutNeeded = true;
     }

     if (!resizedImplicitHeight && sizeThatFits.height != oldSize.height()) {
         m_implicitSize.setHeight(sizeThatFits.height);
         emit q->implicitHeightChanged(sizeThatFits.height);
         layoutNeeded = true;
     }

     if (layoutNeeded)
         updateLayout(false);
}

NSView *QUniAppKitViewPrivate::view()
{
    if (!m_view)
        m_view = createView();
    return m_view;
}

NSView *QUniAppKitViewPrivate::view() const
{
    return const_cast<QUniAppKitViewPrivate *>(this)->view();
}

NSView *QUniAppKitViewPrivate::createView()
{
    return [NSView new];
}

void QUniAppKitViewPrivate::removeSubView(NSView *view)
{
    const BOOL hadSuperview = !!view.superview;
    const QRectF rect = qt_mac_flipRect(view.frame, view);
    [view removeFromSuperview];
    if (hadSuperview)
        view.frame = rect.toCGRect();
}

void QUniAppKitViewPrivate::addSubViewToSuperView(NSView *subView, NSView *superView)
{
    // The flipping machinery here is designed to interop with Cocoa's flipped coordinate system:
    // before we deparent a view, we flip its frame to a top-left origin and then set that as the
    // frame after the control is deparented. Then, when we parent a view, we flip its top-left
    // frame to a bottom-left (AppKit) frame after parenting it. This allows views to always use
    // top-left (Qt) origins while parenting to either flipped or non-flipped views. Note that
    // autoresizing will still interfere with top-left origins so we give fixed-size controls
    // the default AppKit autoresizing mask (NSViewMaxXMargin | NSViewMinYMargin) to compensate.

    if (subView.superview)
        removeSubView(subView);

    // Ratio between frame and alignment rect can change depending on whether the
    // view is attached to a superview, so reset it after reparenting.
    NSRect alignmentRect = [subView alignmentRectForFrame:subView.frame];

    [superView addSubview:subView];

    // If the height of the new superview differs from the previous, we need to recalculate
    // the subview's frame to keep the same top-left distance.
    NSRect frame = [subView frameForAlignmentRect:alignmentRect];
    subView.frame = qt_mac_flipRect(frame, subView).toCGRect();
    subView.autoresizingMask = NSViewMaxXMargin
            | (subView.superview.isFlipped ? NSViewMaxYMargin : NSViewMinYMargin);
}

void QUniAppKitViewPrivate::addSubView(NSView *subView)
{
    addSubViewToSuperView(subView, view());
}

NSRect QUniAppKitViewPrivate::alignmentRect() const
{
    return [view() alignmentRectForFrame:view().frame];
}

void QUniAppKitViewPrivate::setAlignmentRect(NSRect rect)
{
    view().frame = [view() frameForAlignmentRect:rect];
}

void QUniAppKitViewPrivate::setGeometry(const QRectF &rect)
{
    setAlignmentRect(qt_mac_flipRect(rect, view()));
}

QUniAppKitView::QUniAppKitView(QUniAppKitBase *parent)
    : QUniAppKitBase(*new QUniAppKitViewPrivate(), parent)
{
    d_func()->initConnections();
}

QUniAppKitView::QUniAppKitView(QUniAppKitViewPrivate &dd, QUniAppKitBase *parent)
    : QUniAppKitBase(dd, parent)
{
    d_func()->initConnections();
}

QUniAppKitView::~QUniAppKitView()
{
}

bool QUniAppKitView::visible() const
{
    return !d_func()->view().hidden;
}

void QUniAppKitView::setVisible(bool newVisible)
{
    if (newVisible == visible())
        return;

    Q_D(QUniAppKitView);
    d->view().hidden = !newVisible;

    emit visibleChanged(newVisible);
}

void QUniAppKitView::setGeometry(const QRectF &rect)
{
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

void QUniAppKitView::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    setX(posx);
    setY(posy);
    setWidth(w);
    setHeight(h);
}

void QUniAppKitView::move(qreal posx, qreal posy)
{
    setX(posx);
    setY(posy);
}

void QUniAppKitView::move(const QPointF &pos)
{
    setX(pos.x());
    setY(pos.y());
}

void QUniAppKitView::resize(qreal width, qreal height)
{
    setWidth(width);
    setHeight(height);
}

void QUniAppKitView::resize(const QSizeF size)
{
    setWidth(size.width());
    setHeight(size.height());
}

QSizeF QUniAppKitView::implicitSize() const
{
    Q_D(const QUniAppKitView);
    if (!d->m_implicitSize.isValid())
        const_cast<QUniAppKitViewPrivate *>(d)->updateImplicitSize();
    return d->m_implicitSize;
}

void QUniAppKitView::setImplicitSize(const QSizeF &size)
{
    setImplicitWidth(size.width());
    setImplicitHeight(size.height());
}

qreal QUniAppKitView::implicitWidth() const
{
    return implicitSize().width();
}

void QUniAppKitView::setImplicitWidth(qreal width)
{
    Q_D(QUniAppKitView);
    d->setAttribute(QUniAppKitViewPrivate::ResizedImplicitWidth);

    if (width == d->m_implicitSize.width())
        return;

    d->m_implicitSize.setWidth(width);
    d->updateLayout(false);
    emit implicitWidthChanged(width);
}

qreal QUniAppKitView::implicitHeight() const
{
    return implicitSize().height();
}

void QUniAppKitView::setImplicitHeight(qreal height)
{
    Q_D(QUniAppKitView);
    d->setAttribute(QUniAppKitViewPrivate::ResizedImplicitHeight);

    if (height == d->m_implicitSize.height())
        return;

    d->m_implicitSize.setHeight(height);
    d->updateLayout(false);
    emit implicitHeightChanged(height);
}

QRectF QUniAppKitView::geometry() const
{
    Q_D(const QUniAppKitView);
    return qt_mac_flipRect(d->alignmentRect(), d->view());
}

QRectF QUniAppKitView::frameGeometry() const
{
    Q_D(const QUniAppKitView);
    return qt_mac_flipRect(d->view().frame, d->view());
}

qreal QUniAppKitView::x() const
{
    return geometry().x();
}

void QUniAppKitView::setX(qreal newX)
{
    Q_D(QUniAppKitView);
    d->setAttribute(QUniAppKitViewPrivate::MovedX);

    if (newX == x())
        return;

    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setGeometry(g);

    emit xChanged(newX);
}

qreal QUniAppKitView::y() const
{
    return geometry().y();
}

void QUniAppKitView::setY(qreal newY)
{
    Q_D(QUniAppKitView);
    d->setAttribute(QUniAppKitViewPrivate::MovedY);

    if (newY == y())
        return;

    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setGeometry(g);

    emit yChanged(newY);
}

qreal QUniAppKitView::width() const
{
    return geometry().width();
}

void QUniAppKitView::setWidth(qreal newWidth)
{
    Q_D(QUniAppKitView);
    d->setAttribute(QUniAppKitViewPrivate::ResizedWidth);

    if (newWidth == width())
        return;

    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setGeometry(g);

    emit widthChanged(newWidth);
}

qreal QUniAppKitView::height() const
{
    return geometry().height();
}

void QUniAppKitView::setHeight(qreal newHeight)
{
    Q_D(QUniAppKitView);
    d->setAttribute(QUniAppKitViewPrivate::ResizedHeight);

    if (newHeight == height())
        return;

    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setGeometry(g);

    emit heightChanged(newHeight);
}

qreal QUniAppKitView::left() const
{
    return geometry().left();
}

qreal QUniAppKitView::top() const
{
    return geometry().top();
}

qreal QUniAppKitView::right() const
{
    return geometry().right();
}

qreal QUniAppKitView::bottom() const
{
    return geometry().bottom();
}

QUniAppKitView *QUniAppKitView::parentView()
{
    return qobject_cast<QUniAppKitView *>(parent());
}

NSView *QUniAppKitView::nsViewHandle()
{
   return d_func()->view();
}

bool QUniAppKitView::setNativeParent(QObject *parent)
{
    if (QUniAppKitView *p = qobject_cast<QUniAppKitView *>(parent))
        setParent(p);
    else
        return QUniAppKitBase::setNativeParent(parent);
    return true;
}

bool QUniAppKitView::setNativeParent(const QByteArray &type, void *parent)
{
    if (type == "NSView") {
        d_func()->addSubViewToSuperView(nsViewHandle(), static_cast<NSView *>(parent));
    } else {
        return QUniAppKitBase::setNativeParent(type, parent);
    }
    return true;
}

bool QUniAppKitView::addNativeChild(QObject *child)
{
    if (QUniAppKitView *c = qobject_cast<QUniAppKitView *>(child))
        c->setParent(this);
    else
        return QUniAppKitBase::addNativeChild(child);
    return true;
}

bool QUniAppKitView::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "NSView")
        d_func()->addSubView(static_cast<NSView *>(child));
    else
        return QUniAppKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QUniAppKitView::supportedNativeChildTypes()
{
    return QUniAppKitBase::supportedNativeChildTypes() << "NSView";
}

QByteArrayList QUniAppKitView::supportedNativeParentTypes()
{
    return supportedNativeChildTypes();
}

void QUniAppKitView::childEvent(QChildEvent *event)
{
    Q_D(QUniAppKitView);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QUniAppKitViewPrivate *dptr_child = dynamic_cast<QUniAppKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    if (event->added())
        d->addSubView(dptr_child->view());
    else if (event->removed())
        d->removeSubView(dptr_child->view());
}

#include "moc_quniappkitview.cpp"

QT_END_NAMESPACE
