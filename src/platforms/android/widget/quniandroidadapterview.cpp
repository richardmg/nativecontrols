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

#include "quniandroidadapterview_p.h"
#include "quniandroidadapterview_p_p.h"
#include "quniandroidbaseadapter_p.h"
#include "qtuniandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onItemClick(JNIEnv *env, jobject object, jlong instance, jint position)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidAdapterView *view = reinterpret_cast<QUniAndroidAdapterView *>(instance);
    if (view)
        QMetaObject::invokeMethod(view, "click", Qt::QueuedConnection, Q_ARG(int, position));
}

static void registerNativeAdapterViewMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onItemClick", "(JI)V", reinterpret_cast<void *>(native_onItemClick)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

void QUniAndroidAdapterViewPrivate::updateAdapter()
{
    Q_Q(QUniAndroidAdapterView);
    if (!q->isValid())
        return;

    QAndroidJniObject ad;
    if (adapter)
        ad = adapter->instance();

    QAndroidJniObject view = q->instance();
    QtUniAndroid::callFunction([=]() {
        view.callMethod<void>("setAdapter", "(Landroid/widget/Adapter;)V", ad.object());
    });
}

QUniAndroidAdapterView::QUniAndroidAdapterView(QUniAndroidContext *context)
    : QUniAndroidViewGroup(*(new QUniAndroidAdapterViewPrivate), context)
{
}

QUniAndroidBaseAdapter *QUniAndroidAdapterView::adapter() const
{
    Q_D(const QUniAndroidAdapterView);
    return d->adapter;
}

void QUniAndroidAdapterView::setAdapter(QUniAndroidBaseAdapter *adapter)
{
    Q_D(QUniAndroidAdapterView);
    if (d->adapter == adapter)
        return;

    if (d->adapter) {
        d->adapter->setContext(0);
        QObjectPrivate::disconnect(d->adapter, &QUniAndroidObject::instanceChanged, d, &QUniAndroidAdapterViewPrivate::updateAdapter);
        d->adapter->destruct();
    }
    d->adapter = adapter;
    if (d->adapter) {
        d->adapter->setContext(context());
        QObjectPrivate::connect(d->adapter, &QUniAndroidObject::instanceChanged, d, &QUniAndroidAdapterViewPrivate::updateAdapter);
        if (isValid())
            d->adapter->construct();
    }
    emit adapterChanged();
}

void QUniAndroidAdapterView::setSelection(int position)
{
    QtUniAndroid::callIntMethod(instance(), "setSelection", position);
}

QAndroidJniObject QUniAndroidAdapterView::onCreate()
{
    return QAndroidJniObject("android/widget/AdapterView",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidAdapterView::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidAdapterView);
    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/widget/QtUniAdapterViewListener",
                                   "(Landroid/widget/AdapterView;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    QUniAndroidViewGroup::onInflate(instance);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeAdapterViewMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }
}

void QUniAndroidAdapterView::objectChange(ObjectChange change)
{
    Q_D(QUniAndroidAdapterView);
    QUniAndroidViewGroup::objectChange(change);
    if (change == InstanceChange)
        d->updateAdapter();
}

QT_END_NAMESPACE
