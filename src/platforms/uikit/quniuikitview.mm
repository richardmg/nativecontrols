/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native UIKit Controls module of the Qt Toolkit.
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

#include <QtUniControls/qunicontrol.h>
#include <QtUniUIKitControls/quniuikitview.h>
#include <QtUniUIKitControls/private/quniuikitview_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitViewPrivate::QUniUIKitViewPrivate(int version)
    : QUniUIKitBasePrivate(version)
    , m_attributes(0)
    , m_view(nil)
{
}

QUniUIKitViewPrivate::~QUniUIKitViewPrivate()
{
    [m_view release];
}

void QUniUIKitViewPrivate::connectSignals(QUniBase *base)
{
    Q_Q(QUniUIKitView);
    QUniUIKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QUniControl *>(base);
    q->connect(q, &QUniUIKitView::visibleChanged, b, &QUniControl::visibleChanged);
    q->connect(q, &QUniUIKitView::xChanged, b, &QUniControl::xChanged);
    q->connect(q, &QUniUIKitView::rightChanged, b, &QUniControl::rightChanged);
    q->connect(q, &QUniUIKitView::yChanged, b, &QUniControl::yChanged);
    q->connect(q, &QUniUIKitView::bottomChanged, b, &QUniControl::bottomChanged);
    q->connect(q, &QUniUIKitView::widthChanged, b, &QUniControl::widthChanged);
    q->connect(q, &QUniUIKitView::rightChanged, b, &QUniControl::rightChanged);
    q->connect(q, &QUniUIKitView::heightChanged, b, &QUniControl::heightChanged);
    q->connect(q, &QUniUIKitView::bottomChanged, b, &QUniControl::bottomChanged);
    q->connect(q, &QUniUIKitView::implicitWidthChanged, b, &QUniControl::implicitWidthChanged);
    q->connect(q, &QUniUIKitView::implicitHeightChanged, b, &QUniControl::implicitHeightChanged);
}

void QUniUIKitViewPrivate::initConnections()
{
    Q_Q(QUniUIKitView);
    q->connect(q, &QUniUIKitView::xChanged, q, &QUniUIKitView::rightChanged);
    q->connect(q, &QUniUIKitView::yChanged, q, &QUniUIKitView::bottomChanged);
    q->connect(q, &QUniUIKitView::widthChanged, q, &QUniUIKitView::rightChanged);
    q->connect(q, &QUniUIKitView::heightChanged, q, &QUniUIKitView::bottomChanged);
}

void QUniUIKitViewPrivate::updateLayout(bool recursive)
{
    Q_Q(QUniUIKitView);

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
            if (QUniUIKitViewPrivate *childPrivate = dynamic_cast<QUniUIKitViewPrivate *>(QObjectPrivate::get(child)))
                childPrivate->updateLayout(recursive);
        }
    }
}

