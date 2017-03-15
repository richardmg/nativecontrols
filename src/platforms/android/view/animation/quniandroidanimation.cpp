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

#include "quniandroidanimation_p.h"
#include "quniandroidanimation_p_p.h"
#include "qtuniandroidfunctions_p.h"
#include "quniandroidinterpolator_p.h"

QT_BEGIN_NAMESPACE

void QUniAndroidAnimationPrivate::updateInterpolator()
{
    Q_Q(QUniAndroidAnimation);
    if (!q->isValid() || !interpolator || !interpolator->isValid())
        return;

    QAndroidJniObject animation = q->instance();
    QAndroidJniObject ipolator = interpolator->instance();
    QtUniAndroid::callFunction([=]() {
        animation.callMethod<void>("setInterpolator", "(Landroid/view/animation/Interpolator;)V", ipolator.object());
    });
}

QUniAndroidAnimation::QUniAndroidAnimation(QObject *parent)
    : QUniAndroidContextual(*(new QUniAndroidAnimationPrivate), parent)
{
}

QUniAndroidAnimation::QUniAndroidAnimation(QUniAndroidAnimationPrivate &dd, QObject *parent)
    : QUniAndroidContextual(dd, parent)
{
}

int QUniAndroidAnimation::resource() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->resource.isNull())
        return 0;
    return d->resource;
}

void QUniAndroidAnimation::setResource(int resource)
{
    Q_D(QUniAndroidAnimation);
    if (!d->resource.isNull() && d->resource == resource)
        return;

    d->resource = resource;
    emit resourceChanged();
}

int QUniAndroidAnimation::duration() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->duration.isNull())
        return 0;
    return d->duration;
}

void QUniAndroidAnimation::setDuration(int duration)
{
    Q_D(QUniAndroidAnimation);
    if (!d->duration.isNull() && d->duration == duration)
        return;

    d->duration = duration;
    QtUniAndroid::callIntMethod(instance(), "setDuration", duration);
    emit durationChanged();
}

bool QUniAndroidAnimation::fillAfter() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->fillAfter.isNull())
        return false;
    return d->fillAfter;
}

void QUniAndroidAnimation::setFillAfter(bool fill)
{
    Q_D(QUniAndroidAnimation);
    if (!d->fillAfter.isNull() && d->fillAfter == fill)
        return;

    d->fillAfter = fill;
    QtUniAndroid::callBoolMethod(instance(), "setFillAfter", fill);
    emit fillAfterChanged();
}

bool QUniAndroidAnimation::fillBefore() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->fillBefore.isNull())
        return true;
    return d->fillBefore;
}

void QUniAndroidAnimation::setFillBefore(bool fill)
{
    Q_D(QUniAndroidAnimation);
    if (!d->fillBefore.isNull() && d->fillBefore == fill)
        return;

    d->fillBefore = fill;
    QtUniAndroid::callBoolMethod(instance(), "setFillBefore", fill);
    emit fillBeforeChanged();
}

bool QUniAndroidAnimation::fillEnabled() const
{
    Q_D(const QUniAndroidAnimation);
    if (!d->fillEnabled.isNull())
        return false;
    return d->fillEnabled;
}

void QUniAndroidAnimation::setFillEnabled(bool fill)
{
    Q_D(QUniAndroidAnimation);
    if (!d->fillEnabled.isNull() && d->fillEnabled != fill)
        return;

    d->fillEnabled = fill;
    QtUniAndroid::callBoolMethod(instance(), "setFillEnabled", fill);
    emit fillEnabledChanged();
}

QUniAndroidInterpolator *QUniAndroidAnimation::interpolator() const
{
    Q_D(const QUniAndroidAnimation);
    return d->interpolator;
}

void QUniAndroidAnimation::setInterpolator(QUniAndroidInterpolator *interpolator)
{
    Q_D(QUniAndroidAnimation);
    if (d->interpolator == interpolator)
        return;

    if (d->interpolator) {
        QObjectPrivate::disconnect(d->interpolator, &QUniAndroidObject::instanceChanged, d, &QUniAndroidAnimationPrivate::updateInterpolator);
        d->interpolator->destruct();
    }
    d->interpolator = interpolator;
    if (d->interpolator) {
        QObjectPrivate::connect(d->interpolator, &QUniAndroidObject::instanceChanged, d, &QUniAndroidAnimationPrivate::updateInterpolator);
        if (isValid())
            d->interpolator->construct();
    }
}

