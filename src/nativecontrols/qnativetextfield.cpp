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


#include <QtNativeControls/qnativetextfield.h>
#include <QtNativeControls/private/qnativetextfield_p.h>
#include <QtNativeControls/qnativeplatformtextfield.h>

QT_BEGIN_NAMESPACE

#define PLATFORM_TEXT_FIELD dynamic_cast<QNativePlatformTextField *>(d_func()->m_platformBase)

QNativeTextFieldPrivate::QNativeTextFieldPrivate(int version)
    : QNativeControlPrivate(version)
{
}

QNativeTextFieldPrivate::~QNativeTextFieldPrivate()
{
}

QNativeTextField::QNativeTextField(QNativeBase *parent)
    : QNativeControl(*new QNativeTextFieldPrivate(), parent)
{
    d_func()->connectToPlatform();
}

QNativeTextField::QNativeTextField(const QString &text, QNativeBase *parent)
    : QNativeControl(*new QNativeTextFieldPrivate(), parent)
{
    d_func()->connectToPlatform();
    setText(text);
}

QNativeTextField::QNativeTextField(QNativeTextFieldPrivate &dd, QNativeBase *parent)
    : QNativeControl(dd, parent)
{
}

QNativeTextField::~QNativeTextField()
{
}

QString QNativeTextField::text()
{
    return PLATFORM_TEXT_FIELD->text();
}

void QNativeTextField::setText(const QString &newText)
{
    PLATFORM_TEXT_FIELD->setText(newText);
}

QString QNativeTextField::placeholderText()
{
    return PLATFORM_TEXT_FIELD->placeholderText();
}

void QNativeTextField::setPlaceholderText(const QString &placeholderText)
{
    PLATFORM_TEXT_FIELD->setPlaceholderText(placeholderText);
}

#include "moc_qnativetextfield.cpp"

QT_END_NAMESPACE

