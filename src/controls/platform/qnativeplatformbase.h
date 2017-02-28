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

#ifndef QNATIVEPLATFORMBASE_H
#define QNATIVEPLATFORMBASE_H

#include <QtCore>
#include <QtNativeControls/qnativecontrolsglobal.h>

QT_BEGIN_NAMESPACE

class Q_NATIVECONTROLS_EXPORT QNativePlatformBase
{
public:
    virtual ~QNativePlatformBase() {}

    virtual void setPlatformParent(QNativePlatformBase *) = 0;

    /**
     * @brief Override to support mixing platform controls with QNative controls.
     * \a parent is expected to be a type / control specific to the platform, but
     * unknown to QNative. What is means to use it as parent for this object is left
     * for the plugin to decide. You would call this function whenever you need a
     * QNative control to be a child of a QObject based platform control.
     * @return Returns \c true if the plugin was able to use \a parent as parent.
     */
    virtual bool setNativeParent(QObject *parent)
    {
        // Override to support mixing platform controls with QNative controls.
        Q_UNUSED(parent);
        return false;
    }

    /**
     * @brief Override to support mixing platform controls with QNative controls.
     * \a type is the type name of \a parent, and is expected to be a type / control
     * specific to the platform, but unknown to QNative. Especially, this function
     * accept types not deriving from QObject, like native OS controls.
     * What is means to use it as parent for this object is left for the plugin
     * to decide. You would call this function whenever you need a QNative control to be a
     * child of a native OS control.
     * @return Returns \c true if the plugin was able to use \a parent as parent.
     */
    virtual bool setNativeParent(const QByteArray &type, void *parent)
    {
        // Override to support mixing platform controls with QNative controls.
        Q_UNUSED(type);
        Q_UNUSED(parent);
        return false;
    }

    /**
     * @brief Override to support mixing platform controls with QNative controls.
     * \a child is expected to be a type / control specific to the platform, but
     * unknown to QNative. What is means to add it as a child of this object is left
     * for the plugin to decide. You would call this function whenever you need a
     * QObject based platform control to be a child of a QNative control.
     * @return Returns \c true if the plugin was able to add \a child as a child.
     */
    virtual bool addNativeChild(QObject *child)
    {
        // Override to support mixing platform controls with QNative controls.
        Q_UNUSED(child);
        return false;
    }

    /**
     * @brief Override to support mixing platform controls with QNative controls.
     * \a type is the type name of \a child, and is expected to be a type / control
     * specific to the platform, but unknown to QNative. Especially, this function
     * accept types not deriving from QObject, like native OS controls.
     * What is means to add it as a child this object is left for the plugin
     * to decide. You would call this function whenever you need a native OS
     * control to be a child of a QNative control.
     * @return Returns \c true if the plugin was able to add \a child as a child.
     */
    virtual bool addNativeChild(const QByteArray &type, void *child)
    {
        // Override to support mixing platform controls with QNative controls.
        Q_UNUSED(type);
        Q_UNUSED(child);
        return false;
    }

    /**
     * Query the type names supported by addNativeChild().
     */
    virtual QByteArrayList supportedNativeChildTypes()
    {
        // Override to support mixing platform controls with QNative controls.
        return QByteArrayList();
    }

    /**
     * Query the type names supported by setNativeParent().
     */
    virtual QByteArrayList supportedNativeParentTypes()
    {
        // Override to support mixing platform controls with QNative controls.
        return QByteArrayList();
    }
};

QT_END_NAMESPACE

#endif // QNATIVEPLATFORMBASE_H
