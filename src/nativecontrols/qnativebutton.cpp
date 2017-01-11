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

#include <QtNativeControls/qnativebutton.h>
#include <QtNativeControls/private/qnativebutton_p.h>
#include <QtNativeControls/qnativeplatformbutton.h>

QT_BEGIN_NAMESPACE

#define PLATFORM_BUTTON dynamic_cast<QNativePlatformButton *>(d_func()->m_platformBase)

QNativeButtonPrivate::QNativeButtonPrivate(int version)
    : QNativeControlPrivate(version)
{
}

QNativeButtonPrivate::~QNativeButtonPrivate()
{
}

QNativeButton::QNativeButton(QNativeBase *parent)
    : QNativeControl(*new QNativeButtonPrivate(), parent)
{
    d_func()->connectToPlatform();
}

QNativeButton::QNativeButton(const QString &text, QNativeBase *parent)
    : QNativeControl(*new QNativeButtonPrivate(), parent)
{
    d_func()->connectToPlatform();
    setText(text);
}

QNativeButton::QNativeButton(QNativeButtonPrivate &dd, QNativeBase *parent)
    : QNativeControl(dd, parent)
{
}

QNativeButton::~QNativeButton()
{
}

QString QNativeButton::text()
{
    return PLATFORM_BUTTON->text();
}

void QNativeButton::setText(const QString &newText)
{
    PLATFORM_BUTTON->setText(newText);
}

#include "moc_qnativebutton.cpp"

QT_END_NAMESPACE

