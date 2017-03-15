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

#include "quniandroidradiogroup_p.h"
#include "quniandroidlinearlayout_p_p.h"
#include "quniandroidradiobutton_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onCheckedChanged(JNIEnv *env, jobject object, jlong instance, jint checkedId)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidRadioGroup *group = reinterpret_cast<QUniAndroidRadioGroup *>(instance);
    if (group)
        QMetaObject::invokeMethod(group, "_q_updateCheckedButtonId", Qt::QueuedConnection, Q_ARG(int, checkedId));
}

static void registerNativeRadioGroupMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onCheckedChanged", "(JI)V", reinterpret_cast<void *>(native_onCheckedChanged)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QUniAndroidRadioGroupPrivate : public QUniAndroidLinearLayoutPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidRadioGroup)

public:
    void _q_updateCheckedButtonId(int checkedId);
    bool _q_updateCheckedButton(QUniAndroidRadioButton *button);

    QAndroidJniObject listener;
    QUniAndroidRadioButton* checkedButton = nullptr;
};

void QUniAndroidRadioGroupPrivate::_q_updateCheckedButtonId(int checkedId)
{
    Q_Q(QUniAndroidRadioGroup);
    foreach (QObject *child, q->children()) {
        QUniAndroidRadioButton *button = qobject_cast<QUniAndroidRadioButton *>(child);
        if (button && button->identifier() == checkedId) {
            _q_updateCheckedButton(button);
            return;
        }
    }
    _q_updateCheckedButton(nullptr);
}

bool QUniAndroidRadioGroupPrivate::_q_updateCheckedButton(QUniAndroidRadioButton *button)
{
    Q_Q(QUniAndroidRadioGroup);
    if (checkedButton == button)
        return false;

    checkedButton = button;
    emit q->checkedButtonChanged();
    return true;
}

QUniAndroidRadioGroup::QUniAndroidRadioGroup(QUniAndroidContext *context)
    : QUniAndroidLinearLayout(*(new QUniAndroidRadioGroupPrivate), context)
{
}

QUniAndroidRadioButton *QUniAndroidRadioGroup::checkedButton() const
{
    Q_D(const QUniAndroidRadioGroup);
    return d->checkedButton;
}

void QUniAndroidRadioGroup::setCheckedButton(QUniAndroidRadioButton *button)
{
    Q_D(QUniAndroidRadioGroup);
    if (d->_q_updateCheckedButton(button))
        QtNativeAndroid::callIntMethod(instance(), "check", button ? button->identifier() : -1);
}

void QUniAndroidRadioGroup::clearCheck()
{
    QtNativeAndroid::callVoidMethod(instance(), "clearCheck");
}

QAndroidJniObject QUniAndroidRadioGroup::onCreate()
{
    return QAndroidJniObject("android/widget/RadioGroup",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidRadioGroup::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidRadioGroup);
    QUniAndroidLinearLayout::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/widget/QtNativeRadioGroupListener",
                                   "(Landroid/widget/RadioGroup;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeRadioGroupMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }

    int checkedId = instance.callMethod<int>("getCheckedRadioButtonId", "()I");
    QMetaObject::invokeMethod(this, "_q_updateCheckedButtonId", Qt::QueuedConnection, Q_ARG(int, checkedId));
}

QT_END_NAMESPACE

#include "moc_quniandroidradiogroup_p.cpp"
