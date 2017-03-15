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

#include "quniandroidobject_p.h"
#include "quniandroidobject_p_p.h"
#include "qtuniandroidfunctions_p.h"

#include <QtCore/qcoreapplication.h>
#include <QtCore/qreadwritelock.h>
#include <QtCore/qcoreevent.h>

QT_BEGIN_NAMESPACE

Q_GLOBAL_STATIC(QReadWriteLock, instanceLock)

QQmlListProperty<QObject> QUniAndroidObjectPrivate::data()
{
    Q_Q(QUniAndroidObject);
    return QQmlListProperty<QObject>(q, this,
                                     &QUniAndroidObjectPrivate::data_append,
                                     &QUniAndroidObjectPrivate::data_count,
                                     &QUniAndroidObjectPrivate::data_at,
                                     nullptr);
}

void QUniAndroidObjectPrivate::data_append(QQmlListProperty<QObject> *list, QObject *object)
{
    if (QUniAndroidObject *that = qobject_cast<QUniAndroidObject *>(list->object))
        object->setParent(that);
}

int QUniAndroidObjectPrivate::data_count(QQmlListProperty<QObject> *list)
{
    if (QUniAndroidObject *that = qobject_cast<QUniAndroidObject *>(list->object))
        return that->children().count();
    return 0;
}

QObject *QUniAndroidObjectPrivate::data_at(QQmlListProperty<QObject> *list, int index)
{
    if (QUniAndroidObject *that = qobject_cast<QUniAndroidObject *>(list->object))
        return that->children().value(index);
    return nullptr;
}

void QUniAndroidObjectPrivate::setInstance(const QAndroidJniObject &newInstance)
{
    Q_Q(QUniAndroidObject);
    QWriteLocker locker(instanceLock());
    if (instance == newInstance)
        return;
    instance = newInstance;
    // queue to Qt thread if necessary
    QMetaObject::invokeMethod(q, "_q_changeInstance", Qt::AutoConnection);
}

void QUniAndroidObjectPrivate::_q_changeInstance()
{
    Q_Q(QUniAndroidObject);
    Q_ASSERT(QtUniAndroid::isMainQtThread());
    q->objectChange(QUniAndroidObject::InstanceChange);
    emit q->instanceChanged();
}

QUniAndroidObject::QUniAndroidObject(QObject *parent)
    : QObject(*(new QUniAndroidObjectPrivate), parent)
{
}

QUniAndroidObject::QUniAndroidObject(QUniAndroidObjectPrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

bool QUniAndroidObject::isValid() const
{
    Q_D(const QUniAndroidObject);
    QReadLocker locker(instanceLock());
    return d->instance.isValid();
}

QAndroidJniObject QUniAndroidObject::instance() const
{
    Q_D(const QUniAndroidObject);
    QReadLocker locker(instanceLock());
    return d->instance;
}

void QUniAndroidObject::construct()
{
    foreach (QObject *obj, children()) {
        QUniAndroidObject *child = qobject_cast<QUniAndroidObject *>(obj);
        if (child)
            child->construct();
    }

    std::function<void()> method = [=]() {
        inflate(onCreate());
    };

    if (QtUniAndroid::isMainQtThread())
        QtUniAndroid::callFunction(method);
    else
        method();
}

void QUniAndroidObject::inflate(const QAndroidJniObject &instance)
{
    Q_D(QUniAndroidObject);
    std::function<void()> method = [=]() {
        QAndroidJniObject object(instance);
        if (object.isValid())
            onInflate(object);
        d->setInstance(object);
    };

    if (QtUniAndroid::isMainQtThread())
        QtUniAndroid::callFunction(method);
    else
        method();
}

void QUniAndroidObject::destruct()
{
    Q_D(QUniAndroidObject);
    foreach (QObject *obj, children()) {
        QUniAndroidObject *child = qobject_cast<QUniAndroidObject *>(obj);
        if (child)
            child->destruct();
    }

    d->setInstance(QAndroidJniObject());
}

QAndroidJniObject QUniAndroidObject::onCreate()
{
    return QAndroidJniObject();
}

void QUniAndroidObject::onInflate(QAndroidJniObject &instance)
{
    Q_UNUSED(instance);
    Q_ASSERT(!QtUniAndroid::isMainQtThread());
}

bool QUniAndroidObject::isComponentComplete() const
{
    Q_D(const QUniAndroidObject);
    return d->complete;
}

void QUniAndroidObject::classBegin()
{
}

void QUniAndroidObject::componentComplete()
{
    Q_D(QUniAndroidObject);
    d->complete = true;
}

void QUniAndroidObject::objectChange(ObjectChange change)
{
    Q_ASSERT(QtUniAndroid::isMainQtThread());
    Q_UNUSED(change);
}

void QUniAndroidObject::childEvent(QChildEvent *event)
{
    if (event->added())
        emit dataChanged();
    else if (event->removed())
        emit dataChanged();
}

QT_END_NAMESPACE

#include "moc_quniandroidobject_p.cpp"
