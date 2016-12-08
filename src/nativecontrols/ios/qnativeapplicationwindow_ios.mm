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

#include "qnativeapplicationwindow.h"
#include "qnativeapplicationwindow_ios_p.h"

QT_BEGIN_NAMESPACE

QNativeApplicationWindowPrivate::QNativeApplicationWindowPrivate(int version)
    : QNativeControlPrivate(version)
{}

QNativeApplicationWindow::QNativeApplicationWindow(QObject *parent)
    : QNativeControl(*new QNativeApplicationWindowPrivate(), parent)
{
    // Note: using QWindow insteadof UIWindow directly means that it will be
    // registered in QtGuiApplication (e.g QtGuiApplication::topLevelWindows()).
    // Not sure if this is wanted or not, expecially if this needs to be
    // cross platform behaviour.
    QWindow *window = new QWindow();
    window->setWindowState(Qt::WindowFullScreen);

    d_func()->m_window = window;
    d_func()->setView(reinterpret_cast<UIView *>(window->winId()));
}

QNativeApplicationWindow::QNativeApplicationWindow(QNativeApplicationWindowPrivate &dd, QObject *parent)
    : QNativeControl(dd, parent)
{
}

QNativeApplicationWindow::~QNativeApplicationWindow()
{
    d_func()->setView(nullptr);
    delete d_func()->m_window;
}

bool QNativeApplicationWindow::isVisible() const
{
    return QNativeControl::isVisible();
}

void QNativeApplicationWindow::setVisible(bool visible)
{
    QNativeControl::setVisible(visible);
}

#include "moc_qnativeapplicationwindow.cpp"

QT_END_NAMESPACE
