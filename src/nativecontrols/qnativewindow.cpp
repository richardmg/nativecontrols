/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native Controls module of the Qt Toolkit.
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

#include <QtNativeControls/qnativewindow.h>
#include <QtNativeControls/private/qnativewindow_p.h>
#include <QtNativeControls/qnativeplatformwindow.h>

#define PLATFORM_WINDOW dynamic_cast<QNativePlatformWindow *>(d_func()->m_platformBase)

QT_BEGIN_NAMESPACE

QNativeWindowPrivate::QNativeWindowPrivate(int version)
    : QNativeBasePrivate(version)
{
}

QNativeWindowPrivate::~QNativeWindowPrivate()
{
}

QNativeWindow::QNativeWindow()
    : QNativeBase(nullptr)
{
    d_func()->connectToPlatform();
}

QNativeWindow::QNativeWindow(QNativeWindowPrivate &dd, QNativeBase *parent)
    : QNativeBase(dd, parent)
{
}

QNativeWindow::~QNativeWindow()
{
}

qreal QNativeWindow::width() const
{
    return PLATFORM_WINDOW->width();
}

qreal QNativeWindow::height() const
{
    return PLATFORM_WINDOW->height();
}

bool QNativeWindow::isVisible() const
{
    return PLATFORM_WINDOW->isVisible();
}

void QNativeWindow::setVisible(bool v)
{
    PLATFORM_WINDOW->setVisible(v);
}

void QNativeWindow::showFullScreen()
{
    PLATFORM_WINDOW->showFullScreen();
}

#include "moc_qnativewindow.cpp"

QT_END_NAMESPACE

