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
#include <QtNativeControls/qunicontrolsglobal.h>

QT_BEGIN_NAMESPACE

class Q_NATIVECONTROLS_EXPORT QUniPlatformBase
{
public:
    virtual ~QUniPlatformBase() {}

    virtual void setPlatformParent(QUniPlatformBase *) = 0;

    /**
     * \sa QUniBase::setNativeParent(QObject *parent)
     */
    virtual bool setNativeParent(QObject *parent)
    {
        // Override to support mixing platform controls with QUni controls.
        Q_UNUSED(parent);
        return false;
    }

    /**
     * \sa QUniBase::setNativeParent(const QByteArray &type, void *parent)
     */
    virtual bool setNativeParent(const QByteArray &type, void *parent)
    {
        // Override to support mixing platform controls with QUni controls.
        Q_UNUSED(type);
        Q_UNUSED(parent);
        return false;
    }

    /**
     * \sa QUniBase::addNativeChild(QObject *child)
     */
    virtual bool addNativeChild(QObject *child)
    {
        // Override to support mixing platform controls with QUni controls.
        Q_UNUSED(child);
        return false;
    }

    /**
     * \sa QUniBase::addNativeChild(const QByteArray &type, void *child)
     */
    virtual bool addNativeChild(const QByteArray &type, void *child)
    {
        // Override to support mixing platform controls with QUni controls.
        Q_UNUSED(type);
        Q_UNUSED(child);
        return false;
    }

    /**
     * Query the type names supported by addNativeChild().
     */
    virtual QByteArrayList supportedNativeChildTypes()
    {
        // Override to support mixing platform controls with QUni controls.
        return QByteArrayList();
    }

    /**
     * Query the type names supported by setNativeParent().
     */
    virtual QByteArrayList supportedNativeParentTypes()
    {
        // Override to support mixing platform controls with QUni controls.
        return QByteArrayList();
    }
};

QT_END_NAMESPACE

#endif // QNATIVEPLATFORMBASE_H
