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

#include "quniandroidcompoundbutton_p.h"
#include "quniandroidcompoundbutton_p_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onCheckedChanged(JNIEnv *env, jobject object, jlong instance, jboolean isChecked)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidCompoundButton *button = reinterpret_cast<QUniAndroidCompoundButton *>(instance);
    if (button)
        QMetaObject::invokeMethod(button, "_q_updateChecked", Qt::QueuedConnection, Q_ARG(bool, isChecked));
}

static void registerNativeCompoundButtonMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onCheckedChanged", "(JZ)V", reinterpret_cast<void *>(native_onCheckedChanged)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

bool QUniAndroidCompoundButtonPrivate::_q_updateChecked(bool arg)
{
    Q_Q(QUniAndroidCompoundButton);
    if (arg == q->isChecked())
        return false;

    checked = arg;
    emit q->checkedChanged();
    return true;
}

QUniAndroidCompoundButton::QUniAndroidCompoundButton(QUniAndroidContext *context)
    : QUniAndroidButton(*(new QUniAndroidCompoundButtonPrivate), context)
{
}

QUniAndroidCompoundButton::QUniAndroidCompoundButton(QUniAndroidCompoundButtonPrivate &dd, QUniAndroidContext *context)
    : QUniAndroidButton(dd, context)
{
}

bool QUniAndroidCompoundButton::isChecked() const
{
    Q_D(const QUniAndroidCompoundButton);
    return d->checked;
}

void QUniAndroidCompoundButton::setChecked(bool checked)
{
    Q_D(QUniAndroidCompoundButton);
    if (d->_q_updateChecked(checked))
        QtUniAndroid::callBoolMethod(instance(), "setChecked", checked);
}

void QUniAndroidCompoundButton::toggle()
{
    QtUniAndroid::callVoidMethod(instance(), "toggle");
}

QAndroidJniObject QUniAndroidCompoundButton::onCreate()
{
    return QAndroidJniObject("android/widget/CompoundButton",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidCompoundButton::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidCompoundButton);
    QUniAndroidButton::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/widget/QtUniCompoundButtonListener",
                                   "(Landroid/widget/CompoundButton;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeCompoundButtonMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }

    instance.callMethod<void>("setChecked", "(Z)V", d->checked);
}

QT_END_NAMESPACE

#include "moc_quniandroidcompoundbutton_p.cpp"
