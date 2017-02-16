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

#include <QtNativeControls/qnativecontrol.h>
#include <QtNativeUIKitControls/qnativeuikitview.h>
#include <QtNativeUIKitControls/private/qnativeuikitview_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitViewPrivate::QNativeUIKitViewPrivate(int version)
    : QNativeUIKitBasePrivate(version)
    , m_attributes(0)
    , m_view(nil)
{
}

QNativeUIKitViewPrivate::~QNativeUIKitViewPrivate()
{
    [m_view release];
}

void QNativeUIKitViewPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeUIKitView);
    QNativeUIKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QNativeControl *>(base);
    q->connect(q, &QNativeUIKitView::visibleChanged, b, &QNativeControl::visibleChanged);
    q->connect(q, &QNativeUIKitView::xChanged, b, &QNativeControl::xChanged);
    q->connect(q, &QNativeUIKitView::rightChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeUIKitView::yChanged, b, &QNativeControl::yChanged);
    q->connect(q, &QNativeUIKitView::bottomChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeUIKitView::widthChanged, b, &QNativeControl::widthChanged);
    q->connect(q, &QNativeUIKitView::rightChanged, b, &QNativeControl::rightChanged);
    q->connect(q, &QNativeUIKitView::heightChanged, b, &QNativeControl::heightChanged);
    q->connect(q, &QNativeUIKitView::bottomChanged, b, &QNativeControl::bottomChanged);
    q->connect(q, &QNativeUIKitView::implicitWidthChanged, b, &QNativeControl::implicitWidthChanged);
    q->connect(q, &QNativeUIKitView::implicitHeightChanged, b, &QNativeControl::implicitHeightChanged);
}

void QNativeUIKitViewPrivate::initConnections()
{
    Q_Q(QNativeUIKitView);
    q->connect(q, &QNativeUIKitView::xChanged, q, &QNativeUIKitView::rightChanged);
    q->connect(q, &QNativeUIKitView::yChanged, q, &QNativeUIKitView::bottomChanged);
    q->connect(q, &QNativeUIKitView::widthChanged, q, &QNativeUIKitView::rightChanged);
    q->connect(q, &QNativeUIKitView::heightChanged, q, &QNativeUIKitView::bottomChanged);
}

void QNativeUIKitViewPrivate::updateLayout(bool recursive)
{
    Q_Q(QNativeUIKitView);

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
            if (QNativeUIKitViewPrivate *childPrivate = dynamic_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(child)))
                childPrivate->updateLayout(recursive);
        }
    }
}

void QNativeUIKitViewPrivate::updateImplicitSize()
{
    Q_Q(QNativeUIKitView);
    QSizeF oldSize = m_implicitSize;
    m_implicitSize = QSizeF::fromCGSize([view() sizeThatFits:CGSizeZero]);

    if (m_implicitSize.width() != oldSize.width()) {
        updateLayout(false);
        emit q->implicitWidthChanged(m_implicitSize.width());
    }

    if (m_implicitSize.height() != oldSize.height()) {
        updateLayout(false);
        emit q->implicitHeightChanged(m_implicitSize.height());
    }
}

UIView *QNativeUIKitViewPrivate::view()
{
    if (!m_view) {
        m_view = createView();
        if (QNativeUIKitView *parent = q_func()->parentView())
            static_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(parent))->addSubView(m_view);
    }
    return m_view;
}

UIView *QNativeUIKitViewPrivate::view() const
{
    return const_cast<QNativeUIKitViewPrivate *>(this)->view();
}

UIView *QNativeUIKitViewPrivate::createView()
{
    UIView *view = [UIView new];
    view.backgroundColor = [UIColor whiteColor];
    return view;
}

void QNativeUIKitViewPrivate::addSubView(UIView *subView)
{
    CGRect alignmentRect = [subView alignmentRectForFrame:subView.frame];
    [view() addSubview:subView];
    // Ratio between frame and alignment rect can change depending on whether the view is
    // attached to a superview, so reset it after reparenting
    subView.frame = [subView frameForAlignmentRect:alignmentRect];
    subView.autoresizingMask =
            UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleBottomMargin;
}

CGRect QNativeUIKitViewPrivate::alignmentRect() const
{
    return [view() alignmentRectForFrame:view().frame];
}

void QNativeUIKitViewPrivate::setAlignmentRect(CGRect rect)
{
    view().frame = [view() frameForAlignmentRect:rect];
}

void QNativeUIKitViewPrivate::setGeometry(const QRectF &rect)
{
    setAlignmentRect(rect.toCGRect());
}

QNativeUIKitView::QNativeUIKitView(QNativeUIKitBase *parent)
    : QNativeUIKitBase(*new QNativeUIKitViewPrivate(), parent)
{
    d_func()->initConnections();
}

QNativeUIKitView::QNativeUIKitView(QNativeUIKitViewPrivate &dd, QNativeUIKitBase *parent)
    : QNativeUIKitBase(dd, parent)
{
    d_func()->initConnections();
}

QNativeUIKitView::~QNativeUIKitView()
{
}

bool QNativeUIKitView::visible() const
{
    return !d_func()->view().hidden;
}

