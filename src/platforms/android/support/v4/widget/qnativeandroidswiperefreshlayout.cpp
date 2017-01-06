/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#include "qnativeandroidswiperefreshlayout_p.h"
#include "qnativeandroidviewgroup_p_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onRefresh(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QNativeAndroidSwipeRefreshLayout *layout = reinterpret_cast<QNativeAndroidSwipeRefreshLayout *>(instance);
    if (layout)
        QMetaObject::invokeMethod(layout, "_q_updateRefreshing", Qt::QueuedConnection, Q_ARG(bool, true));
}

static void registerNativeSwipeRefreshLayoutMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onRefresh", "(J)V", reinterpret_cast<void *>(native_onRefresh)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QNativeAndroidSwipeRefreshLayoutPrivate : public QNativeAndroidViewGroupPrivate
{
    Q_DECLARE_PUBLIC(QNativeAndroidSwipeRefreshLayout)

public:
    bool _q_updateRefreshing(bool refreshing);

    bool refreshing = false;
    QAndroidJniObject listener;
};

bool QNativeAndroidSwipeRefreshLayoutPrivate::_q_updateRefreshing(bool arg)
{
    Q_Q(QNativeAndroidSwipeRefreshLayout);
    if (refreshing == arg)
        return false;

    refreshing = arg;
    emit q->refreshingChanged();
    return true;
}

QNativeAndroidSwipeRefreshLayout::QNativeAndroidSwipeRefreshLayout(QNativeAndroidContext *context)
    : QNativeAndroidViewGroup(*(new QNativeAndroidSwipeRefreshLayoutPrivate), context)
{
}

bool QNativeAndroidSwipeRefreshLayout::isRefreshing() const
{
    Q_D(const QNativeAndroidSwipeRefreshLayout);
    return d->refreshing;
}

void QNativeAndroidSwipeRefreshLayout::setRefreshing(bool refreshing)
{
    Q_D(QNativeAndroidSwipeRefreshLayout);
    if (d->_q_updateRefreshing(refreshing))
        QtNativeAndroid::callBoolMethod(instance(), "setRefreshing", refreshing);
}

QAndroidJniObject QNativeAndroidSwipeRefreshLayout::onCreate()
{
    return QAndroidJniObject("android/support/v4/widget/SwipeRefreshLayout",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QNativeAndroidSwipeRefreshLayout::onInflate(QAndroidJniObject &instance)
{
    Q_D(QNativeAndroidSwipeRefreshLayout);
    QNativeAndroidViewGroup::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/support/v4/widget/QtNativeSwipeRefreshLayoutListener",
                                   "(Landroid/support/v4/widget/SwipeRefreshLayout;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeSwipeRefreshLayoutMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }
}

QT_END_NAMESPACE
