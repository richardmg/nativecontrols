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
    q->connect(q, &QNativeAppKitView::rightChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeAppKitView::yChanged, b, &QNativeControl::yChanged);
    q->connect(q, &QNativeAppKitView::bottomChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeAppKitView::widthChanged, b, &QNativeControl::widthChanged);
    q->connect(q, &QNativeAppKitView::rightChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeAppKitView::heightChanged, b, &QNativeControl::heightChanged);
    q->connect(q, &QNativeAppKitView::bottomChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeAppKitView::implicitWidthChanged, b, &QNativeControl::implicitWidthChanged);
    q->connect(q, &QNativeAppKitView::implicitHeightChanged, b, &QNativeControl::implicitHeightChanged);
}

void QNativeAppKitViewPrivate::initConnections()
{
    Q_Q(QNativeAppKitView);
    q->connect(q, &QNativeAppKitView::xChanged, q, &QNativeAppKitView::rightChanged);
    q->connect(q, &QNativeAppKitView::yChanged, q, &QNativeAppKitView::bottomChanged);
    q->connect(q, &QNativeAppKitView::widthChanged, q, &QNativeAppKitView::rightChanged);
    q->connect(q, &QNativeAppKitView::heightChanged, q, &QNativeAppKitView::bottomChanged);
}

void QNativeAppKitViewPrivate::updateLayout(bool recursive)
{
    Q_Q(QNativeAppKitView);

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
            if (QNativeAppKitViewPrivate *childPrivate = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(child)))
                childPrivate->updateLayout(recursive);
        }
    }
}

void QNativeAppKitViewPrivate::updateImplicitSize()
{
    Q_Q(QNativeAppKitView);
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

NSView *QNativeAppKitViewPrivate::view()
{
    if (!m_view)
        m_view = createView();
    return m_view;
}

NSView *QNativeAppKitViewPrivate::view() const
{
    return const_cast<QNativeAppKitViewPrivate *>(this)->view();
}

NSView *QNativeAppKitViewPrivate::createView()
{
    return [NSView new];
}

void QNativeAppKitViewPrivate::removeSubView(NSView *view)
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
        removeSubView(subView);

    // The flipping machinery here is designed to interop with Cocoa's flipped coordinate system:
    // before we deparent a view, we flip its frame to a top-left origin and then set that as the
    // frame after the control is deparented. Then, when we parent a view, we flip its top-left
    // frame to a bottom-left (AppKit) frame after parenting it. This allows views to always use
    // top-left (Qt) origins while parenting to either flipped or non-flipped views. Note that
    // autoresizing will still interfere with top-left origins so we give fixed-size controls
    // the default AppKit autoresizing mask (NSViewMaxXMargin | NSViewMinYMargin) to compensate.
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
    return [view() alignmentRectForFrame:view().frame];
}

void QNativeAppKitViewPrivate::setAlignmentRect(NSRect rect)
{
    view().frame = [view() frameForAlignmentRect:rect];
}

void QNativeAppKitViewPrivate::setGeometry(const QRectF &rect)
{
    setAlignmentRect(qt_mac_flipRect(rect, view()));
}

QNativeAppKitView::QNativeAppKitView(QNativeAppKitBase *parent)
    : QNativeAppKitBase(*new QNativeAppKitViewPrivate(), parent)
{
    d_func()->initConnections();
}

