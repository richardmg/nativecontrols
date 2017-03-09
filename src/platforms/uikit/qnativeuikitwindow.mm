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

#include <QtGui/qwindow.h>
#include <QtCore/private/qobject_p.h>
#include <QtNativeUIKitControls/qnativeuikitwindow.h>
#include <QtNativeUIKitControls/qnativeuikitviewcontroller.h>
#include <QtNativeUIKitControls/private/qnativeuikitwindow_p.h>
#include <QtNativeUIKitControls/private/qnativeuikitviewcontroller_p.h>
#include <QtNativeUIKitControls/private/qnativeuikitview_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitWindowPrivate::QNativeUIKitWindowPrivate(int version)
    : QNativeUIKitViewPrivate(version)
    , m_viewController(nullptr)
    , m_viewControllerSetExplicit(false)
{
}

QNativeUIKitWindowPrivate::~QNativeUIKitWindowPrivate()
{
}

void QNativeUIKitWindowPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeUIKitWindow);
    QNativeUIKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QNativeWindow *>(base);
    q->connect(q, &QNativeUIKitWindow::visibleChanged, b, &QNativeWindow::visibleChanged);
}

void QNativeUIKitWindowPrivate::updateLayout(bool recursive)
{
    if (testAttribute(LayedOut))
        return;
    setAttribute(LayedOut);

    if (recursive) {
        for (QObject *child : q_func()->children()) {
            if (QNativeUIKitViewPrivate *basePrivate = dynamic_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(child)))
                basePrivate->updateLayout(recursive);
        }
    }
}

void QNativeUIKitWindowPrivate::addSubViewToContentView(UIView *uiView)
{
    Q_Q(QNativeUIKitWindow);
    QNativeUIKitView *contentView = q->rootViewController()->view();
    QNativeUIKitViewPrivate *dptr_contentView = dynamic_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(contentView));
    dptr_contentView->addSubView(uiView);
}

UIView *QNativeUIKitWindowPrivate::createView()
{
    return [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
}

QNativeUIKitWindow::QNativeUIKitWindow()
    : QNativeUIKitView(*new QNativeUIKitWindowPrivate(), nullptr)
{
}

QNativeUIKitWindow::QNativeUIKitWindow(QNativeUIKitWindowPrivate &dd)
    : QNativeUIKitView(dd, nullptr)
{
}

QNativeUIKitWindow::~QNativeUIKitWindow()
{
}

UIWindow *QNativeUIKitWindow::uiWindowHandle()
{
    return static_cast<UIWindow *>(d_func()->view());
}

void QNativeUIKitWindow::setRootViewController(QNativeUIKitViewController *controller)
{
    Q_D(QNativeUIKitWindow);
    if (d->m_viewController == controller)
        return;

    d->m_viewControllerSetExplicit = true;
    d->m_viewController = dynamic_cast<QNativeUIKitViewController *>(controller);
    uiWindowHandle().rootViewController = d->m_viewController->uiViewControllerHandle();
    emit rootViewControllerChanged(controller);
}

QNativeUIKitViewController *QNativeUIKitWindow::rootViewController() const
{
    Q_D(const QNativeUIKitWindow);
    if (!d->m_viewController) {
        QNativeUIKitWindow *self = const_cast<QNativeUIKitWindow *>(this);
        self->setRootViewController(new QNativeUIKitViewController(self));
        // Keep track of whether or not the view controller was created
        // by ourselves, in case we accidentally create one before
        // the app gets around to add one as a child.
        const_cast<QNativeUIKitWindowPrivate *>(d)->m_viewControllerSetExplicit = false;
    }
    return d->m_viewController;
}

qreal QNativeUIKitWindow::width() const
{
    return d_func()->view().frame.size.width;
}

qreal QNativeUIKitWindow::height() const
{
    return d_func()->view().frame.size.height;
}

bool QNativeUIKitWindow::isVisible() const
{
    return !d_func()->view().hidden;
}

void QNativeUIKitWindow::setVisible(bool newVisible)
{
    if (newVisible == isVisible())
        return;

    if (newVisible) {
        // Now that the window becomes visible, we should check if any of its
        // children needs to be resized to implicit size. Since children
        // are added after the call to setVisible when using QML, we need to
        // post the update request.
        qApp->postEvent(this, new QEvent(QEvent::LayoutRequest));
        // Also, UIKit expects there to always be a root view controller
        // in a UIWindow, so if hasn't been added yet, create one now.
        rootViewController();
        [uiWindowHandle() makeKeyAndVisible];
    } else {
        qWarning("not implemented");
    }

    emit visibleChanged(newVisible);
}

void QNativeUIKitWindow::showFullScreen()
{
    setVisible(true);
}

bool QNativeUIKitWindow::event(QEvent *e)
{
    Q_D(QNativeUIKitWindow);
    switch (e->type()) {
    case QEvent::LayoutRequest:
        d->updateLayout(true);
    default:
        return QNativeUIKitBase::event(e);
    }
    return true;
}

bool QNativeUIKitWindow::addNativeChild(QObject *child)
{
    if (QNativeUIKitView *c = dynamic_cast<QNativeUIKitView *>(child))
        c->setParent(this);
    else if (QNativeUIKitViewController *c = dynamic_cast<QNativeUIKitViewController *>(child))
        c->setParent(this);
    else
        return QNativeUIKitBase::addNativeChild(child);
    return true;
}

bool QNativeUIKitWindow::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "UIView")
        d_func()->addSubViewToContentView(reinterpret_cast<UIView *>(child));
    else if (type == "UIViewController")
        uiWindowHandle().rootViewController = reinterpret_cast<UIViewController *>(child);
    else
        return QNativeUIKitView::addNativeChild(type, child);
    return true;
}

QByteArrayList QNativeUIKitWindow::supportedNativeChildTypes()
{
    return QNativeUIKitView::supportedNativeChildTypes() << "UIViewController";
}

QByteArrayList QNativeUIKitWindow::supportedNativeParentTypes()
{
    return QByteArrayList();
}

void QNativeUIKitWindow::childEvent(QChildEvent *event)
{
    Q_D(QNativeUIKitWindow);
    // Note that event->child() might not be fully constructed at this point, if
    // called from its constructor chain. But the private part will.
    QObject *child = event->child();

    if (QNativeUIKitViewPrivate *dptr_child = dynamic_cast<QNativeUIKitViewPrivate *>(QObjectPrivate::get(child))) {
        if (event->added()) {
            // QNativeUIKitView added as children of the window will have their
            // UIViews added as children of the view controller view instead.
            d->addSubViewToContentView(dptr_child->view());
        } else if (event->removed()) {
            [dptr_child->view() removeFromSuperview];
        }
    } else if (QNativeUIKitViewControllerPrivate *dptr_child = dynamic_cast<QNativeUIKitViewControllerPrivate *>(QObjectPrivate::get(child))) {
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

#include "moc_qnativeuikitwindow.cpp"

QT_END_NAMESPACE
