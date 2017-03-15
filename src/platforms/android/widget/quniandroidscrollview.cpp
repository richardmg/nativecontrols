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

#include "qnativeandroidscrollview_p.h"
#include "qnativeandroidframelayout_p_p.h"
#include "qtnativeandroidfunctions_p.h"
#include "qnativeandroidoptional_p.h"

QT_BEGIN_NAMESPACE

static void native_onScrollChanged(JNIEnv *env, jobject object, jlong instance, jint left, jint top)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QNativeAndroidScrollView *view = reinterpret_cast<QNativeAndroidScrollView *>(instance);
    if (view) {
        QMetaObject::invokeMethod(view, "_q_updateScrollX", Qt::QueuedConnection, Q_ARG(int, left));
        QMetaObject::invokeMethod(view, "_q_updateScrollY", Qt::QueuedConnection, Q_ARG(int, top));
    }
}

static void registerNativeScrollViewMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onScrollChanged", "(JII)V", reinterpret_cast<void *>(native_onScrollChanged)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QNativeAndroidScrollViewPrivate : public QNativeAndroidFrameLayoutPrivate
{
    Q_DECLARE_PUBLIC(QNativeAndroidScrollView)

public:
    bool _q_updateScrollX(int x);
    bool _q_updateScrollY(int y);

    QNativeAndroidOptional<int> scrollX;
    QNativeAndroidOptional<int> scrollY;
};

bool QNativeAndroidScrollViewPrivate::_q_updateScrollX(int x)
{
    Q_Q(QNativeAndroidScrollView);
    if (!scrollX.isNull() && scrollX == x)
        return false;

    scrollX = x;
    emit q->scrollXChanged();
    return true;
}

bool QNativeAndroidScrollViewPrivate::_q_updateScrollY(int y)
{
    Q_Q(QNativeAndroidScrollView);
    if (!scrollY.isNull() && scrollY == y)
        return false;

    scrollY = y;
    emit q->scrollYChanged();
    return true;
}

QNativeAndroidScrollView::QNativeAndroidScrollView(QNativeAndroidContext *context)
    : QNativeAndroidFrameLayout(*(new QNativeAndroidScrollViewPrivate), context)
{
}

int QNativeAndroidScrollView::scrollX() const
{
    Q_D(const QNativeAndroidScrollView);
    if (d->scrollX.isNull())
        return 0;
    return d->scrollX;
}

void QNativeAndroidScrollView::setScrollX(int x)
{
    Q_D(QNativeAndroidScrollView);
    if (d->_q_updateScrollX(x))
        QtNativeAndroid::callIntMethod(instance(), "setScrollX", x);
}

int QNativeAndroidScrollView::scrollY() const
{
    Q_D(const QNativeAndroidScrollView);
    if (d->scrollY.isNull())
        return 0;
    return d->scrollY;
}

void QNativeAndroidScrollView::setScrollY(int y)
{
    Q_D(QNativeAndroidScrollView);
    if (d->_q_updateScrollY(y))
        QtNativeAndroid::callIntMethod(instance(), "setScrollY", y);
}

QAndroidJniObject QNativeAndroidScrollView::onCreate()
{
    return QAndroidJniObject("org/qtproject/qt5/android/bindings/widget/QtNativeScrollView",
                             "(Landroid/content/Context;J)V",
                             ctx().object(),
                             reinterpret_cast<jlong>(this));
}

void QNativeAndroidScrollView::onInflate(QAndroidJniObject &instance)
{
    QNativeAndroidFrameLayout::onInflate(instance);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeScrollViewMethods(instance.object());
        nativeMethodsRegistered = true;
    }
}

QT_END_NAMESPACE

#include "moc_qnativeandroidscrollview_p.cpp"
