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

#include "quniandroidseekbar_p.h"
#include "quniandroidabsseekbar_p_p.h"

QT_BEGIN_NAMESPACE

static void native_onProgressChanged(JNIEnv *env, jobject object, jlong instance, jint progress, jboolean fromUser)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidSeekBar *bar = reinterpret_cast<QUniAndroidSeekBar *>(instance);
    if (bar && fromUser)
        QMetaObject::invokeMethod(bar, "updateProgress", Qt::QueuedConnection, Q_ARG(int, progress));
}

static void registerNativeSeekBarMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onProgressChanged", "(JIZ)V", reinterpret_cast<void *>(native_onProgressChanged)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QUniAndroidSeekBarPrivate : public QUniAndroidAbsSeekBarPrivate
{
public:
    QAndroidJniObject listener;
};

QUniAndroidSeekBar::QUniAndroidSeekBar(QUniAndroidContext *context)
    : QUniAndroidAbsSeekBar(*(new QUniAndroidSeekBarPrivate), context)
{
}

QAndroidJniObject QUniAndroidSeekBar::onCreate()
{
    return QAndroidJniObject("android/widget/SeekBar",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidSeekBar::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidSeekBar);
    QUniAndroidAbsSeekBar::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/widget/QtUniSeekBarListener",
                                   "(Landroid/widget/SeekBar;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeSeekBarMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }
}

QT_END_NAMESPACE
