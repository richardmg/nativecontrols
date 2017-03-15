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

#include "quniandroidnumberpicker_p.h"
#include "quniandroidlinearlayout_p_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onValueChange(JNIEnv *env, jobject object, jlong instance, jint value)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidNumberPicker *picker = reinterpret_cast<QUniAndroidNumberPicker *>(instance);
    if (picker)
        QMetaObject::invokeMethod(picker, "_q_updateValue", Qt::QueuedConnection, Q_ARG(int, value));
}

static void registerNativeNumberPickerMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onValueChange", "(JI)V", reinterpret_cast<void *>(native_onValueChange)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QUniAndroidNumberPickerPrivate : public QUniAndroidLinearLayoutPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidNumberPicker)

public:
    bool _q_updateValue(int value);

    int value = 0;
    QAndroidJniObject listener;
};

bool QUniAndroidNumberPickerPrivate::_q_updateValue(int arg)
{
    Q_Q(QUniAndroidNumberPicker);
    if (value == arg)
        return false;

    value = arg;
    emit q->valueChanged();
    return true;
}

QUniAndroidNumberPicker::QUniAndroidNumberPicker(QUniAndroidContext *context)
    : QUniAndroidLinearLayout(*(new QUniAndroidNumberPickerPrivate), context)
{
}

int QUniAndroidNumberPicker::value() const
{
    Q_D(const QUniAndroidNumberPicker);
    return d->value;
}

void QUniAndroidNumberPicker::setValue(int value)
{
    Q_D(QUniAndroidNumberPicker);
    if (d->_q_updateValue(value))
        QtNativeAndroid::callIntMethod(instance(), "setValue", value);
}

QAndroidJniObject QUniAndroidNumberPicker::onCreate()
{
    return QAndroidJniObject("android/widget/NumberPicker",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidNumberPicker::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidNumberPicker);
    QUniAndroidLinearLayout::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/widget/QtNativeNumberPickerListener",
                                   "(Landroid/widget/NumberPicker;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeNumberPickerMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }

    instance.callMethod<void>("setValue", "(I)V", d->value);
}

QT_END_NAMESPACE

#include "moc_quniandroidnumberpicker_p.cpp"
