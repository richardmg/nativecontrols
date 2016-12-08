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

#include "qnativepushbutton.h"
#include "qnativepushbutton_ios_p.h"

QT_BEGIN_NAMESPACE

QNativePushButtonPrivate::QNativePushButtonPrivate(int version)
    : QNativeControlPrivate(version)
{}

QNativePushButton::QNativePushButton(QObject *parent)
    : QNativeControl(*new QNativePushButtonPrivate(), parent)
{
    UIButton *uiButton = [[UIButton alloc] initWithFrame:CGRectMake(20, 20, 100, 50)];
    [uiButton setTitle:@"Click me" forState:UIControlStateNormal];
    d_func()->setView(uiButton);
}

QNativePushButton::QNativePushButton(QNativePushButtonPrivate &dd, QObject *parent)
    : QNativeControl(dd, parent)
{
}

QNativePushButton::~QNativePushButton()
{
    d_func()->setView(nullptr);
}

bool QNativePushButton::isVisible() const
{
    return QNativeControl::isVisible();
}

void QNativePushButton::setVisible(bool visible)
{
    QNativeControl::setVisible(visible);
}

#include "moc_qnativepushbutton.cpp"

QT_END_NAMESPACE
