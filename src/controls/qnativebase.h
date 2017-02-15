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

#ifndef QNATIVEBASE_H
#define QNATIVEBASE_H

#include <QObject>
#include <QQmlListProperty>
#include <QtNativeControls/qnativecontrolsglobal.h>
#include <QtNativeControls/qnativeqmlbase.h>

QT_BEGIN_NAMESPACE

class QNativePlatformBase;
class QNativeBasePrivate;

class Q_NATIVECONTROLS_EXPORT QNativeBase : public QNativeQmlBase
{
    Q_OBJECT

public:
    explicit QNativeBase(QNativeBase *parent = nullptr);
    virtual ~QNativeBase();

    void setParent(QNativeBase *parent);
    bool setNativeParent(QObject *parent);
    bool setNativeParent(const QByteArray &type, void *parent);
    bool addNativeChild(QObject *child);
    bool addNativeChild(const QByteArray &type, void *child);
    QByteArrayList supportedNativeChildTypes();
    QByteArrayList supportedNativeParentTypes();

protected:
    QNativeBase(QNativeBasePrivate &dd, QNativeBase *parent = nullptr);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QNativeBase)
    Q_DISABLE_COPY(QNativeBase)
};

QT_END_NAMESPACE

#endif // QNATIVEBASE_H
