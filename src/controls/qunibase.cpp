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
 * @brief Set platform object as parent of this object.
 * \a parent is expected to be a subtype / control specific to the platform, but
 * unknown to QUni. What it means to use it as parent for this object is left
 * for the plugin to decide. Normal QObject parent-child ownership will apply, so
 * if \a parent is deleted, \c this will be deleted as well. You would call this
 * function whenever you need a QUni control to be a child of a QObject based
 * platform control.
 * @return Returns \c true if the plugin was able to use \a parent as parent.
 */
bool QUniBase::setNativeParent(QObject *parent)
{
    return d_func()->m_platformBase->setNativeParent(parent);
}

/**
 * @brief Set native OS object as parent of this object.
 * \a type is the type name of \a parent, and is expected to be a type / control
 * specific to the platform, but unknown to QUni. Especially, this function
 * accept types not deriving from QObject, like native OS controls. What it means
 * to use it as parent for this object is left for the plugin to decide.
 * The platform will not take ownership of \c this, so you should consider
 * assigning a normal QObject parent as well for automatic destruction.
 * The platform will not take ownership of \a parent, but depending on the
 * platform, it might keep a strong reference to it for as long as it needs it.
 * You would call this function whenever you need a QUni control to be a
 * child of a native OS control.
 * @return Returns \c true if the plugin was able to use \a parent as parent.
 */
bool QUniBase::setNativeParent(const QByteArray &type, void *parent)
{
    return d_func()->m_platformBase->setNativeParent(type, parent);
}

/**
 * @brief Add platform object as child of this object.
 * \a child is expected to be a subtype / control specific to the platform, but
 * unknown to QUni. What it means to add it as a child of this object is left
 * for the plugin to decide. Normal QObject parent-child ownership will apply, so
 * if \a this is deleted, \a child will be deleted as well. You would call
 * this function whenever you need a QObject based platform control to be a child
 * of a QUni control.
 * @return Returns \c true if the plugin was able to add \a child as a child.
 */
bool QUniBase::addNativeChild(QObject *child)
{
    return d_func()->m_platformBase->addNativeChild(child);
}

/**
 * @brief Add native OS object as child of this object.
 * \a type is the type name of \a child, and is expected to be a type / control
 * specific to the platform, but unknown to QUni. Especially, this function
 * accept types not deriving from QObject, like native OS controls.
 * What it means to add it as a child this object is left for the plugin
 * to decide. The platform will not take ownership of \c this, so you should consider
 * assigning a normal QObject parent as well for automatic destruction.
 * The platform will not take ownership of \a child, but depending on the
 * platform, it might keep a strong reference to it for as long as it needs it.
 * You would call this function whenever you need a native OS
 * control to be a child of a QUni control.
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