QNativeAppKitView::QNativeAppKitView(QNativeAppKitViewPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitBase(dd, parent)
{
    d_func()->initConnections();
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

void QNativeAppKitView::setImplicitSize(const QSizeF &size)
{
    setImplicitWidth(size.width());
    setImplicitHeight(size.height());
}

qreal QNativeAppKitView::implicitWidth() const
{
    return implicitSize().width();
}

void QNativeAppKitView::setImplicitWidth(qreal width)
{
    Q_D(QNativeAppKitView);
    d->setAttribute(QNativeAppKitViewPrivate::ResizedImplicitWidth);

    if (width == d->m_implicitSize.width())
        return;

    d->m_implicitSize.setWidth(width);
    d->updateLayout(false);
    emit implicitWidthChanged(width);
}

qreal QNativeAppKitView::implicitHeight() const
{
    return implicitSize().height();
}

void QNativeAppKitView::setImplicitHeight(qreal height)
{
    Q_D(QNativeAppKitView);
    d->setAttribute(QNativeAppKitViewPrivate::ResizedImplicitHeight);

    if (height == d->m_implicitSize.height())
        return;

    d->m_implicitSize.setHeight(height);
    d->updateLayout(false);
    emit implicitHeightChanged(height);
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
    Q_D(QNativeAppKitView);
    d->setAttribute(QNativeAppKitViewPrivate::MovedX);

    if (newX == x())
        return;

    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setGeometry(g);

    emit xChanged(newX);
}

qreal QNativeAppKitView::y() const
{
    return geometry().y();
}

void QNativeAppKitView::setY(qreal newY)
{
    Q_D(QNativeAppKitView);
    d->setAttribute(QNativeAppKitViewPrivate::MovedY);

    if (newY == y())
        return;

    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setGeometry(g);

    emit yChanged(newY);
}

qreal QNativeAppKitView::width() const
{
    return geometry().width();
}

void QNativeAppKitView::setWidth(qreal newWidth)
{
    Q_D(QNativeAppKitView);
    d->setAttribute(QNativeAppKitViewPrivate::ResizedWidth);

    if (newWidth == width())
        return;

    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setGeometry(g);

    emit widthChanged(newWidth);
}

qreal QNativeAppKitView::height() const
{
    return geometry().height();
}

void QNativeAppKitView::setHeight(qreal newHeight)
{
    Q_D(QNativeAppKitView);
    d->setAttribute(QNativeAppKitViewPrivate::ResizedHeight);

    if (newHeight == height())
        return;

    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setGeometry(g);

    emit heightChanged(newHeight);
}

qreal QNativeAppKitView::left() const
{
    return geometry().left();
}

qreal QNativeAppKitView::top() const
{
    return geometry().top();
}

qreal QNativeAppKitView::right() const
{
    return geometry().right();
}

qreal QNativeAppKitView::bottom() const
{
    return geometry().bottom();
}

QNativeAppKitView *QNativeAppKitView::parentView()
{
    return dynamic_cast<QNativeAppKitView *>(parent());
}

NSView *QNativeAppKitView::nsViewHandle()
{
   return d_func()->view();
}

bool QNativeAppKitView::setNativeParent(QObject *parent)
{
    if (QNativeAppKitView *p = dynamic_cast<QNativeAppKitView *>(parent))
        setParent(p);
    else
        return QNativeAppKitBase::setNativeParent(parent);
    return true;
}

bool QNativeAppKitView::setNativeParent(const QByteArray &type, void *parent)
{
    if (type == "NSView")
        [reinterpret_cast<NSView *>(parent) addSubview:nsViewHandle()];
    else
        return QNativeAppKitBase::setNativeParent(type, parent);
    return true;
}

bool QNativeAppKitView::addNativeChild(QObject *child)
{
    if (QNativeAppKitView *c = dynamic_cast<QNativeAppKitView *>(child))
        c->setParent(this);
    else
        return QNativeAppKitBase::addNativeChild(child);
    return true;
}

bool QNativeAppKitView::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "NSView")
        d_func()->addSubView(reinterpret_cast<NSView *>(child));
    else
        return QNativeAppKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QNativeAppKitView::supportedNativeChildTypes()
{
    return QNativeAppKitBase::supportedNativeChildTypes() << "NSView";
}

QByteArrayList QNativeAppKitView::supportedNativeParentTypes()
{
    return supportedNativeChildTypes();
}

void QNativeAppKitView::childEvent(QChildEvent *event)
{
    Q_D(QNativeAppKitView);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QNativeAppKitViewPrivate *dptr_child = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    if (event->added())
        d->addSubView(dptr_child->view());
    else if (event->removed())
        d->removeSubView(dptr_child->view());
}

#include "moc_qnativeappkitview.cpp"

QT_END_NAMESPACE
