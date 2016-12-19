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

#include <UIKit/UIKit.h>

#include <QtGui/qwindow.h>
#include <QtNativeUIKitControls/qnativeuikitwindow.h>
#include <QtNativeUIKitControls/private/qnativeuikitwindow_p.h>

QT_BEGIN_NAMESPACE

QNativeUIKitWindowPrivate::QNativeUIKitWindowPrivate(int version)
    : QNativeUIKitBasePrivate(version)
{
    // Note: using QWindow insteadof UIWindow directly means that it will be
    // registered in QtGuiApplication (e.g QtGuiApplication::topLevelWindows()).
    // Not sure if this is wanted or not, expecially if this needs to be
    // cross platform behaviour.
    m_window = new QWindow();
    setView(reinterpret_cast<UIView *>(m_window->winId()));
}

QNativeUIKitWindowPrivate::~QNativeUIKitWindowPrivate()
{
    delete m_window;
}

void QNativeUIKitWindowPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeUIKitWindow);
    QNativeUIKitBasePrivate::connectSignals(base);
    q->connect(q, SIGNAL(visibleChanged(bool)), base, SIGNAL(visibleChanged(bool)));
}

QNativeUIKitWindow::QNativeUIKitWindow(QObject *parent)
    : QNativeUIKitBase(*new QNativeUIKitWindowPrivate(), parent)
{
}

QNativeUIKitWindow::QNativeUIKitWindow(QNativeUIKitWindowPrivate &dd, QObject *parent)
    : QNativeUIKitBase(dd, parent)
{
}

QNativeUIKitWindow::~QNativeUIKitWindow()
{
}

bool QNativeUIKitWindow::isVisible() const
{
    return d_func()->m_window->isVisible();
}

void QNativeUIKitWindow::setVisible(bool newVisible)
{
    if (newVisible == isVisible())
        return;

    Q_D(QNativeUIKitWindow);
    d->m_window->setVisible(newVisible);

    emit visibleChanged(newVisible);
}

void QNativeUIKitWindow::showFullScreen()
{
    Q_D(QNativeUIKitWindow);
    bool wasVisible = d->m_window->isVisible();
    d->m_window->showFullScreen();
    if (!wasVisible)
        emit visibleChanged(true);
}

#include "moc_qnativeuikitwindow.cpp"

QT_END_NAMESPACE