int QUniAndroidAnimation::repeatCount() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->repeatCount.isNull())
        return 0;
    return d->repeatCount;
}

void QUniAndroidAnimation::setRepeatCount(int count)
{
    Q_D(QUniAndroidAnimation);
    if (!d->repeatCount.isNull() && d->repeatCount == count)
        return;

    d->repeatCount = count;
    QtUniAndroid::callIntMethod(instance(), "setRepeatCount", count);
    emit repeatCountChanged();
}

QUniAndroidAnimation::RepeatMode QUniAndroidAnimation::repeatMode() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->repeatMode.isNull())
        return RESTART;
    return d->repeatMode;
}

void QUniAndroidAnimation::setRepeatMode(RepeatMode mode)
{
    Q_D(QUniAndroidAnimation);
    if (!d->repeatMode.isNull() && d->repeatMode == mode)
        return;

    d->repeatMode = mode;
    QtUniAndroid::callIntMethod(instance(), "setRepeatMode", mode);
    emit repeatModeChanged();
}

int QUniAndroidAnimation::startOffset() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->startOffset.isNull())
        return 0;
    return d->startOffset;
}

void QUniAndroidAnimation::setStartOffset(int offset)
{
    Q_D(QUniAndroidAnimation);
    if (!d->startOffset.isNull() && d->startOffset == offset)
        return;

    d->startOffset = offset;
    QtUniAndroid::callIntMethod(instance(), "setStartOffset", offset);
    emit startOffsetChanged();
}

QUniAndroidAnimation::ZAdjustment QUniAndroidAnimation::zAdjustment() const
{
    Q_D(const QUniAndroidAnimation);
    if (d->zAdjustment.isNull())
        return ZORDER_NORMAL;
    return d->zAdjustment;
}

void QUniAndroidAnimation::setZAdjustment(ZAdjustment adjustment)
{
    Q_D(QUniAndroidAnimation);
    if (!d->zAdjustment.isNull() && d->zAdjustment == adjustment)
        return;

    d->zAdjustment = adjustment;
    QtUniAndroid::callIntMethod(instance(), "setZAdjustment", adjustment);
    emit zAdjustmentChanged();
}

void QUniAndroidAnimation::cancel()
{
    QtUniAndroid::callVoidMethod(instance(), "cancel");
}

void QUniAndroidAnimation::start()
{
    QtUniAndroid::callVoidMethod(instance(), "start");
}

void QUniAndroidAnimation::startNow()
{
    QtUniAndroid::callVoidMethod(instance(), "startNow");
}

QAndroidJniObject QUniAndroidAnimation::onCreate()
{
    Q_D(QUniAndroidAnimation);
    if (d->resource.isNull())
        return QAndroidJniObject("android/view/animation/Animation");

    return QAndroidJniObject::callStaticObjectMethod("android/view/animation/AnimationUtils",
                                                     "loadAnimation",
                                                     "(Landroid/content/Context;I)Landroid/view/animation/Animation;",
                                                     ctx().object(),
                                                     d->resource);
}

void QUniAndroidAnimation::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidAnimation);
    QUniAndroidContextual::onInflate(instance);

    if (!d->resource.isNull())
        return;

    if (!d->duration.isNull())
        instance.callMethod<void>("setDuration", "(J)V", static_cast<jlong>(d->duration));
    if (!d->fillAfter.isNull())
        instance.callMethod<void>("setFillAfter", "(Z)V", d->fillAfter);
    if (!d->fillBefore.isNull())
        instance.callMethod<void>("setFillBefore", "(Z)V", d->fillBefore);
    if (!d->fillEnabled.isNull())
        instance.callMethod<void>("setFillEnabled", "(Z)V", d->fillEnabled);
    if (!d->repeatCount.isNull())
        instance.callMethod<void>("setRepeatCount", "(I)V", d->repeatCount);
    if (!d->repeatMode.isNull())
        instance.callMethod<void>("setRepeatMode", "(I)V", d->repeatMode);
    if (!d->startOffset.isNull())
        instance.callMethod<void>("setStartOffset", "(J)V", static_cast<jlong>(d->startOffset));
    if (!d->zAdjustment.isNull())
        instance.callMethod<void>("setZAdjustment", "(I)V", d->zAdjustment);
}

void QUniAndroidAnimation::objectChange(ObjectChange change)
{
    Q_D(QUniAndroidAnimation);
    if (change == InstanceChange)
        d->updateInterpolator();
}

QT_END_NAMESPACE
