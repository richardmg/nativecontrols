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

#include <QtNativeControls/qunitextfield.h>
#include <QtNativeControls/private/qunitextfield_p.h>
#include <QtNativeControls/quniplatformtextfield.h>
#include <QtNativeControls/private/quniplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QUniTextFieldPrivate::QUniTextFieldPrivate(int version)
    : QUniControlPrivate(version)
    , m_platformTextField(nullptr)
{
}

QUniTextFieldPrivate::~QUniTextFieldPrivate()
{
}

void QUniTextFieldPrivate::createPlatformTextField()
{
    Q_ASSERT(!m_platformTextField);
    m_platformTextField = QUniPlatformManager::platformPlugin()->createTextField(q_func());
    Q_ASSERT(m_platformTextField);
    setPlatformTextField(m_platformTextField);
}

void QUniTextFieldPrivate::setPlatformTextField(QUniPlatformTextField *platformTextField)
{
    m_platformTextField = platformTextField;
    setPlatformControl(platformTextField);
}

QUniTextField::QUniTextField(QUniBase *parent)
    : QUniControl(*new QUniTextFieldPrivate(), parent)
{
    d_func()->createPlatformTextField();
}

QUniTextField::QUniTextField(const QString &text, QUniBase *parent)
    : QUniControl(*new QUniTextFieldPrivate(), parent)
{
    d_func()->createPlatformTextField();
    setText(text);
}

QUniTextField::QUniTextField(QUniTextFieldPrivate &dd, QUniBase *parent)
    : QUniControl(dd, parent)
{
}

QUniTextField::~QUniTextField()
{
}

QString QUniTextField::text()
{
    return d_func()->m_platformTextField->text();
}

void QUniTextField::setText(const QString &newText)
{
    d_func()->m_platformTextField->setText(newText);
}

QString QUniTextField::placeholderText()
{
    return d_func()->m_platformTextField->placeholderText();
}

void QUniTextField::setPlaceholderText(const QString &placeholderText)
{
    d_func()->m_platformTextField->setPlaceholderText(placeholderText);
}

#include "moc_qunitextfield.cpp"

QT_END_NAMESPACE

