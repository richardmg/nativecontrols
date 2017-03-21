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

#include <QtGui/qwindow.h>
#include <QtCore/private/qobject_p.h>
#include <QtUniAppKitControls/quniappkitwindow.h>
#include <QtUniAppKitControls/quniappkitviewcontroller.h>
#include <QtUniAppKitControls/private/quniappkitwindow_p.h>
#include <QtUniAppKitControls/private/quniappkitviewcontroller_p.h>
#include <QtUniAppKitControls/private/quniappkitview_p.h>

@interface QtUniNSView : NSView

@end

@implementation QtUniNSView

- (BOOL)isFlipped
{
    static const bool useFlippedViews = qEnvironmentVariableIsSet("QT_UNI_MAC_USE_FLIPPED_NSVIEWS");
    return useFlippedViews ? YES : NO;
}

@end

@interface QUniAppKitWindowDelegate : NSObject <NSWindowDelegate> {
    QT_PREPEND_NAMESPACE(QUniAppKitWindowPrivate) *_window;
}

@end

@implementation QUniAppKitWindowDelegate

- (instancetype)initWithQUniAppKitWindowPrivate:(QT_PREPEND_NAMESPACE(QUniAppKitWindowPrivate) *)window
{
    self = [self init];
    if (self) {
        _window = window;
    }

    return self;
}

- (void)windowDidResize:(NSNotification *)notification
{
    NSWindow *window = (NSWindow *)notification.object;
    emit _window->q_func()->widthChanged(window.contentView.frame.size.width);
    emit _window->q_func()->heightChanged(window.contentView.frame.size.height);
}

@end

QT_BEGIN_NAMESPACE

QUniAppKitWindowPrivate::QUniAppKitWindowPrivate(int version)
    : QUniAppKitBasePrivate(version)
    , m_window(nullptr)
    , m_viewController(nullptr)
    , m_delegate(nullptr)
    , m_viewControllerSetExplicit(false)
{
}

QUniAppKitWindowPrivate::~QUniAppKitWindowPrivate()
{
    [m_window release];
}

void QUniAppKitWindowPrivate::connectSignals(QUniBase *base)
{
    Q_Q(QUniAppKitWindow);
    QUniAppKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QUniWindow *>(base);
    q->connect(q, &QUniAppKitWindow::widthChanged, b, &QUniWindow::widthChanged);
    q->connect(q, &QUniAppKitWindow::heightChanged, b, &QUniWindow::heightChanged);
    q->connect(q, &QUniAppKitWindow::visibleChanged, b, &QUniWindow::visibleChanged);
}

void QUniAppKitWindowPrivate::updateLayout(bool recursive)
{
    if (testAttribute(LayedOut))
        return;
    setAttribute(LayedOut);

    if (recursive) {
        for (QObject *child : q_func()->children()) {
            if (QUniAppKitViewPrivate *basePrivate = dynamic_cast<QUniAppKitViewPrivate *>(QObjectPrivate::get(child)))
                basePrivate->updateLayout(recursive);
        }
    }
}

void QUniAppKitWindowPrivate::setFrame(const QRectF &frame)
{
    [window() setFrame:frame.toCGRect() display:YES];
}

void QUniAppKitWindowPrivate::addSubViewToContentView(NSView *nsView)
{
    Q_Q(QUniAppKitWindow);
    QUniAppKitView *contentView = q->contentViewController()->view();
    QUniAppKitViewPrivate *dptr_contentView = dynamic_cast<QUniAppKitViewPrivate *>(QObjectPrivate::get(contentView));
    dptr_contentView->addSubView(nsView);
}

void QUniAppKitWindowPrivate::removeSubViewFromContentView(NSView *view)
{
    const BOOL hadSuperview = !!view.superview;
    const QRectF rect = qt_mac_flipRect(view.frame, view);
    [view removeFromSuperview];
    if (hadSuperview)
        view.frame = rect.toCGRect();
}

NSWindow *QUniAppKitWindowPrivate::window()
{
    if (m_window)
        return m_window;

    m_delegate = [[QUniAppKitWindowDelegate alloc] initWithQUniAppKitWindowPrivate:this];

    NSRect screenFrame = NSScreen.mainScreen.visibleFrame;
    NSRect windowFrame = NSMakeRect(0, 0,
                                    (NSInteger)(NSWidth(screenFrame) / 3),
                                    (NSInteger)(NSHeight(screenFrame) / 3));

    const auto styleMask = (NSWindowStyleMask)(NSWindowStyleMaskTitled |
                                               NSWindowStyleMaskClosable |
                                               NSWindowStyleMaskMiniaturizable |
                                               NSWindowStyleMaskResizable);

    m_window = [[NSWindow alloc] initWithContentRect:windowFrame
                                           styleMask:styleMask
                                             backing:NSBackingStoreBuffered
                                               defer:YES];
    m_window.delegate = m_delegate;

    return m_window;
}

