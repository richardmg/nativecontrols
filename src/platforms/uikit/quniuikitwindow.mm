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
#include <QtUniUIKitControls/quniuikitwindow.h>
#include <QtUniUIKitControls/quniuikitviewcontroller.h>
#include <QtUniUIKitControls/private/quniuikitwindow_p.h>
#include <QtUniUIKitControls/private/quniuikitviewcontroller_p.h>
#include <QtUniUIKitControls/private/quniuikitview_p.h>

QT_BEGIN_NAMESPACE

QUniUIKitWindowPrivate::QUniUIKitWindowPrivate(int version)
    : QUniUIKitViewPrivate(version)
    , m_viewController(nullptr)
    , m_viewControllerSetExplicit(false)
{
}

QUniUIKitWindowPrivate::~QUniUIKitWindowPrivate()
{
}

void QUniUIKitWindowPrivate::connectSignals(QUniBase *base)
{
    Q_Q(QUniUIKitWindow);
    QUniUIKitBasePrivate::connectSignals(base);
    const auto b = static_cast<QUniWindow *>(base);
    q->connect(q, &QUniUIKitWindow::visibleChanged, b, &QUniWindow::visibleChanged);
}

void QUniUIKitWindowPrivate::updateLayout(bool recursive)
{
    if (testAttribute(LayedOut))
        return;
    setAttribute(LayedOut);

    if (recursive) {
        for (QObject *child : q_func()->children()) {
            if (QUniUIKitViewPrivate *basePrivate = dynamic_cast<QUniUIKitViewPrivate *>(QObjectPrivate::get(child)))
                basePrivate->updateLayout(recursive);
        }
    }
}

void QUniUIKitWindowPrivate::addSubViewToContentView(UIView *uiView)
{
    Q_Q(QUniUIKitWindow);
    QUniUIKitView *contentView = q->rootViewController()->view();
    QUniUIKitViewPrivate *dptr_contentView = dynamic_cast<QUniUIKitViewPrivate *>(QObjectPrivate::get(contentView));
    dptr_contentView->addSubView(uiView);
}

UIView *QUniUIKitWindowPrivate::createView()
{
    return [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
}

QUniUIKitWindow::QUniUIKitWindow()
    : QUniUIKitView(*new QUniUIKitWindowPrivate(), nullptr)
{
}

QUniUIKitWindow::QUniUIKitWindow(QUniUIKitWindowPrivate &dd)
    : QUniUIKitView(dd, nullptr)
{
}

QUniUIKitWindow::~QUniUIKitWindow()
{
}

UIWindow *QUniUIKitWindow::uiWindowHandle()
{
    return static_cast<UIWindow *>(d_func()->view());
}

void QUniUIKitWindow::setRootViewController(QUniUIKitViewController *controller)
{
    Q_D(QUniUIKitWindow);
    if (d->m_viewController == controller)
        return;

    d->m_viewControllerSetExplicit = true;
    d->m_viewController = controller;
    uiWindowHandle().rootViewController = d->m_viewController->uiViewControllerHandle();
    emit rootViewControllerChanged(controller);
}

QUniUIKitViewController *QUniUIKitWindow::rootViewController() const
{
    Q_D(const QUniUIKitWindow);
    if (!d->m_viewController) {
        QUniUIKitWindow *self = const_cast<QUniUIKitWindow *>(this);
        self->setRootViewController(new QUniUIKitViewController(self));
        // Keep track of whether or not the view controller was created
        // by ourselves, in case we accidentally create one before
        // the app gets around to add one as a child.
        const_cast<QUniUIKitWindowPrivate *>(d)->m_viewControllerSetExplicit = false;
    }
    return d->m_viewController;
}

qreal QUniUIKitWindow::width() const
{
    return geometry().width();
}

qreal QUniUIKitWindow::height() const
{
    return geometry().height();
}

bool QUniUIKitWindow::isVisible() const
{
    return !d_func()->view().hidden;
}

void QUniUIKitWindow::setVisible(bool newVisible)
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

void QUniUIKitWindow::showFullScreen()
{
    setVisible(true);
}

QRectF QUniUIKitWindow::geometry() const
{
    return QRectF::fromCGRect(d_func()->view().frame);
}

bool QUniUIKitWindow::event(QEvent *e)
{
    Q_D(QUniUIKitWindow);
    switch (e->type()) {
    case QEvent::LayoutRequest:
        d->updateLayout(true);
    default:
        return QUniUIKitBase::event(e);
    }
    return true;
}

bool QUniUIKitWindow::addNativeChild(QObject *child)
{
    if (QUniUIKitView *c = qobject_cast<QUniUIKitView *>(child))
        c->setParent(this);
    else if (QUniUIKitViewController *c = qobject_cast<QUniUIKitViewController *>(child))
        c->setParent(this);
    else
        return QUniUIKitBase::addNativeChild(child);
    return true;
}

bool QUniUIKitWindow::addNativeChild(const QByteArray &type, void *child)
{
    if (type == "UIView")
        d_func()->addSubViewToContentView(static_cast<UIView *>(child));
    else if (type == "UIViewController")
        uiWindowHandle().rootViewController = static_cast<UIViewController *>(child);
    else
        return QUniUIKitView::addNativeChild(type, child);
    return true;
}

QByteArrayList QUniUIKitWindow::supportedNativeChildTypes()
{
    return QUniUIKitView::supportedNativeChildTypes() << "UIViewController";
}

QByteArrayList QUniUIKitWindow::supportedNativeParentTypes()
{
    return QByteArrayList();
}

#include "moc_quniuikitwindow.cpp"

QT_END_NAMESPACE
