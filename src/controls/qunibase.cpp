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

#include <QtUniControls/qunibase.h>
#include <QtUniControls/private/qunibase_p.h>

#include <QtUniControls/quniplatformbase.h>
#include <QtUniControls/private/quniplatformmanager_p.h>

QT_BEGIN_NAMESPACE

QUniBasePrivate::QUniBasePrivate(int version)
    : QUniQmlBasePrivate(version)
    , m_platformBase(nullptr)
{
}

QUniBasePrivate::~QUniBasePrivate()
{
    delete m_platformBase;
}

void QUniBasePrivate::setPlatformBase(QUniPlatformBase *platformBase)
{
    // QUniBasePrivate will take ownership over platformBase.
    m_platformBase = platformBase;
    syncPlatformParent();
}

void QUniBasePrivate::syncPlatformParent()
{
    QUniBase *p = qobject_cast<QUniBase *>(q_func()->parent());
    m_platformBase->setPlatformParent(p ? static_cast<QUniBasePrivate *>(QObjectPrivate::get(p))->m_platformBase : nullptr);
}

QUniBase::QUniBase(QUniBase *parent)
    : QUniQmlBase(parent)
{
}

QUniBase::QUniBase(QUniBasePrivate &dd, QUniBase *parent)
    : QUniQmlBase(dd, parent)
{
}

QUniBase::~QUniBase()
{
}

void QUniBase::setParent(QUniBase *parentBase)
{
    if (parentBase == parent())
        return;

    QObject::setParent(parentBase);
    d_func()->syncPlatformParent();
    emit parentChanged(parentBase);
}

QUniBase *QUniBase::parentBase()
{
    return qobject_cast<QUniBase *>(parent());
}

/**
 * @brief Set \a parent as \l{QObject::parent()}{parent} of this object.
 * \a parent is expected to be a subtype / control specific to the
 * platform, but unknown to QUni.
 * If the platform plugin recognizes \a parent as a platform
 * control, it will set it as a \l{QObject::parent()}{parent} of the
 * platform control that it used as backend for this object.
 * @return Returns \c true if the plugin was able to use \a parent as parent.
 */
bool QUniBase::setNativeParent(QObject *parent)
{
    return d_func()->m_platformBase->setNativeParent(parent);
}

/**
 * @brief Set \a parent as parent of this object.
 * \a parent is expected to be a subtype / control specific to the
 * platform, but unknown to QUni.
 * Especially, \a parent is in most cases expected to be a native OS control.
 * Calling this function will \underline{not} change QObject::parent().
 * It will only let the platform plugin crate a parent-child relationship between
 * the native controls that are used as backends by \c this and \a parent.
 * @return Returns \c true if the plugin was able to use \a parent as parent.
 */
bool QUniBase::setNativeParent(const QByteArray &type, void *parent)
{
    return d_func()->m_platformBase->setNativeParent(type, parent);
}

/**
 * @brief Set \a this as a \l{QObject::parent()}{parent} of \a child.
 * \a child is expected to be a subtype / control specific to the
 * platform, but unknown to QUni.
 * If the platform plugin recognizes \a child as a platform
 * control, it will add it as a child of the
 * platform control that is used as backend for this object.
 * @return Returns \c true if the plugin was able to add \a child as a child.
 */
bool QUniBase::addNativeChild(QObject *child)
{
    return d_func()->m_platformBase->addNativeChild(child);
}

/**
 * @brief Set \a this as a structural parent of \a child.
 * \a child is expected to be a subtype / control specific to the
 * platform, but unknown to QUni.
 * Especially, \a child is in most cases expected to be a native OS control.
 * Calling this function will \underline{not} change the childs QObject::parent().
 * It will only let the platform plugin crate a parent-child relationship between
 * the native controls that are used as backends by \c this and \a child.
 * @return Returns \c true if the plugin was able to add \a child as a child.
 */
bool QUniBase::addNativeChild(const QByteArray &type, void *child)
{
    return d_func()->m_platformBase->addNativeChild(type, child);
}

/**
 * Query the type names supported by addNativeChild().
 */
QByteArrayList QUniBase::supportedNativeChildTypes()
{
    return d_func()->m_platformBase->supportedNativeChildTypes();
}

/**
 * Query the type names supported by setNativeParent().
 */
QByteArrayList QUniBase::supportedNativeParentTypes()
{
    return d_func()->m_platformBase->supportedNativeParentTypes();
}

void QUniBase::childEvent(QChildEvent *event)
{
    if (QUniBase *child = qobject_cast<QUniBase *>(event->child()))
        child->d_func()->syncPlatformParent();
}

#include "moc_qunibase.cpp"

QT_END_NAMESPACE
