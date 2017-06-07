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

#include <QtUniUIKitControls/quniuikitview.h>
#include <QtUniUIKitControls/private/quniuikitview_p.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

@interface QUniUIView : UIView
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>
@end

@implementation QUniUIView
#define QUNI_INTERFACE_IMPLEMENTATION
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>
@end

QT_BEGIN_NAMESPACE

static UIColor *qt_toUIColor(const QColor &qcolor)
{
    return [UIColor
            colorWithRed:qcolor.red()/ 255.
            green:qcolor.green() / 255.
            blue:qcolor.blue() / 255.
            alpha:qcolor.alpha() / 255.];
}

static QColor qt_nsColorToQColor(UIColor *uiColor)
{
    CGFloat r, g, b, a;
    [uiColor getRed:&r green:&g blue:&b alpha:&a];
    return QColor::fromRgba(qRgba(r * 255, g * 255, b * 255, a * 255));
}

QUniUIKitViewPrivate::QUniUIKitViewPrivate(int version)
    : QUniUIKitResponderPrivate(version)
    , m_sizeToFit(false)
{
}

QUniUIKitViewPrivate::~QUniUIKitViewPrivate()
{
}

void QUniUIKitViewPrivate::initConnections()
{
    Q_Q(QUniUIKitView);
    q->connect(q, &QUniUIKitView::xChanged, q, [q](){ emit q->rightChanged(q->right()); });
    q->connect(q, &QUniUIKitView::yChanged, q, [q](){ emit q->bottomChanged(q->bottom()); });
    q->connect(q, &QUniUIKitView::widthChanged, q, [q](){ emit q->rightChanged(q->right()); });
    q->connect(q, &QUniUIKitView::heightChanged, q, [q](){ emit q->bottomChanged(q->bottom()); });
}

void QUniUIKitViewPrivate::onFrameChanged()
{
    // This callback can either happen async when setting geometry (frame)
    // from QUniUIKitView, or because of spontanious changes from UIKit (e.g orientation
    // change).
    // Note that when we assign a frame to a uiview, UIKit might modify the
    // frame so that it ends up with a positive width and height. This causes problems
    // if you bind width to e.g 'width: parent.width - x', since if the expression ends
    // up negative, UIKit will 'flip' x and width. For those cases it means that we might
    // temporary report "wrong" geometry until we get this callback and read the actual
    // values.

    Q_Q(QUniUIKitView);
    CGRect actualRect = alignmentRect();

    if (m_x != actualRect.origin.x) {
        m_x.setReadValue(actualRect.origin.x);
        emit q->xChanged(m_x);
    }

    if (m_y != actualRect.origin.y) {
        m_y.setReadValue(actualRect.origin.y);
        emit q->yChanged(m_y);
    }

    if (m_width != actualRect.size.width) {
        m_width.setReadValue(actualRect.size.width);
        emit q->widthChanged(m_width);
    }

    if (m_height != actualRect.size.height) {
        m_height.setReadValue(actualRect.size.height);
        emit q->heightChanged(m_height);
    }
}

void QUniUIKitViewPrivate::updateIntrinsicContentSize()
{
    // This function should be called whenever the view
    // changes properties that can affect intrinsic size.

    if (!isNSObjectCreated())
        return;

    syncIntrinsicContentWidth();
    syncIntrinsicContentHeight();
}

UIView *QUniUIKitViewPrivate::view() const
{
    return static_cast<UIView *>(nsObject());
}

void QUniUIKitViewPrivate::setNSObject(NSObject *nsObject)
{
    Q_Q(QUniUIKitView);
    QUniUIKitBasePrivate::setNSObject(nsObject);
    UIView *v = static_cast<UIView *>(nsObject);

    syncIntrinsicContentWidth();
    syncIntrinsicContentHeight();
    syncX();
    syncY();
    syncWidth();
    syncHeight();
    syncAlpha();
    syncBackgroundColor();
    syncVisible();

    if (QUniUIKitView *qparentView = q->parentView())
        qparentView->d_func()->addSubView(v);
}

