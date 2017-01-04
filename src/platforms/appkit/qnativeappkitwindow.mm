/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
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
#include <QtNativeAppKitControls/private/qnativeappkitwindow_p.h>

QT_BEGIN_NAMESPACE

QNativeAppKitWindowPrivate::QNativeAppKitWindowPrivate(int version)
    : QNativeAppKitBasePrivate(version)
{
    NSRect screenFrame = NSScreen.mainScreen.visibleFrame;
    NSRect windowFrame = NSMakeRect(0, 0,
                                    (NSInteger)(NSWidth(screenFrame) / 3),
                                    (NSInteger)(NSHeight(screenFrame) / 3));

    NSView *view = [[[NSView alloc] initWithFrame:windowFrame] autorelease];

    NSViewController *viewController = [[NSViewController new] autorelease];
    viewController.view = view;

    m_window = [NSWindow windowWithContentViewController:viewController];
    m_window.contentViewController = viewController;

    setView(view);
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
    q->connect(q, &QNativeAppKitWindow::visibleChanged, b, &QNativeWindow::visibleChanged);
}

void QNativeAppKitWindowPrivate::updateLayout(bool recursive)
{
    if (testAttribute(LayedOut))
        return;
    setAttribute(LayedOut);

    if (recursive) {
        for (QObject *child : q_func()->children())
            static_cast<QNativeAppKitBasePrivate *>(QObjectPrivate::get(child))->updateLayout(recursive);
    }
}

QNativeAppKitWindow::QNativeAppKitWindow(QObject *parent)
    : QNativeAppKitBase(*new QNativeAppKitWindowPrivate(), parent)
{
}

QNativeAppKitWindow::QNativeAppKitWindow(QNativeAppKitWindowPrivate &dd, QObject *parent)
    : QNativeAppKitBase(dd, parent)
{
}

QNativeAppKitWindow::~QNativeAppKitWindow()
{
}

NSWindow *QNativeAppKitWindow::nsWindowHandle()
{
    return d_func()->m_window;
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
        d_func()->updateLayout(true);
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

#include "moc_qnativeappkitwindow.cpp"

QT_END_NAMESPACE