void QNativeUIKitView::setVisible(bool newVisible)
{
    if (newVisible == visible())
        return;

    Q_D(QNativeUIKitView);
    d->view().hidden = !newVisible;

    emit visibleChanged(newVisible);
}

void QNativeUIKitView::setGeometry(const QRectF &rect)
{
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

void QNativeUIKitView::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    setX(posx);
    setY(posy);
    setWidth(w);
    setHeight(h);
}

void QNativeUIKitView::move(qreal posx, qreal posy)
{
    setX(posx);
    setY(posy);
}

void QNativeUIKitView::move(const QPointF &pos)
{
    setX(pos.x());
    setY(pos.y());
}

void QNativeUIKitView::resize(qreal width, qreal height)
{
    setWidth(width);
    setHeight(height);
}

void QNativeUIKitView::resize(const QSizeF size)
{
    setWidth(size.width());
    setHeight(size.height());
}

QSizeF QNativeUIKitView::implicitSize() const
{
    Q_D(const QNativeUIKitView);
    if (!d->m_implicitSize.isValid())
        const_cast<QNativeUIKitViewPrivate *>(d)->updateImplicitSize();
    return d->m_implicitSize;
}

qreal QNativeUIKitView::implicitWidth() const
{
    return implicitSize().width();
}

qreal QNativeUIKitView::implicitHeight() const
{
    return implicitSize().height();
}

QRectF QNativeUIKitView::geometry() const
{
    return QRectF::fromCGRect(d_func()->alignmentRect());
}

QRectF QNativeUIKitView::frameGeometry() const
{
    return QRectF::fromCGRect(d_func()->view().frame);
}

qreal QNativeUIKitView::x() const
{
    return geometry().x();
}

void QNativeUIKitView::setX(qreal newX)
{
    if (newX == x())
        return;

    Q_D(QNativeUIKitView);
    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitViewPrivate::MovedX);

    emit xChanged(newX);
}

qreal QNativeUIKitView::y() const
{
    return geometry().y();
}

void QNativeUIKitView::setY(qreal newY)
{
    if (newY == y())
        return;

    Q_D(QNativeUIKitView);
    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitViewPrivate::MovedY);

    emit yChanged(newY);
}

qreal QNativeUIKitView::width() const
{
    return geometry().width();
}

void QNativeUIKitView::setWidth(qreal newWidth)
{
    if (newWidth == width())
        return;

    Q_D(QNativeUIKitView);
    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitViewPrivate::ResizedWidth);

    emit widthChanged(newWidth);
}

qreal QNativeUIKitView::height() const
{
    return geometry().height();
}

void QNativeUIKitView::setHeight(qreal newHeight)
{
    if (newHeight == height())
        return;

    Q_D(QNativeUIKitView);
    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setGeometry(g);
    d->setAttribute(QNativeUIKitViewPrivate::ResizedHeight);

    emit heightChanged(newHeight);
}

qreal QNativeUIKitView::left() const
{
    return geometry().left();
}

qreal QNativeUIKitView::top() const
{
    return geometry().top();
}

qreal QNativeUIKitView::right() const
{
    return geometry().right();
}

qreal QNativeUIKitView::bottom() const
{
    return geometry().bottom();
}

QNativeUIKitView *QNativeUIKitView::parentView()
{
    return dynamic_cast<QNativeUIKitView *>(parent());
}

UIView *QNativeUIKitView::uiViewHandle()
{
   return d_func()->view();
}

bool QNativeUIKitView::setNativeParent(QObject *parent)
{
    if (QNativeUIKitView *p = dynamic_cast<QNativeUIKitView *>(parent))
        setParent(p);
    else
        return QNativeUIKitBase::setNativeParent(parent);
    return true;
}

bool QNativeUIKitView::setNativeParent(const QByteArray &type, void *parent)
{
    if (type == "UIView")
        [reinterpret_cast<UIView *>(parent) addSubview:uiViewHandle()];
    else
        return QNativeUIKitBase::setNativeParent(type, parent);
    return true;
}

bool QNativeUIKitView::addNativeChild(QObject *child)
{
    if (QNativeUIKitView *c = dynamic_cast<QNativeUIKitView *>(child))
        c->setParent(this);
    else
        return QNativeUIKitBase::addNativeChild(child);
    return true;
}

bool QNativeUIKitView::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "UIView")
        d_func()->addSubView(reinterpret_cast<UIView *>(child));
    else
        return QNativeUIKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QNativeUIKitView::supportedNativeChildTypes()
{
    return QNativeUIKitBase::supportedNativeChildTypes() << "UIView";
}

QByteArrayList QNativeUIKitView::supportedNativeParentTypes()
{
    return supportedNativeChildTypes();
}

void QNativeUIKitView::childEvent(QChildEvent *event)
{
    Q_D(QNativeUIKitView);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QNativeUIKitViewPrivate *dptr_child = dynamic_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    if (event->added()) {
        d->addSubView(dptr_child->view());
    } else if (event->removed()) {
        [dptr_child->view() removeFromSuperview];
    }
}

#include "moc_qnativeuikitview.cpp"

QT_END_NAMESPACE
