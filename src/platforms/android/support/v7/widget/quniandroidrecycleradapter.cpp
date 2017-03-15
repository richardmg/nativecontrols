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

#include "quniandroidrecycleradapter_p.h"
#include "quniandroidcontextual_p_p.h"
#include "qtnativeandroidfunctions_p.h"
#include "quniandroidview_p.h"
#include <QtQml/qqmlcomponent.h>
#include <QtQml/qqmlcontext.h>

QT_BEGIN_NAMESPACE

class QNativeAndroidRecyclerAdapterPrivate : public QNativeAndroidContextualPrivate
{
    Q_DECLARE_PUBLIC(QNativeAndroidRecyclerAdapter)

public:
    static QNativeAndroidRecyclerAdapterPrivate *get(QNativeAndroidRecyclerAdapter *adapter)
    {
        return adapter->d_func();
    }

    QNativeAndroidView *_q_createItem();
    void _q_setItemPosition(QNativeAndroidView *item, int position);

    int count = 0;
    QQmlComponent *delegate = nullptr;
    QList<QAndroidJniObject> holders;
};

QNativeAndroidView *QNativeAndroidRecyclerAdapterPrivate::_q_createItem()
{
    Q_Q(QNativeAndroidRecyclerAdapter);
    QNativeAndroidView *item = nullptr;
    if (delegate) {
        QQmlContext *creationContext = delegate->creationContext();
        QQmlContext *context = new QQmlContext(creationContext ? creationContext : qmlContext(q));
        QObject *object = delegate->beginCreate(context);
        if (object) {
            context->setParent(object);
            item = qobject_cast<QNativeAndroidView *>(object);
            if (!item)
                delete object;
        } else {
            delete context;
        }
    } else {
        item = new QNativeAndroidView;
    }
    if (item) {
        item->setContext(q->context());
        item->setParentView(qobject_cast<QNativeAndroidView *>(q->parent())); // TODO
        _q_setItemPosition(item, -1);
    }
    if (delegate)
        delegate->completeCreate();
    return item;
}

void QNativeAndroidRecyclerAdapterPrivate::_q_setItemPosition(QNativeAndroidView *item, int position)
{
    QQmlContext *context = qmlContext(item);
    if (context)
        context = context->parentContext();
    if (context)
        context->setContextProperty(QStringLiteral("position"), position);
}

static jobject native_onCreateViewHolder(JNIEnv *env, jobject object, jlong instance, jobject parent, jint viewType)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    Q_UNUSED(parent);
    Q_UNUSED(viewType);
    QNativeAndroidRecyclerAdapter *adapter = reinterpret_cast<QNativeAndroidRecyclerAdapter *>(instance);
    if (adapter) {
        QNativeAndroidView *item = nullptr;
        QMetaObject::invokeMethod(adapter, "_q_createItem", Qt::BlockingQueuedConnection, Q_RETURN_ARG(QNativeAndroidView *, item));
        item->construct();
        QNativeAndroidRecyclerAdapterPrivate *p = QNativeAndroidRecyclerAdapterPrivate::get(adapter);
        p->holders += QAndroidJniObject("org/qtproject/qt5/android/bindings/support/v7/widget/QtNativeRecyclerAdapter$ViewHolder",
                                        "(Landroid/view/View;J)V",
                                        item->instance().object(),
                                        reinterpret_cast<jlong>(item));
        return p->holders.last().object();
    }
    return 0;
}

static void native_onBindViewHolder(JNIEnv *env, jobject object, jlong instance, jobject holder, jint position)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QNativeAndroidRecyclerAdapter *adapter = reinterpret_cast<QNativeAndroidRecyclerAdapter *>(instance);
    if (adapter) {
        jlong vi = QAndroidJniObject(holder).callMethod<jlong>("getInstance");
        QNativeAndroidView *item = reinterpret_cast<QNativeAndroidView *>(vi);
        if (item)
            QMetaObject::invokeMethod(adapter, "_q_setItemPosition", Qt::BlockingQueuedConnection, Q_ARG(QNativeAndroidView *, item), Q_ARG(int, position));
    }
}

static void registerNativeRecyclerAdapterMethods(jobject adapter)
{
    JNINativeMethod methods[] {{"onCreateViewHolder", "(JLandroid/view/ViewGroup;I)Lorg/qtproject/qt5/android/bindings/support/v7/widget/QtNativeRecyclerAdapter$ViewHolder;", reinterpret_cast<void *>(native_onCreateViewHolder)},
                               {"onBindViewHolder", "(JLorg/qtproject/qt5/android/bindings/support/v7/widget/QtNativeRecyclerAdapter$ViewHolder;I)V", reinterpret_cast<void *>(native_onBindViewHolder)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(adapter);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

QNativeAndroidRecyclerAdapter::QNativeAndroidRecyclerAdapter(QObject *parent)
    : QNativeAndroidContextual(*(new QNativeAndroidRecyclerAdapterPrivate), parent)
{
}

int QNativeAndroidRecyclerAdapter::count() const
{
    Q_D(const QNativeAndroidRecyclerAdapter);
    return d->count;
}

void QNativeAndroidRecyclerAdapter::setCount(int count)
{
    Q_D(QNativeAndroidRecyclerAdapter);
    if (d->count == count)
        return;

    d->count = count;
    QtNativeAndroid::callIntMethod(instance(), "setItemCount", count);
    emit countChanged();
}

QQmlComponent *QNativeAndroidRecyclerAdapter::delegate() const
{
    Q_D(const QNativeAndroidRecyclerAdapter);
    return d->delegate;
}

void QNativeAndroidRecyclerAdapter::setDelegate(QQmlComponent *delegate)
{
    Q_D(QNativeAndroidRecyclerAdapter);
    if (d->delegate == delegate)
        return;

    d->delegate = delegate;
    QtNativeAndroid::callVoidMethod(instance(), "notifyDataSetChanged");
    emit delegateChanged();
}

QAndroidJniObject QNativeAndroidRecyclerAdapter::onCreate()
{
    Q_D(QNativeAndroidRecyclerAdapter);
    return QAndroidJniObject("org/qtproject/qt5/android/bindings/support/v7/widget/QtNativeRecyclerAdapter",
                             "(IJ)V",
                             d->count,
                             reinterpret_cast<jlong>(this));
}

void QNativeAndroidRecyclerAdapter::onInflate(QAndroidJniObject &instance)
{
    Q_D(QNativeAndroidRecyclerAdapter);
    QNativeAndroidContextual::onInflate(instance);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeRecyclerAdapterMethods(instance.object());
        nativeMethodsRegistered = true;
    }

    if (d->count > 0)
        instance.callMethod<void>("setItemCount", "(I)V", d->count);
}

QT_END_NAMESPACE

#include "moc_quniandroidrecycleradapter_p.cpp"
