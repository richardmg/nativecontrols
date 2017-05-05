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

static void *KVOFrameChanged = &KVOFrameChanged;

@interface QPlainUIKitView : UIView
@property (nonatomic, readwrite) CGSize intrinsicContentSize;
@end

@implementation QPlainUIKitView
@end

@interface QUniUIKitViewDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniUIKitViewPrivate) *_view;
}
@end

@implementation QUniUIKitViewDelegate

-(id)initWithQUniUIKitViewPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitViewPrivate) *)view
{
    self = [self init];
    if (self) {
        _view = view;
    }

    return self;
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    Q_UNUSED(keyPath);
    Q_UNUSED(object);
    Q_UNUSED(change);

    if (context == KVOFrameChanged)
        _view->emitFrameChanged();
    else
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
}
@end

QT_BEGIN_NAMESPACE

QUniUIKitViewPrivate::QUniUIKitViewPrivate(int version)
    : QUniUIKitBasePrivate(version)
    , m_attributes(0)
    , m_view(nil)
    , m_delegate(nullptr)
#ifdef QT_DEBUG
    , m_createViewRecursionGuard(false)
#endif
{
}

QUniUIKitViewPrivate::~QUniUIKitViewPrivate()
{
    if (m_view) {
        @try {
            [m_view removeObserver:m_delegate forKeyPath:@"frame" context:NULL];
        } @catch (NSException *) {
            // Work-around: if that app starts, but ends, before the app 'didFinishLaunching'
            // (which happens when running auto tests), we get a NSRangeException telling us that
            // we never "registered as an observer". Which is wrong, and we therefore ignore.
        }

        dispatch_async(dispatch_get_main_queue (), ^{
            // Because KVO removeObserver above is not executed by UIKit straight away, we
            // get an 'NSInternalInconsistencyException' if we release m_view directly
            // after. So, work around this for now by postponing the release.
            [m_view release];
            [m_delegate release];
        });
    }
}

void QUniUIKitViewPrivate::initConnections()
{
    Q_Q(QUniUIKitView);
    q->connect(q, &QUniUIKitView::xChanged, q, &QUniUIKitView::rightChanged);
    q->connect(q, &QUniUIKitView::yChanged, q, &QUniUIKitView::bottomChanged);
    q->connect(q, &QUniUIKitView::widthChanged, q, &QUniUIKitView::rightChanged);
    q->connect(q, &QUniUIKitView::heightChanged, q, &QUniUIKitView::bottomChanged);
}

void QUniUIKitViewPrivate::emitFrameChanged()
{
    Q_Q(QUniUIKitView);

    // Update m_lastEmittedFrame before emitting signals
    // to avoid recursive binding loops. This can happen if
    // e.g changing width causes x to changes as well, since
    // then we enter here recursively.
    QRectF frame = q->frameGeometry();
    QRectF lastFrame = m_lastEmittedFrame;
    m_lastEmittedFrame = frame;

    if (frame.x() != lastFrame.x())
        emit q->xChanged(frame.x());
    if (frame.y() != lastFrame.y())
        emit q->yChanged(frame.y());
    if (frame.width() != lastFrame.width())
        emit q->widthChanged(frame.width());
    if (frame.height() != lastFrame.height())
        emit q->heightChanged(frame.height());
}

void QUniUIKitViewPrivate::updateIntrinsicContentSize()
{
    // This function should be called whenever the view
    // changes properties that can affect intrinsic size.
    Q_Q(QUniUIKitView);
    QSizeF oldSize = m_intrinsicContentSize;
    CGSize newSize = view().intrinsicContentSize;

    if (newSize.width != oldSize.width()) {
        m_intrinsicContentSize.setWidth(newSize.width);
        emit q->intrinsicContentWidthChanged(newSize.width);
    }

    if (newSize.height != oldSize.height()) {
        m_intrinsicContentSize.setHeight(newSize.height);
        emit q->intrinsicContentHeightChanged(newSize.height);
    }
}

UIView *QUniUIKitViewPrivate::view()
{
    if (!m_view) {
#ifdef QT_DEBUG
        // Check that we don't end up calling view() from createView(). This can
        // easily happen if we e.g create several views inside createView, and
        // construct parent-child relationships. The solution is to call setView
        // early on from within createView() before creating child views.
        Q_ASSERT(!m_createViewRecursionGuard);
        m_createViewRecursionGuard = true;
#endif
        // The common case should be that we enter this block to lazy create the UIView
        // we wrap when someone actually needs it (which is usually when properties
        // are assigned values, or another QUniUIKitView is set as child). But for
        // subclasses that adopts an already existing UIView, e.g to wrap read-only
        // UIView properties in other UIViews (like UITableViewCell.label), calling
        // setView early on is necessary.
        createView();
        Q_ASSERT(m_view);
    }
    return m_view;
}

