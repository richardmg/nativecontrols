/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
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

#include <QtNativeControls/quniwindow.h>
#include <QtNativeControls/private/quniwindow_p.h>
#include <QtNativeControls/quniplatformwindow.h>
#include <QtNativeControls/private/quniplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QUniWindowPrivate::QUniWindowPrivate(int version)
    : QUniBasePrivate(version)
    , m_platformWindow(nullptr)
{
}

QUniWindowPrivate::~QUniWindowPrivate()
{
}

void QUniWindowPrivate::createPlatformWindow()
{
    Q_ASSERT(!m_platformWindow);
    m_platformWindow = QUniPlatformManager::platformPlugin()->createWindow(q_func());
    Q_ASSERT(m_platformWindow);
    setPlatformWindow(m_platformWindow);
}

void QUniWindowPrivate::setPlatformWindow(QUniPlatformWindow *platformWindow)
{
    m_platformWindow = platformWindow;
    setPlatformBase(platformWindow);
}

QUniWindow::QUniWindow()
    : QUniBase(*new QUniWindowPrivate(), nullptr)
{
    d_func()->createPlatformWindow();
}

QUniWindow::QUniWindow(QUniWindowPrivate &dd, QUniBase *parent)
    : QUniBase(dd, parent)
{
}

QUniWindow::~QUniWindow()
{
}

qreal QUniWindow::width() const
{
    return d_func()->m_platformWindow->width();
}

qreal QUniWindow::height() const
{
    return d_func()->m_platformWindow->height();
}

bool QUniWindow::isVisible() const
{
    return d_func()->m_platformWindow->isVisible();
}

void QUniWindow::setVisible(bool v)
{
    d_func()->m_platformWindow->setVisible(v);
}

void QUniWindow::showFullScreen()
{
    d_func()->m_platformWindow->showFullScreen();
}

#include "moc_quniwindow.cpp"

QT_END_NAMESPACE