void QUniUIKitViewPrivate::createNSObject()
{
    UIView *view = [[QUniUIView new] autorelease];
    view.backgroundColor = [UIColor whiteColor];
    setNSObject(view);
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

void QUniUIKitViewPrivate::updateGeometry()
{
    // When assigning a frame to a uiview, UIKit might modify the frame so that
    // it ends up with a positive width and height. This causes problems if you bind
    // e.g 'x: 10', and then width ends up negative, since then UIKit will 'swap' x and
    // width. So for that reason we store different read/write values for the
    // geometry variables (handled by the type), and always try to reapply the
    // written requested geometry whenever some of the values are updated.
    @try {
        setAlignmentRect(CGRectMake(m_x.writeValue(), m_y.writeValue(), m_width.writeValue(), m_height.writeValue()));
        [view() setNeedsLayout];
    } @catch (NSException *) {
        // QML can sometimes end up evaluating a geometry
        // binding to NaN. And trying to set that on a UIView
        // will cause a CALayerInvalidGeometry exception to be
        // thrown. We choose to ignore this here, and trust the
        // app to set a valid geometry later.
    }
}

void QUniUIKitViewPrivate::syncX()
{
    if (m_x.hasExplicitValue()) {
        updateGeometry();
        emit q_func()->xChanged(m_x);
    } else {
        float value = alignmentRect().origin.x;
        if (m_x != value) {
            m_x.setReadValue(value);
            emit q_func()->xChanged(m_x);
        }
    }
}

void QUniUIKitViewPrivate::syncY()
{
    if (m_y.hasExplicitValue()) {
        updateGeometry();
        emit q_func()->yChanged(m_y);
    } else {
        float value = alignmentRect().origin.y;
        if (m_y != value) {
            m_y.setReadValue(value);
            emit q_func()->yChanged(m_y);
        }
    }
}

void QUniUIKitViewPrivate::syncWidth()
{
    if (m_width.hasExplicitValue()) {
        updateGeometry();
        emit q_func()->widthChanged(m_width);
    } else {
        float value = alignmentRect().size.width;
        if (m_width != value) {
            m_width.setReadValue(value);
            emit q_func()->widthChanged(m_width);
        }
    }
}

void QUniUIKitViewPrivate::syncHeight()
{
    if (m_height.hasExplicitValue()) {
        updateGeometry();
        emit q_func()->heightChanged(m_height);
    } else {
        float value = alignmentRect().size.height;
        if (m_height != value) {
            m_height.setReadValue(value);
            emit q_func()->heightChanged(m_height);
        }
    }
}

void QUniUIKitViewPrivate::syncIntrinsicContentWidth()
{
    if (m_intrinsicContentWidth.hasExplicitValue()) {
        if (![view() respondsToSelector:@selector(setIntrinsicContentSize:)]) {
            qWarning("Warning: Cannot set intrinsicContentWidth for %s",
                     qPrintable(QString::fromNSString(NSStringFromClass([view() class]))));
            return;
        }
        CGSize size = CGSizeMake(m_intrinsicContentWidth, m_intrinsicContentHeight);
        static_cast<QUniUIView *>(view()).intrinsicContentSize = size;
        emit q_func()->intrinsicContentWidthChanged(m_intrinsicContentWidth);
    } else {
        float value = view().intrinsicContentSize.width;
        if (value != m_intrinsicContentWidth) {
            m_intrinsicContentWidth.reset(view().intrinsicContentSize.width);
            emit q_func()->intrinsicContentWidthChanged(m_intrinsicContentWidth);
        }
    }

    syncSizeToFit();
}

void QUniUIKitViewPrivate::syncIntrinsicContentHeight()
{
    if (m_intrinsicContentHeight.hasExplicitValue()) {
        if (![view() respondsToSelector:@selector(setIntrinsicContentSize:)]) {
            qWarning("Warning: Cannot set intrinsicContentHeight for %s",
                     qPrintable(QString::fromNSString(NSStringFromClass([view() class]))));
            return;
        }
        CGSize size = CGSizeMake(m_intrinsicContentWidth, m_intrinsicContentHeight);
        static_cast<QUniUIView *>(view()).intrinsicContentSize = size;
        emit q_func()->intrinsicContentHeightChanged(m_intrinsicContentHeight);
    } else {
        float value = view().intrinsicContentSize.height;
        if (value != m_intrinsicContentHeight) {
            m_intrinsicContentHeight.reset(view().intrinsicContentSize.height);
            emit q_func()->intrinsicContentHeightChanged(m_intrinsicContentHeight);
        }
    }

    syncSizeToFit();
}

void QUniUIKitViewPrivate::syncSizeToFit()
{
    if (!m_sizeToFit)
        return;

    if (!m_width.hasExplicitValue()) {
        // Implement an implicit binding "width:
        // intrinsicContentWidth" when width is unspecified
        if (m_width != m_intrinsicContentWidth) {
            m_width.reset(m_intrinsicContentWidth);
            updateGeometry();
            emit q_func()->widthChanged(m_width);
        }
    }

    if (!m_height.hasExplicitValue()) {
        // Implement an implicit binding "height:
        // intrinsicContentHeight" when height is unspecified
        if (m_height != m_intrinsicContentHeight) {
            m_height.reset(m_intrinsicContentHeight);
            updateGeometry();
            emit q_func()->heightChanged(m_height);
        }
    }
}

void QUniUIKitViewPrivate::syncVisible()
{
    if (m_visible.hasExplicitValue())
        view().hidden = !m_visible;
    m_visible.reset(!view().hidden);
    emit q_func()->visibleChanged(m_visible);
}

void QUniUIKitViewPrivate::syncAlpha()
{
    if (m_alpha.hasExplicitValue())
        view().alpha = m_alpha;
    m_alpha.reset(view().alpha);
    emit q_func()->alphaChanged(m_alpha);
}

void QUniUIKitViewPrivate::syncBackgroundColor()
{
    if (m_backgroundColor.hasExplicitValue())
        view().backgroundColor = qt_toUIColor(m_backgroundColor);
    m_backgroundColor.reset(qt_nsColorToQColor(view().backgroundColor));
    emit q_func()->backgroundColorChanged(m_backgroundColor);
}

QUniUIKitView::QUniUIKitView(QUniUIKitBase *parent)
    : QUniUIKitResponder(*new QUniUIKitViewPrivate(), parent)
{
    d_func()->initConnections();
}

QUniUIKitView::QUniUIKitView(UIView *view, QUniUIKitBase *parent)
    : QUniUIKitResponder(*new QUniUIKitViewPrivate(), parent)
{
    Q_D(QUniUIKitView);
    d->setNSObject(view);
    d->initConnections();
}

QUniUIKitView::QUniUIKitView(QUniUIKitViewPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitResponder(dd, parent)
{
    d_func()->initConnections();
}

QUniUIKitView::~QUniUIKitView()
{
}

SYNTHESIZE_QPROPERTY_CACHED(x, X, qreal, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(y, Y, qreal, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(width, Width, qreal, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(height, Height, qreal, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(intrinsicContentWidth, IntrinsicContentWidth, qreal, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(intrinsicContentHeight, IntrinsicContentHeight, qreal, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(sizeToFit, SizeToFit, bool, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(visible, Visible, bool, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(alpha, Alpha, qreal, QUniUIKitView)
SYNTHESIZE_QPROPERTY_CACHED(backgroundColor, BackgroundColor, QColor, QUniUIKitView)

QRectF QUniUIKitView::geometry() const
{
    Q_D(const QUniUIKitView);
    return QRectF(d->m_x, d->m_y, d->m_width, d->m_height);
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

QSizeF QUniUIKitView::intrinsicSize() const
{
    Q_D(const QUniUIKitView);
    return QSizeF(d->m_intrinsicContentWidth, d->m_intrinsicContentHeight);
}

void QUniUIKitView::setIntrinsicSize(const QSizeF &size)
{
    setIntrinsicContentWidth(size.width());
    setIntrinsicContentHeight(size.height());
}

QRectF QUniUIKitView::frameGeometry() const
{
    return QRectF::fromCGRect(d_func()->view().frame);
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

void QUniUIKitView::childEvent(QChildEvent *event)
{
    Q_D(QUniUIKitView);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QUniUIKitViewPrivate *dptr_child = dynamic_cast<QUniUIKitViewPrivate *>(QObjectPrivate::get(event->child()));
    if (!dptr_child)
        return;

    if (!dptr_child->isNSObjectCreated()) {
        // Delay setting up the parent-child relationship on the UIViews as long as possible.
        // This is especially important to support dynamic object creation from QML like
        // 'uiTableViewCellComponent.createObject(tableView, { reuseIdentifier: id });', where
        // reuseIdentifier cannot be set/changed after the view has been created.
        return;
    }

    if (event->added()) {
        d->addSubView(dptr_child->view());
    } else if (event->removed()) {
        [dptr_child->view() removeFromSuperview];
    }
}

#include "moc_quniuikitview.cpp"

QT_END_NAMESPACE