UIView *QUniUIKitViewPrivate::view() const
{
    return const_cast<QUniUIKitViewPrivate *>(this)->view();
}

void QUniUIKitViewPrivate::setView(UIView *view)
{
    Q_ASSERT_X(!m_view, Q_FUNC_INFO, "setView should only be called once");
    m_view = [view retain];

    if (QUniUIKitView *qparentView = q_func()->parentView()) {
        // Let the UIView hierarchy mirror the QUniUIKitView hierarchy
        qparentView->d_func()->addSubView(m_view);
    }

    // UIKit will sometimes change the frame of a view on it's own.
    // This will e.g happen for the root view inside a view controller
    // upon orientation change, or when the root view inside a tab is
    // made visible the first time.
    // Since we only wrap the native controls, and as such, cannot easily
    // override methods like "updateSubviews", we choose to use the
    // infamous KVO pattern to catch the frame changes for now, so that
    // we always emit signals when the frame changes.
    qt_setAssociatedQObject(m_view, q_func());
    m_delegate = [[QUniUIKitViewDelegate alloc] initWithQUniUIKitViewPrivate:this];
    [m_view addObserver:m_delegate forKeyPath:@"frame" options:0 context:KVOFrameChanged];
}

void QUniUIKitViewPrivate::createView()
{
    UIView *view = [[QPlainUIKitView new] autorelease];
    view.backgroundColor = [UIColor whiteColor];
    setView(view);
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
    @try {
        setAlignmentRect(rect.toCGRect());
    } @catch (NSException *) {
        // QML can sometimes end up evaluating a geometry
        // binding to NaN. And trying to set that on a UIView
        // will cause a CALayerInvalidGeometry exception to be
        // thrown. We choose to ignore this here, and trust the
        // app to set a valid geometry later.
    }
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

QSizeF QUniUIKitView::intrinsicSize() const
{
    return QSizeF::fromCGSize(d_func()->view().intrinsicContentSize);
}

void QUniUIKitView::setIntrinsicSize(const QSizeF &size)
{
    setIntrinsicContentWidth(size.width());
    setIntrinsicContentHeight(size.height());
}

qreal QUniUIKitView::intrinsicContentWidth() const
{
    return d_func()->view().intrinsicContentSize.width;
}

void QUniUIKitView::setIntrinsicContentWidth(qreal width)
{
    Q_D(QUniUIKitView);

    CGSize size = d->view().intrinsicContentSize;
    if (width == size.width)
        return;

    if (![d->view() respondsToSelector:@selector(setIntrinsicContentSize:)]) {
        qWarning("Warning: Cannot set intrinsicContentWidth for %s",
                 qPrintable(QString::fromNSString(NSStringFromClass([d->view() class]))));
        return;
    }

    size.width = width;
    static_cast<QPlainUIKitView *>(d->view()).intrinsicContentSize = size;

    emit intrinsicContentWidthChanged(width);
}

qreal QUniUIKitView::intrinsicContentHeight() const
{
    return d_func()->view().intrinsicContentSize.height;
}

void QUniUIKitView::setIntrinsicContentHeight(qreal height)
{
    Q_D(QUniUIKitView);

    CGSize size = d->view().intrinsicContentSize;
    if (height == size.height)
        return;

    if (![d->view() respondsToSelector:@selector(setIntrinsicContentSize:)]) {
        qWarning("Warning: Cannot set intrinsicContentHeight for %s",
                 qPrintable(QString::fromNSString(NSStringFromClass([d->view() class]))));
        return;
    }

    size.height = height;
    static_cast<QPlainUIKitView *>(d->view()).intrinsicContentSize = size;

    emit intrinsicContentHeightChanged(height);
}

QColor QUniUIKitView::backgroundColor() const
{
    CGFloat r, g, b, a;
    [d_func()->view().backgroundColor getRed:&r green:&g blue:&b alpha:&a];
    return QColor::fromRgba(qRgba(r * 255, g * 255, b * 255, a * 255));
}

void QUniUIKitView::setBackgroundColor(const QColor &color)
{
    if (backgroundColor() == color)
        return;

    uiViewHandle().backgroundColor = [UIColor
            colorWithRed:color.red() / 255.
            green:color.green() / 255.
            blue:color.blue() / 255.
            alpha:color.alpha() / 255.];

    emit backgroundColorChanged(color);
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

    if (!dptr_child->isViewCreated()) {
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