QUniAppKitWindow::QUniAppKitWindow()
    : QUniAppKitBase(*new QUniAppKitWindowPrivate(), nullptr)
{
}

QUniAppKitWindow::QUniAppKitWindow(QUniAppKitWindowPrivate &dd)
    : QUniAppKitBase(dd, nullptr)
{
}

QUniAppKitWindow::~QUniAppKitWindow()
{
    Q_D(QUniAppKitWindow);
    [d->m_delegate release];
}

NSWindow *QUniAppKitWindow::nsWindowHandle()
{
    return d_func()->window();
}

void QUniAppKitWindow::setContentViewController(QUniAppKitViewController *controller)
{
    Q_D(QUniAppKitWindow);
    if (d->m_viewController == controller)
        return;

    d->m_viewControllerSetExplicit = true;
    d->m_viewController = controller;

    if (controller) {
        QRectF windowFrame = frame();
        nsWindowHandle().contentViewController = controller->nsViewControllerHandle();
        setFrame(windowFrame);
    } else {
        nsWindowHandle().contentViewController = nil;
    }

    emit contentViewControllerChanged(controller);
}

QUniAppKitViewController *QUniAppKitWindow::contentViewController() const
{
    Q_D(const QUniAppKitWindow);
    if (!d->m_viewController) {
        QUniAppKitWindow *self = const_cast<QUniAppKitWindow *>(this);
        self->setContentViewController(new QUniAppKitViewController(self));
        // Keep track of whether or not the view controller was created
        // by ourselves, in case we accidentally create one before
        // the app gets around to add one as a child.
        const_cast<QUniAppKitWindowPrivate *>(d)->m_viewControllerSetExplicit = false;
    }
    return d->m_viewController;
}

QRectF QUniAppKitWindow::frame() const
{
    return QRectF::fromCGRect(const_cast<QUniAppKitWindow *>(this)->nsWindowHandle().frame);
}

void QUniAppKitWindow::setFrame(const QRectF &frame)
{
    setGeometry(frame);
}

QRectF QUniAppKitWindow::contentRect() const
{
    return contentRectForFrameRect(frame());
}

QRectF QUniAppKitWindow::contentRectForFrameRect(const QRectF &rect) const
{
    NSWindow *window = const_cast<QUniAppKitWindow *>(this)->nsWindowHandle();
    return QRectF::fromCGRect([window contentRectForFrameRect:rect.toCGRect()]);
}

QRectF QUniAppKitWindow::frameRectForContentRect(const QRectF &rect) const
{
    NSWindow *window = const_cast<QUniAppKitWindow *>(this)->nsWindowHandle();
    return QRectF::fromCGRect([window frameRectForContentRect:rect.toCGRect()]);
}

bool QUniAppKitWindow::isVisible() const
{
    return const_cast<QUniAppKitWindow *>(this)->nsWindowHandle().visible;
}

void QUniAppKitWindow::setVisible(bool newVisible)
{
    if (newVisible == isVisible())
        return;

    [nsWindowHandle() setIsVisible:newVisible];
    if (newVisible) {
        // Now that the window becomes visible, we should check if any of its
        // children needs to be resized to implicit size. Since children
        // are added after the call to setVisible when using QML, we need to
        // post the update request.
        qApp->postEvent(this, new QEvent(QEvent::LayoutRequest));
        // Also, AppKit expects there to always be a content view controller
        // in a NSWindow, so if hasn't been added yet, create one now.
        contentViewController();
        [nsWindowHandle() makeKeyAndOrderFront:nsWindowHandle()];
    }

    emit visibleChanged(newVisible);
}

void QUniAppKitWindow::showFullScreen()
{
    if (!isVisible())
        setVisible(true);

    if (([nsWindowHandle() styleMask] & NSFullScreenWindowMask) != NSFullScreenWindowMask)
        [nsWindowHandle() toggleFullScreen:nsWindowHandle()];
}

QRectF QUniAppKitWindow::geometry() const
{
    return frame();
}

void QUniAppKitWindow::setGeometry(const QRectF &rect)
{
    setX(rect.x());
    setY(rect.y());
    setWidth(rect.width());
    setHeight(rect.height());
}

void QUniAppKitWindow::setGeometry(qreal posx, qreal posy, qreal w, qreal h)
{
    setX(posx);
    setY(posy);
    setWidth(w);
    setHeight(h);
}