void QUniUIKitViewPrivate::updateImplicitSize()
{
    Q_Q(QUniUIKitView);
    // This function should be called whenever the view changes properties
    // that can affect implicit size. But if the app has set an implicit
    // size explicit, that size should always be kept, and if we can just return.
    // Otherwise, we ask UIKit for the best size that fits the view.
    const bool resizedImplicitWidth = testAttribute(ResizedImplicitWidth);
    const bool resizedImplicitHeight = testAttribute(ResizedImplicitHeight);
    if (resizedImplicitWidth && resizedImplicitHeight)
        return;

    QSizeF oldSize = m_implicitSize;
    CGSize sizeThatFits = [view() sizeThatFits:CGSizeZero];
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

UIView *QUniUIKitViewPrivate::view()
{
    if (!m_view)
        m_view = createView();
    return m_view;
}

UIView *QUniUIKitViewPrivate::view() const
{
    return const_cast<QUniUIKitViewPrivate *>(this)->view();
}

UIView *QUniUIKitViewPrivate::createView()
{
    UIView *view = [UIView new];
    view.backgroundColor = [UIColor whiteColor];
    return view;
}

void QUniUIKitViewPrivate::addSubView(UIView *subView)
{
    // Ratio between frame and alignment rect can change depending on whether the
    // view is attached to a superview, so reset it after reparenting
    CGRect alignmentRect = [subView alignmentRectForFrame:subView.frame];

    [view() addSubview:subView];

    subView.frame = [subView frameForAlignmentRect:alignmentRect];
    subView.autoresizingMask =
            UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleBottomMargin;
}

CGRect QUniUIKitViewPrivate::alignmentRect() const
{
    return [view() alignmentRectForFrame:view().frame];
}

void QUniUIKitViewPrivate::setAlignmentRect(CGRect rect)
{
    view().frame = [view() frameForAlignmentRect:rect];
}

void QUniUIKitViewPrivate::setGeometry(const QRectF &rect)
{
    setAlignmentRect(rect.toCGRect());
}

QUniUIKitView::QUniUIKitView(QUniUIKitBase *parent)
    : QUniUIKitBase(*new QUniUIKitViewPrivate(), parent)
{
    d_func()->initConnections();
}

QUniUIKitView::QUniUIKitView(QUniUIKitViewPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitBase(dd, parent)
{
    d_func()->initConnections();
}

QUniUIKitView::~QUniUIKitView()
{
}

bool QUniUIKitView::visible() const
{
    return !d_func()->view().hidden;
}

void QUniUIKitView::setVisible(bool newVisible)
{
    if (newVisible == visible())
        return;

    Q_D(QUniUIKitView);
    d->view().hidden = !newVisible;

    emit visibleChanged(newVisible);
}

void QUniUIKitView::setGeometry(const QRectF &rect)
{
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

void QUniUIKitView::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    setX(posx);
    setY(posy);
    setWidth(w);
    setHeight(h);
}

void QUniUIKitView::move(qreal posx, qreal posy)
{
    setX(posx);
    setY(posy);
}

void QUniUIKitView::move(const QPointF &pos)
{
    setX(pos.x());
    setY(pos.y());
}

void QUniUIKitView::resize(qreal width, qreal height)
{
    setWidth(width);
    setHeight(height);
}

void QUniUIKitView::resize(const QSizeF size)
{
    setWidth(size.width());
    setHeight(size.height());
}

QSizeF QUniUIKitView::implicitSize() const
{
    Q_D(const QUniUIKitView);
    if (!d->m_implicitSize.isValid())
        const_cast<QUniUIKitViewPrivate *>(d)->updateImplicitSize();
    return d->m_implicitSize;
}

void QUniUIKitView::setImplicitSize(const QSizeF &size)
{
    setImplicitWidth(size.width());
    setImplicitHeight(size.height());
}

qreal QUniUIKitView::implicitWidth() const
{
    return implicitSize().width();
}

void QUniUIKitView::setImplicitWidth(qreal width)
{
    Q_D(QUniUIKitView);
    d->setAttribute(QUniUIKitViewPrivate::ResizedImplicitWidth);

    if (width == d->m_implicitSize.width())
        return;

    d->m_implicitSize.setWidth(width);
    d->updateLayout(false);
    emit implicitWidthChanged(width);
}

qreal QUniUIKitView::implicitHeight() const
{
    return implicitSize().height();
}

void QUniUIKitView::setImplicitHeight(qreal height)
{
    Q_D(QUniUIKitView);
    d->setAttribute(QUniUIKitViewPrivate::ResizedImplicitHeight);

    if (height == d->m_implicitSize.height())
        return;

    d->m_implicitSize.setHeight(height);
    d->updateLayout(false);
    emit implicitHeightChanged(height);
}

QRectF QUniUIKitView::geometry() const
{
    return QRectF::fromCGRect(d_func()->alignmentRect());
}

QRectF QUniUIKitView::frameGeometry() const
{
    return QRectF::fromCGRect(d_func()->view().frame);
}

qreal QUniUIKitView::x() const
{
    return geometry().x();
}

void QUniUIKitView::setX(qreal newX)
{
    Q_D(QUniUIKitView);
    d->setAttribute(QUniUIKitViewPrivate::MovedX);

    if (newX == x())
        return;

    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setGeometry(g);

    emit xChanged(newX);
}

qreal QUniUIKitView::y() const
{
    return geometry().y();
}

void QUniUIKitView::setY(qreal newY)
{
    Q_D(QUniUIKitView);
    d->setAttribute(QUniUIKitViewPrivate::MovedY);

    if (newY == y())
        return;

    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setGeometry(g);

    emit yChanged(newY);
}

qreal QUniUIKitView::width() const
{
    return geometry().width();
}

void QUniUIKitView::setWidth(qreal newWidth)
{
    Q_D(QUniUIKitView);
    d->setAttribute(QUniUIKitViewPrivate::ResizedWidth);

    if (newWidth == width())
        return;

    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setGeometry(g);

    emit widthChanged(newWidth);
}

qreal QUniUIKitView::height() const
{
    return geometry().height();
}

void QUniUIKitView::setHeight(qreal newHeight)
{
    Q_D(QUniUIKitView);
    d->setAttribute(QUniUIKitViewPrivate::ResizedHeight);

    if (newHeight == height())
        return;

    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setGeometry(g);

    emit heightChanged(newHeight);
}

qreal QUniUIKitView::left() const
{
    return geometry().left();
}

qreal QUniUIKitView::top() const
{
    return geometry().top();
}

qreal QUniUIKitView::right() const
{
    return geometry().right();
}

qreal QUniUIKitView::bottom() const
{
    return geometry().bottom();
}

QUniUIKitView *QUniUIKitView::parentView()
{
    return qobject_cast<QUniUIKitView *>(parent());
}

UIView *QUniUIKitView::uiViewHandle()
{
   return d_func()->view();
}

bool QUniUIKitView::setNativeParent(QObject *parent)
{
    if (QUniUIKitView *p = qobject_cast<QUniUIKitView *>(parent))
        setParent(p);
    else
        return QUniUIKitBase::setNativeParent(parent);
    return true;
}

bool QUniUIKitView::setNativeParent(const QByteArray &type, void *parent)
{
    if (type == "UIView")
        [static_cast<UIView *>(parent) addSubview:uiViewHandle()];
    else
        return QUniUIKitBase::setNativeParent(type, parent);
    return true;
}

bool QUniUIKitView::addNativeChild(QObject *child)
{
    if (QUniUIKitView *c = qobject_cast<QUniUIKitView *>(child))
        c->setParent(this);
    else
        return QUniUIKitBase::addNativeChild(child);
    return true;
}

bool QUniUIKitView::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "UIView")
        d_func()->addSubView(static_cast<UIView *>(child));
    else
        return QUniUIKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QUniUIKitView::supportedNativeChildTypes()
{
    return QUniUIKitBase::supportedNativeChildTypes() << "UIView";
}

QByteArrayList QUniUIKitView::supportedNativeParentTypes()
{
    return supportedNativeChildTypes();
}

void QUniUIKitView::childEvent(QChildEvent *event)
{
    Q_D(QUniUIKitView);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QUniUIKitViewPrivate *dptr_child = dynamic_cast<QUniUIKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    if (event->added()) {
        d->addSubView(dptr_child->view());
    } else if (event->removed()) {
        [dptr_child->view() removeFromSuperview];
    }
}

#include "moc_quniuikitview.cpp"

QT_END_NAMESPACE
