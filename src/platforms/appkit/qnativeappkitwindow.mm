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
#include <QtNativeAppKitControls/qnativeappkitwindow.h>
#include <QtNativeAppKitControls/qnativeappkitviewcontroller.h>
#include <QtNativeAppKitControls/private/qnativeappkitwindow_p.h>
#include <QtNativeAppKitControls/private/qnativeappkitviewcontroller_p.h>
#include <QtNativeAppKitControls/private/qnativeappkitview_p.h>

@interface QtNativeNSView : NSView

@end

@implementation QtNativeNSView

- (BOOL)isFlipped
{
    static const bool useFlippedViews = qEnvironmentVariableIsSet("QT_NATIVE_MAC_USE_FLIPPED_NSVIEWS");
    return useFlippedViews ? YES : NO;
}

@end

@interface QNativeAppKitWindowDelegate : NSObject <NSWindowDelegate> {
    QT_PREPEND_NAMESPACE(QNativeAppKitWindowPrivate) *_window;
}

@end

@implementation QNativeAppKitWindowDelegate

- (instancetype)initWithQNativeAppKitWindowPrivate:(QT_PREPEND_NAMESPACE(QNativeAppKitWindowPrivate) *)window
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

QNativeAppKitWindowPrivate::QNativeAppKitWindowPrivate(int version)
    : QNativeAppKitViewPrivate(version)
    , m_window(nullptr)
    , m_viewController(nullptr)
    , m_viewControllerSetExplicit(false)
{
}

QNativeAppKitWindowPrivate::~QNativeAppKitWindowPrivate()
{
    [m_window release];
}

void QNativeAppKitWindowPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeAppKitWindow);
    QNativeAppKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QNativeWindow *>(base);
    q->connect(q, &QNativeAppKitWindow::widthChanged, b, &QNativeWindow::widthChanged);
    q->connect(q, &QNativeAppKitWindow::heightChanged, b, &QNativeWindow::heightChanged);
    q->connect(q, &QNativeAppKitWindow::visibleChanged, b, &QNativeWindow::visibleChanged);
}

void QNativeAppKitWindowPrivate::updateLayout(bool recursive)
{
    if (testAttribute(LayedOut))
        return;
    setAttribute(LayedOut);

    if (recursive) {
        for (QObject *child : q_func()->children()) {
            if (QNativeAppKitViewPrivate *basePrivate = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(child)))
                basePrivate->updateLayout(recursive);
        }
    }
}

void QNativeAppKitWindowPrivate::addSubViewToContentView(NSView *nsView)
{
    Q_Q(QNativeAppKitWindow);
    QNativeAppKitView *contentView = q->rootViewController()->view();
    QNativeAppKitViewPrivate *dptr_contentView = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(contentView));
    dptr_contentView->addSubView(nsView);
}

NSView *QNativeAppKitWindowPrivate::createView()
{
    m_delegate = [[QNativeAppKitWindowDelegate alloc] initWithQNativeAppKitWindowPrivate:this];

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

    return m_window.contentView;
}

QNativeAppKitWindow::QNativeAppKitWindow()
    : QNativeAppKitView(*new QNativeAppKitWindowPrivate(), nullptr)
{
}

QNativeAppKitWindow::QNativeAppKitWindow(QNativeAppKitWindowPrivate &dd)
    : QNativeAppKitView(dd, nullptr)
{
}

QNativeAppKitWindow::~QNativeAppKitWindow()
{
    Q_D(QNativeAppKitWindow);
    [d->m_delegate release];
}

NSWindow *QNativeAppKitWindow::nsWindowHandle()
{
    return d_func()->view().window;
}

void QNativeAppKitWindow::setRootViewController(QNativeAppKitViewController *controller)
{
    Q_D(QNativeAppKitWindow);
    if (d->m_viewController == controller)
        return;

    d->m_viewControllerSetExplicit = true;
    d->m_viewController = dynamic_cast<QNativeAppKitViewController *>(controller);
    [d->m_viewController->nsViewControllerHandle().view setFrame:nsWindowHandle().contentView.frame]; // TODO: Determine how to handle view controller resizing
    nsWindowHandle().contentViewController = d->m_viewController->nsViewControllerHandle();
    emit rootViewControllerChanged(controller);
}

