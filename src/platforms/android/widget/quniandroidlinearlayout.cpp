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

#include "quniandroidlinearlayout_p.h"
#include "quniandroidlinearlayout_p_p.h"

QT_BEGIN_NAMESPACE

QUniAndroidLinearLayout::QUniAndroidLinearLayout(QUniAndroidContext *context)
    : QUniAndroidViewGroup(*(new QUniAndroidLinearLayoutPrivate), context)
{
}

QUniAndroidLinearLayout::QUniAndroidLinearLayout(QUniAndroidLinearLayoutPrivate &dd, QUniAndroidContext *context)
    : QUniAndroidViewGroup(dd, context)
{
}

QUniAndroidLinearLayoutParams *QUniAndroidLinearLayout::qmlAttachedProperties(QObject *object)
{
    QUniAndroidView *view = qobject_cast<QUniAndroidView*>(object);
    if (view)
        return new QUniAndroidLinearLayoutParams(view);
    return 0;
}

bool QUniAndroidLinearLayout::isBaselineAligned() const
{
    Q_D(const QUniAndroidLinearLayout);
    if (d->baselineAligned.isNull())
        return true;
    return d->baselineAligned;
}

void QUniAndroidLinearLayout::setBaselineAligned(bool aligned)
{
    Q_D(QUniAndroidLinearLayout);
    if (aligned == isBaselineAligned())
        return;

    d->baselineAligned = aligned;
//    if (isValid())
//        jniObject().callMethod<void>("setBaselineAligned", "(Z)V", aligned);
    emit baselineAlignedChanged();
}

int QUniAndroidLinearLayout::baselineAlignedChildIndex() const
{
    Q_D(const QUniAndroidLinearLayout);
    if (d->baselineAlignedChildIndex.isNull())
        return -1;
    return d->baselineAlignedChildIndex;
}

void QUniAndroidLinearLayout::setBaselineAlignedChildIndex(int index)
{
    Q_D(QUniAndroidLinearLayout);
    if (index == baselineAlignedChildIndex())
        return;

    d->baselineAlignedChildIndex = index;
//    if (isValid())
//        jniObject().callMethod<void>("setBaselineAlignedChildIndex", "(I)V", index);
    emit baselineAlignedChildIndexChanged();
}

bool QUniAndroidLinearLayout::isMeasureWithLargestChildEnabled() const
{
    Q_D(const QUniAndroidLinearLayout);
    if (d->measureWithLargestChild.isNull())
        return false;
    return d->measureWithLargestChild;
}

void QUniAndroidLinearLayout::setMeasureWithLargestChildEnabled(bool enabled)
{
    Q_D(QUniAndroidLinearLayout);
    if (enabled == isMeasureWithLargestChildEnabled())
        return;

    d->measureWithLargestChild = enabled;
//    if (isValid())
//        jniObject().callMethod<void>("setMeasureWithLargestChildEnabled", "(Z)V", enabled);
    emit measureWithLargestChildEnabledChanged();
}

QUniAndroidLinearLayout::Orientation QUniAndroidLinearLayout::orientation() const
{
    Q_D(const QUniAndroidLinearLayout);
    if (d->orientation.isNull())
        return HORIZONTAL;
    return d->orientation;
}

void QUniAndroidLinearLayout::setOrientation(Orientation value)
{
    Q_D(QUniAndroidLinearLayout);
    if (value == orientation())
        return;

    d->orientation = value;
//    if (isValid())
//        jniObject().callMethod<void>("setOrientation", "(I)V", value);
    emit orientationChanged();
}

qreal QUniAndroidLinearLayout::weightSum() const
{
    Q_D(const QUniAndroidLinearLayout);
    if (d->weightSum.isNull())
        return -1.0f;
    return d->weightSum;
}

void QUniAndroidLinearLayout::setWeightSum(qreal sum)
{
    Q_D(QUniAndroidLinearLayout);
    if (sum == weightSum())
        return;

    d->weightSum = sum;
//    if (isValid())
//        jniObject().callMethod<void>("setWeightSum", "(J)V", sum);
    emit weightSumChanged();
}

QAndroidJniObject QUniAndroidLinearLayout::onCreate()
{
    return QAndroidJniObject("android/widget/LinearLayout",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidLinearLayout::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidLinearLayout);
    if (!d->baselineAligned.isNull())
        instance.callMethod<void>("setBaselineAligned", "(Z)V", d->baselineAligned);
    if (!d->measureWithLargestChild.isNull())
        instance.callMethod<void>("setMeasureWithLargestChildEnabled", "(Z)V", d->measureWithLargestChild);
    if (!d->orientation.isNull())
        instance.callMethod<void>("setOrientation", "(I)V", d->orientation);
    if (!d->weightSum.isNull())
        instance.callMethod<void>("setWeightSum", "(J)V", d->weightSum);

    QUniAndroidViewGroup::onInflate(instance);

    if (!d->baselineAlignedChildIndex.isNull())
        instance.callMethod<void>("setBaselineAlignedChildIndex", "(I)V", d->baselineAlignedChildIndex);
}

QT_END_NAMESPACE
