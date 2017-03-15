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

class QUniAndroidRecyclerAdapterPrivate : public QUniAndroidContextualPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidRecyclerAdapter)

public:
    static QUniAndroidRecyclerAdapterPrivate *get(QUniAndroidRecyclerAdapter *adapter)
    {
        return adapter->d_func();
    }

    QUniAndroidView *_q_createItem();
    void _q_setItemPosition(QUniAndroidView *item, int position);

    int count = 0;
    QQmlComponent *delegate = nullptr;
    QList<QAndroidJniObject> holders;
};

QUniAndroidView *QUniAndroidRecyclerAdapterPrivate::_q_createItem()
{
    Q_Q(QUniAndroidRecyclerAdapter);
    QUniAndroidView *item = nullptr;
    if (delegate) {
        QQmlContext *creationContext = delegate->creationContext();
        QQmlContext *context = new QQmlContext(creationContext ? creationContext : qmlContext(q));
        QObject *object = delegate->beginCreate(context);
        if (object) {
            context->setParent(object);
            item = qobject_cast<QUniAndroidView *>(object);
            if (!item)
                delete object;
        } else {
            delete context;
        }
    } else {
        item = new QUniAndroidView;
    }
    if (item) {
        item->setContext(q->context());
        item->setParentView(qobject_cast<QUniAndroidView *>(q->parent())); // TODO
        _q_setItemPosition(item, -1);
    }
    if (delegate)
        delegate->completeCreate();
    return item;
}

void QUniAndroidRecyclerAdapterPrivate::_q_setItemPosition(QUniAndroidView *item, int position)
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
    QUniAndroidRecyclerAdapter *adapter = reinterpret_cast<QUniAndroidRecyclerAdapter *>(instance);
    if (adapter) {
        QUniAndroidView *item = nullptr;
        QMetaObject::invokeMethod(adapter, "_q_createItem", Qt::BlockingQueuedConnection, Q_RETURN_ARG(QUniAndroidView *, item));
        item->construct();
        QUniAndroidRecyclerAdapterPrivate *p = QUniAndroidRecyclerAdapterPrivate::get(adapter);
        p->holders += QAndroidJniObject("org/qtproject/qt5/android/bindings/support/v7/widget/QtUniRecyclerAdapter$ViewHolder",
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
    QUniAndroidRecyclerAdapter *adapter = reinterpret_cast<QUniAndroidRecyclerAdapter *>(instance);
    if (adapter) {
        jlong vi = QAndroidJniObject(holder).callMethod<jlong>("getInstance");
        QUniAndroidView *item = reinterpret_cast<QUniAndroidView *>(vi);
        if (item)
            QMetaObject::invokeMethod(adapter, "_q_setItemPosition", Qt::BlockingQueuedConnection, Q_ARG(QUniAndroidView *, item), Q_ARG(int, position));
    }
}

static void registerNativeRecyclerAdapterMethods(jobject adapter)
{
    JNINativeMethod methods[] {{"onCreateViewHolder", "(JLandroid/view/ViewGroup;I)Lorg/qtproject/qt5/android/bindings/support/v7/widget/QtUniRecyclerAdapter$ViewHolder;", reinterpret_cast<void *>(native_onCreateViewHolder)},
                               {"onBindViewHolder", "(JLorg/qtproject/qt5/android/bindings/support/v7/widget/QtUniRecyclerAdapter$ViewHolder;I)V", reinterpret_cast<void *>(native_onBindViewHolder)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(adapter);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

QUniAndroidRecyclerAdapter::QUniAndroidRecyclerAdapter(QObject *parent)
    : QUniAndroidContextual(*(new QUniAndroidRecyclerAdapterPrivate), parent)
{
}

int QUniAndroidRecyclerAdapter::count() const
{
    Q_D(const QUniAndroidRecyclerAdapter);
    return d->count;
}

void QUniAndroidRecyclerAdapter::setCount(int count)
{
    Q_D(QUniAndroidRecyclerAdapter);
    if (d->count == count)
        return;

    d->count = count;
    QtUniAndroid::callIntMethod(instance(), "setItemCount", count);
    emit countChanged();
}

QQmlComponent *QUniAndroidRecyclerAdapter::delegate() const
{
    Q_D(const QUniAndroidRecyclerAdapter);
    return d->delegate;
}

void QUniAndroidRecyclerAdapter::setDelegate(QQmlComponent *delegate)
{
    Q_D(QUniAndroidRecyclerAdapter);
    if (d->delegate == delegate)
        return;

    d->delegate = delegate;
    QtUniAndroid::callVoidMethod(instance(), "notifyDataSetChanged");
    emit delegateChanged();
}

QAndroidJniObject QUniAndroidRecyclerAdapter::onCreate()
{
    Q_D(QUniAndroidRecyclerAdapter);
    return QAndroidJniObject("org/qtproject/qt5/android/bindings/support/v7/widget/QtUniRecyclerAdapter",
                             "(IJ)V",
                             d->count,
                             reinterpret_cast<jlong>(this));
}

void QUniAndroidRecyclerAdapter::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidRecyclerAdapter);
    QUniAndroidContextual::onInflate(instance);

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