void QUniAppKitWindow::setPosition(const QPointF &pos)
{
    setX(pos.x());
    setY(pos.y());
}

void QUniAppKitWindow::resize(const QSizeF size)
{
    setWidth(size.width());
    setHeight(size.height());
}

qreal QUniAppKitWindow::x() const
{
    return geometry().x();
}

void QUniAppKitWindow::setX(qreal newX)
{
    Q_D(QUniAppKitWindow);
    d->setAttribute(QUniAppKitWindowPrivate::MovedX);

    if (newX == x())
        return;

    QRectF g = geometry();
    g.moveLeft(newX);
    d_func()->setFrame(g);

    emit xChanged(newX);
}

qreal QUniAppKitWindow::y() const
{
    return geometry().y();
}

void QUniAppKitWindow::setY(qreal newY)
{
    Q_D(QUniAppKitWindow);
    d->setAttribute(QUniAppKitWindowPrivate::MovedY);

    if (newY == y())
        return;

    QRectF g = geometry();
    g.moveTop(newY);
    d_func()->setFrame(g);

    emit yChanged(newY);
}

qreal QUniAppKitWindow::width() const
{
    return geometry().width();
}

void QUniAppKitWindow::setWidth(qreal newWidth)
{
    Q_D(QUniAppKitWindow);
    d->setAttribute(QUniAppKitWindowPrivate::ResizedWidth);

    if (newWidth == width())
        return;

    QRectF g = geometry();
    g.setWidth(newWidth);
    d_func()->setFrame(g);

    emit widthChanged(newWidth);
}

qreal QUniAppKitWindow::height() const
{
    return geometry().height();
}

void QUniAppKitWindow::setHeight(qreal newHeight)
{
    Q_D(QUniAppKitWindow);
    d->setAttribute(QUniAppKitWindowPrivate::ResizedHeight);

    if (newHeight == height())
        return;

    QRectF g = geometry();
    g.setHeight(newHeight);
    d_func()->setFrame(g);

    emit heightChanged(newHeight);
}

bool QUniAppKitWindow::event(QEvent *e)
{
    Q_D(QUniAppKitWindow);
    switch (e->type()) {
    case QEvent::LayoutRequest:
        d->updateLayout(true);
    default:
        return QUniAppKitBase::event(e);
    }
    return true;
}

bool QUniAppKitWindow::addNativeChild(QObject *child)
{
    if (QUniAppKitView *c = qobject_cast<QUniAppKitView *>(child))
        c->setParent(this);
    else if (QUniAppKitViewController *c = qobject_cast<QUniAppKitViewController *>(child))
        c->setParent(this);
    else
        return QUniAppKitBase::addNativeChild(child);
    return true;
}

bool QUniAppKitWindow::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "NSView")
        d_func()->addSubViewToContentView(static_cast<NSView *>(child));
    else if (type == "NSViewController")
        nsWindowHandle().contentViewController = static_cast<NSViewController *>(child);
    else
        return QUniAppKitBase::addNativeChild(type, child);
    return true;
}

QByteArrayList QUniAppKitWindow::supportedNativeChildTypes()
{
    return QUniAppKitBase::supportedNativeChildTypes() << "NSView" << "NSViewController";
}

QByteArrayList QUniAppKitWindow::supportedNativeParentTypes()
{
    return QByteArrayList();
}

void QUniAppKitWindow::childEvent(QChildEvent *event)
{
    Q_D(QUniAppKitWindow);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QObject *child = event->child();

    if (QUniAppKitViewPrivate *dptr_child = dynamic_cast<QUniAppKitViewPrivate *>(QObjectPrivate::get(event->child()))) {
        if (event->added()) {
            // QUniAppKitView added as children of the window will have their
            // NSViews added as children of the view controller view instead.
            d->addSubViewToContentView(dptr_child->view());
        } else if (event->removed()) {
            d->removeSubViewFromContentView(dptr_child->view());
        }
    } else if (QUniAppKitViewControllerPrivate *dptr_child = dynamic_cast<QUniAppKitViewControllerPrivate *>(QObjectPrivate::get(child))) {
        if (event->added()) {
            if (!d->m_viewController || !d->m_viewControllerSetExplicit) {
                // If no view controller is set from before (other than the default
                // one), we let the first set child controller become the root view controller.
                setContentViewController(dptr_child->q_func());
            }
        } else if (event->removed()) {
            if (dptr_child->q_func() == d->m_viewController)
                setContentViewController(nullptr);
        }
    }
}

#include "moc_quniappkitwindow.cpp"

QT_END_NAMESPACE
