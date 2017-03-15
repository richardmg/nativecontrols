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

#include "quniandroidswiperefreshlayout_p.h"
#include "quniandroidviewgroup_p_p.h"
#include "qtuniandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onRefresh(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidSwipeRefreshLayout *layout = reinterpret_cast<QUniAndroidSwipeRefreshLayout *>(instance);
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

class QUniAndroidSwipeRefreshLayoutPrivate : public QUniAndroidViewGroupPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidSwipeRefreshLayout)

public:
    bool _q_updateRefreshing(bool refreshing);

    bool refreshing = false;
    QAndroidJniObject listener;
};

bool QUniAndroidSwipeRefreshLayoutPrivate::_q_updateRefreshing(bool arg)
{
    Q_Q(QUniAndroidSwipeRefreshLayout);
    if (refreshing == arg)
        return false;

    refreshing = arg;
    emit q->refreshingChanged();
    return true;
}

QUniAndroidSwipeRefreshLayout::QUniAndroidSwipeRefreshLayout(QUniAndroidContext *context)
    : QUniAndroidViewGroup(*(new QUniAndroidSwipeRefreshLayoutPrivate), context)
{
}

bool QUniAndroidSwipeRefreshLayout::isRefreshing() const
{
    Q_D(const QUniAndroidSwipeRefreshLayout);
    return d->refreshing;
}

void QUniAndroidSwipeRefreshLayout::setRefreshing(bool refreshing)
{
    Q_D(QUniAndroidSwipeRefreshLayout);
    if (d->_q_updateRefreshing(refreshing))
        QtUniAndroid::callBoolMethod(instance(), "setRefreshing", refreshing);
}

QAndroidJniObject QUniAndroidSwipeRefreshLayout::onCreate()
{
    return QAndroidJniObject("android/support/v4/widget/SwipeRefreshLayout",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidSwipeRefreshLayout::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidSwipeRefreshLayout);
    QUniAndroidViewGroup::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/support/v4/widget/QtUniSwipeRefreshLayoutListener",
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
