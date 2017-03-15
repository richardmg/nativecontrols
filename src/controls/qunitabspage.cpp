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

#include <QtNativeControls/qnativetabspage.h>
#include <QtNativeControls/private/qnativetabspage_p.h>
#include <QtNativeControls/qnativeplatformtabspage.h>
#include <QtNativeControls/private/qnativeplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QNativeTabsPagePrivate::QNativeTabsPagePrivate(int version)
    : QNativePagePrivate(version)
    , m_platformTabsPage(nullptr)
{
}

QNativeTabsPagePrivate::~QNativeTabsPagePrivate()
{
}

void QNativeTabsPagePrivate::createPlatformTabsPage()
{
    Q_ASSERT(!m_platformTabsPage);
    m_platformTabsPage = QNativePlatformManager::platformPlugin()->createTabsPage(q_func());
    Q_ASSERT(m_platformTabsPage);
    setPlatformTabsPage(m_platformTabsPage);
}

void QNativeTabsPagePrivate::setPlatformTabsPage(QNativePlatformTabsPage *platformTabsPage)
{
    m_platformTabsPage = platformTabsPage;
    setPlatformPage(platformTabsPage);
}

QNativeTabsPage::QNativeTabsPage(QNativeBase *parent)
    : QNativePage(*new QNativeTabsPagePrivate(), parent)
{
    d_func()->createPlatformTabsPage();
}

QNativeTabsPage::QNativeTabsPage(QNativeTabsPagePrivate &dd, QNativeBase *parent)
    : QNativePage(dd, parent)
{
}

QNativeTabsPage::~QNativeTabsPage()
{
}

#include "moc_qnativetabspage.cpp"

QT_END_NAMESPACE
