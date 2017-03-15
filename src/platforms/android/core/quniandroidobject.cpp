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
#include "qtnativeandroidfunctions_p.h"

#include <QtCore/qcoreapplication.h>
#include <QtCore/qreadwritelock.h>
#include <QtCore/qcoreevent.h>

QT_BEGIN_NAMESPACE

Q_GLOBAL_STATIC(QReadWriteLock, instanceLock)

QQmlListProperty<QObject> QNativeAndroidObjectPrivate::data()
{
    Q_Q(QNativeAndroidObject);
    return QQmlListProperty<QObject>(q, this,
                                     &QNativeAndroidObjectPrivate::data_append,
                                     &QNativeAndroidObjectPrivate::data_count,
                                     &QNativeAndroidObjectPrivate::data_at,
                                     nullptr);
}

void QNativeAndroidObjectPrivate::data_append(QQmlListProperty<QObject> *list, QObject *object)
{
    if (QNativeAndroidObject *that = qobject_cast<QNativeAndroidObject *>(list->object))
        object->setParent(that);
}

int QNativeAndroidObjectPrivate::data_count(QQmlListProperty<QObject> *list)
{
    if (QNativeAndroidObject *that = qobject_cast<QNativeAndroidObject *>(list->object))
        return that->children().count();
    return 0;
}

QObject *QNativeAndroidObjectPrivate::data_at(QQmlListProperty<QObject> *list, int index)
{
    if (QNativeAndroidObject *that = qobject_cast<QNativeAndroidObject *>(list->object))
        return that->children().value(index);
    return nullptr;
}

void QNativeAndroidObjectPrivate::setInstance(const QAndroidJniObject &newInstance)
{
    Q_Q(QNativeAndroidObject);
    QWriteLocker locker(instanceLock());
    if (instance == newInstance)
        return;
    instance = newInstance;
    // queue to Qt thread if necessary
    QMetaObject::invokeMethod(q, "_q_changeInstance", Qt::AutoConnection);
}

void QNativeAndroidObjectPrivate::_q_changeInstance()
{
    Q_Q(QNativeAndroidObject);
    Q_ASSERT(QtNativeAndroid::isMainQtThread());
    q->objectChange(QNativeAndroidObject::InstanceChange);
    emit q->instanceChanged();
}

QNativeAndroidObject::QNativeAndroidObject(QObject *parent)
    : QObject(*(new QNativeAndroidObjectPrivate), parent)
{
}

QNativeAndroidObject::QNativeAndroidObject(QNativeAndroidObjectPrivate &dd, QObject *parent)
    : QObject(dd, parent)
{
}

bool QNativeAndroidObject::isValid() const
{
    Q_D(const QNativeAndroidObject);
    QReadLocker locker(instanceLock());
    return d->instance.isValid();
}

QAndroidJniObject QNativeAndroidObject::instance() const
{
    Q_D(const QNativeAndroidObject);
    QReadLocker locker(instanceLock());
    return d->instance;
}

void QNativeAndroidObject::construct()
{
    foreach (QObject *obj, children()) {
        QNativeAndroidObject *child = qobject_cast<QNativeAndroidObject *>(obj);
        if (child)
            child->construct();
    }

    std::function<void()> method = [=]() {
        inflate(onCreate());
    };

    if (QtNativeAndroid::isMainQtThread())
        QtNativeAndroid::callFunction(method);
    else
        method();
}

void QNativeAndroidObject::inflate(const QAndroidJniObject &instance)
{
    Q_D(QNativeAndroidObject);
    std::function<void()> method = [=]() {
        QAndroidJniObject object(instance);
        if (object.isValid())
            onInflate(object);
        d->setInstance(object);
    };

    if (QtNativeAndroid::isMainQtThread())
        QtNativeAndroid::callFunction(method);
    else
        method();
}

void QNativeAndroidObject::destruct()
{
    Q_D(QNativeAndroidObject);
    foreach (QObject *obj, children()) {
        QNativeAndroidObject *child = qobject_cast<QNativeAndroidObject *>(obj);
        if (child)
            child->destruct();
    }

    d->setInstance(QAndroidJniObject());
}

QAndroidJniObject QNativeAndroidObject::onCreate()
{
    return QAndroidJniObject();
}

void QNativeAndroidObject::onInflate(QAndroidJniObject &instance)
{
    Q_UNUSED(instance);
    Q_ASSERT(!QtNativeAndroid::isMainQtThread());
}

bool QNativeAndroidObject::isComponentComplete() const
{
    Q_D(const QNativeAndroidObject);
    return d->complete;
}

void QNativeAndroidObject::classBegin()
{
}

void QNativeAndroidObject::componentComplete()
{
    Q_D(QNativeAndroidObject);
    d->complete = true;
}

void QNativeAndroidObject::objectChange(ObjectChange change)
{
    Q_ASSERT(QtNativeAndroid::isMainQtThread());
    Q_UNUSED(change);
}

void QNativeAndroidObject::childEvent(QChildEvent *event)
{
    if (event->added())
        emit dataChanged();
    else if (event->removed())
        emit dataChanged();
}

QT_END_NAMESPACE

#include "moc_quniandroidobject_p.cpp"
