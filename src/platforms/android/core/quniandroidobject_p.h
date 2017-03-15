/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt QML Android module of the Qt Toolkit.
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

#ifndef QNATIVEANDROIDOBJECT_P_H
#define QNATIVEANDROIDOBJECT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtUniAndroid/private/qtuniandroidglobal_p.h>

#include <QtCore/qobject.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtAndroidExtras/qandroidjniobject.h>
#include <QtAndroidExtras/qandroidjnienvironment.h>

QT_BEGIN_NAMESPACE

class QUniAndroidObjectPrivate;

class Q_NATIVEANDROID_EXPORT QUniAndroidObject : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PRIVATE_PROPERTY(QUniAndroidObject::d_func(), QQmlListProperty<QObject> data READ data NOTIFY dataChanged DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "data")
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit QUniAndroidObject(QObject *parent = nullptr);

    bool isValid() const;
    QAndroidJniObject instance() const;

    void construct();
    void inflate(const QAndroidJniObject &instance);
    void destruct();

    enum ObjectChange {
        InstanceChange
    };

Q_SIGNALS:
    void dataChanged();
    void instanceChanged();

protected:
    QUniAndroidObject(QUniAndroidObjectPrivate &dd, QObject *parent = nullptr);

    virtual QAndroidJniObject onCreate();
    virtual void onInflate(QAndroidJniObject &instance);

    bool isComponentComplete() const;
    void classBegin() override;
    void componentComplete() override;

    virtual void objectChange(ObjectChange change);

    void childEvent(QChildEvent *event) override;

private:
    Q_DISABLE_COPY(QUniAndroidObject)
    Q_DECLARE_PRIVATE(QUniAndroidObject)

    Q_PRIVATE_SLOT(d_func(), void _q_changeInstance())
};

QT_END_NAMESPACE

#endif // QNATIVEANDROIDOBJECT_P_H
