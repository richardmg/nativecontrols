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

#include <QtNativeControls/qunicontrol.h>
#include <QtNativeControls/private/qunicontrol_p.h>
#include <QtNativeControls/quniplatformcontrol.h>
#include <QtNativeControls/quniview.h>
#include <QtNativeControls/private/quniplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QUniControlPrivate::QUniControlPrivate(int version)
    : QUniViewPrivate(version)
    , m_platformControl(nullptr)
{
}

QUniControlPrivate::~QUniControlPrivate()
{
}

void QUniControlPrivate::createPlatformControl()
{
    Q_ASSERT(!m_platformControl);
    m_platformControl = QUniPlatformManager::platformPlugin()->createControl(q_func());
    Q_ASSERT(m_platformControl);
    setPlatformControl(m_platformControl);
}

void QUniControlPrivate::setPlatformControl(QUniPlatformControl *platformControl)
{
    m_platformControl = platformControl;
    setPlatformView(platformControl);
}

QUniControl::QUniControl(QUniBase *parent)
    : QUniView(parent)
{
    d_func()->createPlatformControl();
}

QUniControl::QUniControl(QUniControlPrivate &dd, QUniBase *parent)
    : QUniView(dd, parent)
{
}

QUniControl::~QUniControl()
{
}

#include "moc_qunicontrol.cpp"

QT_END_NAMESPACE