QNativeAppKitViewController *QNativeAppKitWindow::rootViewController() const
{
    Q_D(const QNativeAppKitWindow);
    if (!d->m_viewController) {
        QNativeAppKitWindow *self = const_cast<QNativeAppKitWindow *>(this);
        self->setRootViewController(new QNativeAppKitViewController(self));
        // Keep track of whether or not the view controller was created
        // by ourselves, in case we accidentally create one before
        // the app gets around to add one as a child.
        const_cast<QNativeAppKitWindowPrivate *>(d)->m_viewControllerSetExplicit = false;
    }
    return d->m_viewController;
}

QRectF QNativeAppKitWindow::geometry() const
{
    const NSRect r = [d_func()->m_window contentRectForFrameRect:d_func()->m_window.frame];
    return QRectF(r.origin.x, r.origin.y, r.size.width, r.size.height);
}

NSRect qt_mac_flipRect(const QRectF &rect, NSView *view);

void QNativeAppKitWindow::setGeometry(const QRectF &rect)
{
    [nsWindowHandle() setFrame:[nsWindowHandle() frameRectForContentRect:
      NSMakeRect(rect.x(), rect.y(), rect.width(), rect.height())] display:YES];
}

QRectF QNativeAppKitWindow::frameGeometry() const
{
    const NSRect frame = d_func()->m_window.frame;
    return QRectF(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
}

qreal QNativeAppKitWindow::width() const
{
    return QNativeAppKitView::width();
}

qreal QNativeAppKitWindow::height() const
{
    return QNativeAppKitView::height();
}

bool QNativeAppKitWindow::isVisible() const
{
    return d_func()->m_window.visible;
}

void QNativeAppKitWindow::setVisible(bool newVisible)
{
    if (newVisible == isVisible())
        return;

    [d_func()->m_window setIsVisible:newVisible];
    if (newVisible) {
        // Now that the window becomes visible, we should check if any of its
        // children needs to be resized to implicit size. Since children
        // are added after the call to setVisible when using QML, we need to
        // post the update request.
        qApp->postEvent(this, new QEvent(QEvent::LayoutRequest));
        // Also, AppKit expects there to always be a root view controller
        // in a NSWindow, so if hasn't been added yet, create one now.
        rootViewController();
        [d_func()->m_window makeKeyAndOrderFront:d_func()->m_window];
    }

    emit visibleChanged(newVisible);
}

void QNativeAppKitWindow::showFullScreen()
{
    if (!isVisible())
        setVisible(true);

    if (([d_func()->m_window styleMask] & NSFullScreenWindowMask) != NSFullScreenWindowMask)
        [d_func()->m_window toggleFullScreen:d_func()->m_window];

}

bool QNativeAppKitWindow::event(QEvent *e)
{
    Q_D(QNativeAppKitWindow);
    switch (e->type()) {
    case QEvent::LayoutRequest:
        d->updateLayout(true);
    default:
        return QNativeAppKitBase::event(e);
    }
    return true;

}

void QNativeAppKitWindow::childEvent(QChildEvent *event)
{
    Q_D(QNativeAppKitWindow);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QObject *child = event->child();

    if (QNativeAppKitViewPrivate *dptr_child = dynamic_cast<QNativeAppKitViewPrivate *>(QObjectPrivate::get(event->child()))) {
        if (event->added()) {
            // QNativeAppKitView added as children of the window will have their
            // NSViews added as children of the view controller view instead.
            d->addSubViewToContentView(dptr_child->view());
        } else if (event->removed()) {
            d->removeSubView(dptr_child->view());
        }
    } else if (QNativeAppKitViewControllerPrivate *dptr_child = dynamic_cast<QNativeAppKitViewControllerPrivate *>(QObjectPrivate::get(child))) {
        if (event->added()) {
            if (!d->m_viewController || !d->m_viewControllerSetExplicit) {
                // If no view controller is set from before (other than the default
                // one), we let the first set child controller become the root view controller.
                setRootViewController(dptr_child->q_func());
            }
        } else if (event->removed()) {
            if (dptr_child->q_func() == d->m_viewController)
                setRootViewController(nullptr);
        }
    }
}

#include "moc_qnativeappkitwindow.cpp"

QT_END_NAMESPACE
