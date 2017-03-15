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

#include <QtUniControls/qunisearchfield.h>
#include <QtUniControls/private/qunisearchfield_p.h>
#include <QtUniControls/quniplatformsearchfield.h>
#include <QtUniControls/private/quniplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QUniSearchFieldPrivate::QUniSearchFieldPrivate(int version)
    : QUniControlPrivate(version)
    , m_platformSearchField(nullptr)
{
}

QUniSearchFieldPrivate::~QUniSearchFieldPrivate()
{
}

void QUniSearchFieldPrivate::createPlatformSearchField()
{
    Q_ASSERT(!m_platformSearchField);
    m_platformSearchField = QUniPlatformManager::platformPlugin()->createSearchField(q_func());
    Q_ASSERT(m_platformSearchField);
    setPlatformSearchField(m_platformSearchField);
}

void QUniSearchFieldPrivate::setPlatformSearchField(QUniPlatformSearchField *platformSearchField)
{
    m_platformSearchField = platformSearchField;
    setPlatformControl(platformSearchField);
}

QUniSearchField::QUniSearchField(QUniBase *parent)
    : QUniControl(*new QUniSearchFieldPrivate(), parent)
{
    d_func()->createPlatformSearchField();
}

QUniSearchField::QUniSearchField(const QString &text, QUniBase *parent)
    : QUniControl(*new QUniSearchFieldPrivate(), parent)
{
    d_func()->createPlatformSearchField();
    setText(text);
}

QUniSearchField::QUniSearchField(QUniSearchFieldPrivate &dd, QUniBase *parent)
    : QUniControl(dd, parent)
{
}

QUniSearchField::~QUniSearchField()
{
}

QString QUniSearchField::text()
{
    return d_func()->m_platformSearchField->text();
}

void QUniSearchField::setText(const QString &newText)
{
    d_func()->m_platformSearchField->setText(newText);
}

QString QUniSearchField::placeholderText()
{
    return d_func()->m_platformSearchField->placeholderText();
}

void QUniSearchField::setPlaceholderText(const QString &placeholderText)
{
    d_func()->m_platformSearchField->setPlaceholderText(placeholderText);
}

#include "moc_qunisearchfield.cpp"

QT_END_NAMESPACE

