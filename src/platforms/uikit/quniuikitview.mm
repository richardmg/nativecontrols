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

const QEvent::Type kEventTypeEmitGeometryChangesLater = QEvent::User;

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
    , m_emitMaskToUseOnFrameChanged(0)
    , m_delayedEmitMask(0)
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
    Q_Q(QUniUIKitView);
    // This callback can either happen synchronously when setting geometry (frame)
    // from QUniUIKitView, or because of spontanious changes from UIKit (e.g orientation
    // change). In the former case we set a m_kvoEmitMask in the setter function
    // so we know which signal to emit. Otherwise we emit signals for all detected
    // changes.
    // The problem is that when we assign a frame to a uiview, UIKit might modify the
    // frame so that it ends up with a positive width and height. This causes problems
    // if you bind width to e.g 'width: parent.width - x', since if the expression ends
    // up negative, UIKit will 'flip' x and width, which means that we need to emit changed
    // signals for both. But, we can only emit a signal for the property currently being set
    // from QML, otherwise we can cause binding loops to happen (e.g if we emit xChanged in
    // the binding example above, when it sets a new width). As such, we need to emit the
    // remaining properties async later.

    Attributes changedMask = 0;
    CGRect actualRect = alignmentRect();

    if (m_x != actualRect.origin.x)
        changedMask |= MovedX;
    if (m_y != actualRect.origin.y)
        changedMask |= MovedY;
    if (m_width != actualRect.size.width)
        changedMask |= ResizedWidth;
    if (m_height != actualRect.size.height)
        changedMask |= ResizedHeight;

    m_x.setReadValue(actualRect.origin.x);
    m_y.setReadValue(actualRect.origin.y);
    m_width.setReadValue(actualRect.size.width);
    m_height.setReadValue(actualRect.size.height);

    if (m_emitMaskToUseOnFrameChanged == 0) {
        // Spontanious update not related to setting a qproperty.
        // Emit changes to all needed properties.
        m_emitMaskToUseOnFrameChanged = changedMask;
    } else {
        // Synchronous update as a result of setting a qproperty
        if (m_emitMaskToUseOnFrameChanged != changedMask) {
            // Properties other than the one expected has changed, so
            // we need to post an event and handle those later.
            m_delayedEmitMask |= changedMask;
            qApp->postEvent(q, new QEvent(kEventTypeEmitGeometryChangesLater));
        }
    }

    // Since we are about to emit the changes in m_kvoEmitMask, we can
    // remove them from m_qeventEmitMask so we don't emit them once more later.
    m_delayedEmitMask &= ~m_emitMaskToUseOnFrameChanged;

    emitGeometryChanges(m_emitMaskToUseOnFrameChanged);
    m_emitMaskToUseOnFrameChanged = 0;
}

void QUniUIKitViewPrivate::onEmitGeometryChangesLater()
{
    Q_Q(QUniUIKitView);
    qApp->removePostedEvents(q, kEventTypeEmitGeometryChangesLater);
    emitGeometryChanges(m_delayedEmitMask);
    m_delayedEmitMask = 0;
}

void QUniUIKitViewPrivate::emitGeometryChanges(Attributes emitFlags)
{
    Q_Q(QUniUIKitView);
    if (emitFlags & MovedX)
        emit q->xChanged(m_x);
    if (emitFlags & MovedY)
        emit q->yChanged(m_y);
    if (emitFlags & ResizedWidth)
        emit q->widthChanged(m_width);
    if (emitFlags & ResizedHeight)
        emit q->heightChanged(m_height);
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

    syncX();
    syncY();
    syncWidth();
    syncHeight();
    syncAlpha();
    syncBackgroundColor();
    syncVisible();
    syncIntrinsicContentWidth();
    syncIntrinsicContentHeight();

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

void QUniUIKitViewPrivate::updateGeometry(Attributes propertiesToUpdate)
{
    // When assigning a frame to a uiview, UIKit might modify the frame so that
    // it ends up with a positive width and height. This causes problems if you bind
    // e.g 'x: 10', and then width ends up negative, since then UIKit will 'swap' x and
    // width. So for that reason we store different read/write values for the
    // geometry variables (handled by the type), and always try to reapply the
    // written requested geometry whenever some of the values are updated.
    @try {
        m_emitMaskToUseOnFrameChanged = propertiesToUpdate;
        setAlignmentRect(CGRectMake(m_x.writeValue(), m_y.writeValue(), m_width.writeValue(), m_height.writeValue()));
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
        updateGeometry(MovedX);
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
        updateGeometry(MovedY);
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
        updateGeometry(ResizedWidth);
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
        updateGeometry(ResizedHeight);
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
    } else {
        float value = view().intrinsicContentSize.width;
        if (value != m_intrinsicContentWidth) {
            m_intrinsicContentWidth.reset(view().intrinsicContentSize.width);
            emit q_func()->intrinsicContentWidthChanged(value);
        }
    }
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
    } else {
        float value = view().intrinsicContentSize.height;
        if (value != m_intrinsicContentHeight) {
            m_intrinsicContentHeight.reset(view().intrinsicContentSize.height);
            emit q_func()->intrinsicContentHeightChanged(value);
        }
    }
}

void QUniUIKitViewPrivate::syncVisible()
{
    if (m_visible.hasExplicitValue())
        view().hidden = !m_visible;
    m_visible.reset(!view().hidden);
}

void QUniUIKitViewPrivate::syncAlpha()
{
    if (m_alpha.hasExplicitValue())
        view().alpha = m_alpha;
    m_alpha.reset(view().alpha);
}

void QUniUIKitViewPrivate::syncBackgroundColor()
{
    if (m_backgroundColor.hasExplicitValue())
        view().backgroundColor = qt_toUIColor(m_backgroundColor);
    m_backgroundColor.reset(qt_nsColorToQColor(view().backgroundColor));
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

bool QUniUIKitView::event(QEvent *event)
{
    Q_D(QUniUIKitView);
    switch (event->type()) {
    case kEventTypeEmitGeometryChangesLater:
        d->onEmitGeometryChangesLater();
        break;
    default:
        return QUniUIKitResponder::event(event);
    }
    return true;
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
