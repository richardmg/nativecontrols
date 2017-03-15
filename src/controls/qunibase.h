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
#include <QtNativeControls/qunicontrolsglobal.h>
#include <QtNativeControls/quniqmlbase.h>

QT_BEGIN_NAMESPACE

class QUniPlatformBase;
class QUniBasePrivate;

class Q_NATIVECONTROLS_EXPORT QUniBase : public QUniQmlBase
{
    Q_OBJECT
    Q_PROPERTY(QUniBase *parent READ parentBase WRITE setParent NOTIFY parentChanged DESIGNABLE false)

public:
    explicit QUniBase(QUniBase *parent = nullptr);
    virtual ~QUniBase();

    void setParent(QUniBase *parent);
    QUniBase *parentBase();

    bool setNativeParent(QObject *parent);
    bool setNativeParent(const QByteArray &type, void *parent);
    bool addNativeChild(QObject *child);
    bool addNativeChild(const QByteArray &type, void *child);
    QByteArrayList supportedNativeChildTypes();
    QByteArrayList supportedNativeParentTypes();

Q_SIGNALS:
    void parentChanged(QUniBase *parent);

protected:
    QUniBase(QUniBasePrivate &dd, QUniBase *parent = nullptr);
    void childEvent(QChildEvent *event) override;

private:
    Q_DECLARE_PRIVATE(QUniBase)
    Q_DISABLE_COPY(QUniBase)
};

QT_END_NAMESPACE

#endif // QNATIVEBASE_H
