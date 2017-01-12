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


#include <QtNativeControls/qnativesearchfield.h>
#include <QtNativeControls/private/qnativesearchfield_p.h>
#include <QtNativeControls/qnativeplatformsearchfield.h>

QT_BEGIN_NAMESPACE

#define PLATFORM_SEARCH_FIELD dynamic_cast<QNativePlatformSearchField *>(d_func()->m_platformBase)

QNativeSearchFieldPrivate::QNativeSearchFieldPrivate(int version)
    : QNativeControlPrivate(version)
{
}

QNativeSearchFieldPrivate::~QNativeSearchFieldPrivate()
{
}

QNativeSearchField::QNativeSearchField(QNativeBase *parent)
    : QNativeControl(*new QNativeSearchFieldPrivate(), parent)
{
    d_func()->connectToPlatform();
}

QNativeSearchField::QNativeSearchField(const QString &text, QNativeBase *parent)
    : QNativeControl(*new QNativeSearchFieldPrivate(), parent)
{
    d_func()->connectToPlatform();
    setText(text);
}

QNativeSearchField::QNativeSearchField(QNativeSearchFieldPrivate &dd, QNativeBase *parent)
    : QNativeControl(dd, parent)
{
}

QNativeSearchField::~QNativeSearchField()
{
}

QString QNativeSearchField::text()
{
    return PLATFORM_SEARCH_FIELD->text();
}

void QNativeSearchField::setText(const QString &newText)
{
    PLATFORM_SEARCH_FIELD->setText(newText);
}

QString QNativeSearchField::placeholderText()
{
    return PLATFORM_SEARCH_FIELD->placeholderText();
}

void QNativeSearchField::setPlaceholderText(const QString &placeholderText)
{
    PLATFORM_SEARCH_FIELD->setPlaceholderText(placeholderText);
}

#include "moc_qnativesearchfield.cpp"

QT_END_NAMESPACE

