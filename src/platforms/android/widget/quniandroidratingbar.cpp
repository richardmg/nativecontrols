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

#include "quniandroidratingbar_p.h"
#include "quniandroidabsseekbar_p_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

static void native_onRatingChanged(JNIEnv *env, jobject object, jlong instance, jfloat rating, jboolean fromUser)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidRatingBar *bar = reinterpret_cast<QUniAndroidRatingBar *>(instance);
    if (bar && fromUser)
        QMetaObject::invokeMethod(bar, "updateRating", Qt::QueuedConnection, Q_ARG(qreal, rating));
}

static void registerNativeRatingBarMethods(jobject listener)
{
    JNINativeMethod methods[] {{"onRatingChanged", "(JFZ)V", reinterpret_cast<void *>(native_onRatingChanged)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(listener);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QUniAndroidRatingBarPrivate : public QUniAndroidAbsSeekBarPrivate
{
public:
    qreal rating = 0.0;
    QAndroidJniObject listener;
};

QUniAndroidRatingBar::QUniAndroidRatingBar(QUniAndroidContext *context)
    : QUniAndroidAbsSeekBar(*(new QUniAndroidRatingBarPrivate), context)
{
}

qreal QUniAndroidRatingBar::rating() const
{
    Q_D(const QUniAndroidRatingBar);
    return d->rating;
}

void QUniAndroidRatingBar::setRating(qreal rating)
{
    Q_D(QUniAndroidRatingBar);
    if (qFuzzyCompare(d->rating, rating))
        return;

    d->rating = rating;
    QtNativeAndroid::callRealMethod(instance(), "setRating", rating);
    emit ratingChanged();
}

QAndroidJniObject QUniAndroidRatingBar::onCreate()
{
    return QAndroidJniObject("android/widget/RatingBar",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidRatingBar::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidRatingBar);
    QUniAndroidAbsSeekBar::onInflate(instance);

    d->listener = QAndroidJniObject("org/qtproject/qt5/android/bindings/widget/QtNativeRatingBarListener",
                                   "(Landroid/widget/RatingBar;J)V",
                                   instance.object(),
                                   reinterpret_cast<jlong>(this));

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeRatingBarMethods(d->listener.object());
        nativeMethodsRegistered = true;
    }

    instance.callMethod<void>("setRating", "(F)V", d->rating);
}

QT_END_NAMESPACE
