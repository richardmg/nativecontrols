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
#include <QtNativeUIKitControls/private/qnativeuikitwindow_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitWindowPrivate::QNativeUIKitWindowPrivate(int version)
    : QNativeUIKitBasePrivate(version)
{
    m_window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    UIViewController *viewController = [[UIViewController new] autorelease];
    UIView *view = [[[UIView alloc] initWithFrame:m_window.bounds] autorelease];

    m_window.rootViewController = viewController;
    viewController.view = view;

    view.backgroundColor = [UIColor whiteColor];

    setView(view);
}

QNativeUIKitWindowPrivate::~QNativeUIKitWindowPrivate()
{
    [m_window release];
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
            if (QNativeUIKitBasePrivate *basePrivate = dynamic_cast<QNativeUIKitBasePrivate *>(QObjectPrivate::get(child)))
                basePrivate->updateLayout(recursive);
        }
    }
}

QNativeUIKitWindow::QNativeUIKitWindow()
    : QNativeUIKitBase(*new QNativeUIKitWindowPrivate(), nullptr)
{
}

QNativeUIKitWindow::QNativeUIKitWindow(QNativeUIKitWindowPrivate &dd)
    : QNativeUIKitBase(dd, nullptr)
{
}

QNativeUIKitWindow::~QNativeUIKitWindow()
{
}

UIWindow *QNativeUIKitWindow::uiWindowHandle() const
{
    return d_func()->m_window;
}

qreal QNativeUIKitWindow::width() const
{
    return uiWindowHandle().frame.size.width;
}

qreal QNativeUIKitWindow::height() const
{
    return uiWindowHandle().frame.size.height;
}

bool QNativeUIKitWindow::isVisible() const
{
    return !d_func()->m_window.hidden;
}

void QNativeUIKitWindow::setVisible(bool newVisible)
{
    if (newVisible == isVisible())
        return;

    Q_D(QNativeUIKitWindow);

    if (newVisible) {
        // Now that the window becomes visible, we should check if any of its
        // children needs to be resized to implicit size. Since children
        // are added after the call to setVisible when using QML, we need to
        // post the update request.
        qApp->postEvent(this, new QEvent(QEvent::LayoutRequest));
        [d->m_window makeKeyAndVisible];
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

#include "moc_qnativeuikitwindow.cpp"

QT_END_NAMESPACE
