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

#include "quniandroidservice_p.h"
#include "quniandroidcontextwrapper_p_p.h"
#include "qtuniandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onCreated(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    Q_UNUSED(instance);
//    QUniAndroidService *service = reinterpret_cast<QUniAndroidService *>(instance);
//    if (service)
//        QMetaObject::invokeMethod(service, "created", Qt::QueuedConnection);
}

static void native_onDestroyed(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidService *service = reinterpret_cast<QUniAndroidService *>(instance);
    if (service)
        QMetaObject::invokeMethod(service, "stopped", Qt::QueuedConnection);
}

static jboolean native_onStartCommand(JNIEnv *env, jobject object, jlong instance, jint flags, jint startId)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidService *service = reinterpret_cast<QUniAndroidService *>(instance);
    bool ret = false;
    if (service) {
        QMetaObject::invokeMethod(service, "_q_startCommand", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, ret), Q_ARG(int, flags), Q_ARG(int, startId));
        QMetaObject::invokeMethod(service, "started", Qt::QueuedConnection);
    }
    return ret;
}

static void registerNativeServiceMethods(jobject service)
{
    JNINativeMethod methods[] {{"onCreated", "(J)V", reinterpret_cast<void *>(native_onCreated)},
                               {"onDestroyed", "(J)V", reinterpret_cast<void *>(native_onDestroyed)},
                               {"onStartCommand", "(JII)Z", reinterpret_cast<void *>(native_onStartCommand)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(service);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QUniAndroidServicePrivate : public QUniAndroidContextWrapperPrivate
{
public:
    bool _q_startCommand(int flags, int startId);

    bool sticky = true;
};

bool QUniAndroidServicePrivate::_q_startCommand(int flags, int startId)
{
    Q_UNUSED(flags);
    Q_UNUSED(startId);
    return sticky;
}

QUniAndroidService::QUniAndroidService(QObject *parent)
    : QUniAndroidContextWrapper(*(new QUniAndroidServicePrivate), nullptr, parent)
{
}

bool QUniAndroidService::isSticky() const
{
    Q_D(const QUniAndroidService);
    return d->sticky;
}

void QUniAndroidService::setSticky(bool sticky)
{
    Q_D(QUniAndroidService);
    if (d->sticky == sticky)
        return;

    d->sticky = sticky;
    emit stickyChanged();
}

void QUniAndroidService::start()
{
    QAndroidJniObject context = ctx();
    QAndroidJniObject service = instance();

    if (!context.isValid() || !service.isValid())
        return; // TODO: warn

    QtUniAndroid::callFunction([=]() {
        QAndroidJniObject cls = service.callObjectMethod("getClass", "()Ljava/lang/Class;");
        QAndroidJniObject intent = QAndroidJniObject("android/content/Intent",
                                                     "(Landroid/content/Context;Ljava/lang/Class;)V",
                                                     context.object(),
                                                     cls.object());
        intent.callObjectMethod("putExtra",
                                "(Ljava/lang/String;J)Landroid/content/Intent;",
                                QAndroidJniObject::fromString(QStringLiteral("QtUniService")).object(),
                                reinterpret_cast<jlong>(this));
        QAndroidJniObject component = context.callObjectMethod("startService",
                                                               "(Landroid/content/Intent;)Landroid/content/ComponentName;",
                                                               intent.object());
        Q_UNUSED(component);
    });
}

void QUniAndroidService::stop()
{
    QAndroidJniObject context = ctx();
    QAndroidJniObject service = instance();

    if (!context.isValid() || !service.isValid())
        return; // TODO: warn

    QtUniAndroid::callFunction([=]() {
        QAndroidJniObject cls = service.callObjectMethod("getClass", "()Ljava/lang/Class;");
        QAndroidJniObject intent = QAndroidJniObject("android/content/Intent",
                                                     "(Landroid/content/Context;Ljava/lang/Class;)V",
                                                     context.object(),
                                                     cls.object());
        intent.callObjectMethod("putExtra",
                                "(Ljava/lang/String;J)Landroid/content/Intent;",
                                QAndroidJniObject::fromString(QStringLiteral("QtUniService")).object(),
                                reinterpret_cast<jlong>(this));
        context.callMethod<jboolean>("stopService",
                                     "(Landroid/content/Intent;)Z",
                                     intent.object());
    });
}

QAndroidJniObject QUniAndroidService::onCreate()
{
    return QAndroidJniObject("org/qtproject/qt5/android/bindings/app/QtUniService");
}

void QUniAndroidService::onInflate(QAndroidJniObject& instance)
{
    QUniAndroidContextWrapper::onInflate(instance);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeServiceMethods(instance.object());
        nativeMethodsRegistered = true;
    }
}

QT_END_NAMESPACE

#include "moc_quniandroidservice_p.cpp"
