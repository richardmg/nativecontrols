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

#include <QtUniControls/qunitabspage.h>
#include <QtUniControls/private/qunitabspage_p.h>
#include <QtUniControls/quniplatformtabspage.h>
#include <QtUniControls/private/quniplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QUniTabsPagePrivate::QUniTabsPagePrivate(int version)
    : QUniPagePrivate(version)
    , m_platformTabsPage(nullptr)
{
}

QUniTabsPagePrivate::~QUniTabsPagePrivate()
{
}

void QUniTabsPagePrivate::createPlatformTabsPage()
{
    Q_ASSERT(!m_platformTabsPage);
    m_platformTabsPage = QUniPlatformManager::platformPlugin()->createTabsPage(q_func());
    Q_ASSERT(m_platformTabsPage);
    setPlatformTabsPage(m_platformTabsPage);
}

void QUniTabsPagePrivate::setPlatformTabsPage(QUniPlatformTabsPage *platformTabsPage)
{
    m_platformTabsPage = platformTabsPage;
    setPlatformPage(platformTabsPage);
}

QUniTabsPage::QUniTabsPage(QUniBase *parent)
    : QUniPage(*new QUniTabsPagePrivate(), parent)
{
    d_func()->createPlatformTabsPage();
}

QUniTabsPage::QUniTabsPage(QUniTabsPagePrivate &dd, QUniBase *parent)
    : QUniPage(dd, parent)
{
}

QUniTabsPage::~QUniTabsPage()
{
}

#include "moc_qunitabspage.cpp"

QT_END_NAMESPACE