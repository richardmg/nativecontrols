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

#include "quniandroidviewanimator_p.h"
#include "quniandroidviewanimator_p_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

QUniAndroidViewAnimator::QUniAndroidViewAnimator(QUniAndroidContext *context)
    : QUniAndroidFrameLayout(*(new QUniAndroidViewAnimatorPrivate), context)
{
}

int QUniAndroidViewAnimator::displayedChild() const
{
    Q_D(const QUniAndroidViewAnimator);
    if (d->displayedChild.isNull())
        return 0;
    return d->displayedChild;
}

void QUniAndroidViewAnimator::setDisplayedChild(int child)
{
    Q_D(QUniAndroidViewAnimator);
    if (child == displayedChild())
        return;

    d->displayedChild = child;
    QtNativeAndroid::callIntMethod(instance(), "setDisplayedChild", child);
    emit displayedChildChanged();
}

int QUniAndroidViewAnimator::inAnimation() const
{
    Q_D(const QUniAndroidViewAnimator);
    if (d->inAnimation.isNull())
        return -1;
    return d->inAnimation;
}

void QUniAndroidViewAnimator::setInAnimation(int animation)
{
    Q_D(QUniAndroidViewAnimator);
    if (animation == inAnimation())
        return;

    d->inAnimation = animation;
    if (instance().isValid()) {
        QtNativeAndroid::callFunction([=]() {
            instance().callMethod<void>("setInAnimation", "(Landroid/content/Context;I)V", ctx().object(), animation);
        });
    }
    QtNativeAndroid::callIntMethod(instance(), "setInAnimation", animation);
    emit inAnimationChanged();
}

int QUniAndroidViewAnimator::outAnimation() const
{
    Q_D(const QUniAndroidViewAnimator);
    if (d->outAnimation.isNull())
        return -1;
    return d->outAnimation;
}

void QUniAndroidViewAnimator::setOutAnimation(int animation)
{
    Q_D(QUniAndroidViewAnimator);
    if (animation == outAnimation())
        return;

    d->outAnimation = animation;
    if (instance().isValid()) {
        QtNativeAndroid::callFunction([=]() {
            instance().callMethod<void>("setOutAnimation", "(Landroid/content/Context;I)V", ctx().object(), animation);
        });
    }
    QtNativeAndroid::callIntMethod(instance(), "setInAnimation", animation);
    emit inAnimationChanged();
}

void QUniAndroidViewAnimator::showNext()
{
    QtNativeAndroid::callVoidMethod(instance(), "showNext");
}

void QUniAndroidViewAnimator::showPrevious()
{
    QtNativeAndroid::callVoidMethod(instance(), "showPrevious");
}

QAndroidJniObject QUniAndroidViewAnimator::onCreate()
{
    return QAndroidJniObject("android/widget/ViewAnimator",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidViewAnimator::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidViewAnimator);
    QUniAndroidFrameLayout::onInflate(instance);

    if (!d->displayedChild.isNull())
        instance.callMethod<void>("setDisplayedChild", "(I)V", d->displayedChild);
    if (!d->inAnimation.isNull())
        instance.callMethod<void>("setInAnimation", "(Landroid/content/Context;I)V", ctx().object(), d->inAnimation);
    if (!d->outAnimation.isNull())
        instance.callMethod<void>("setOutAnimation", "(Landroid/content/Context;I)V", ctx().object(), d->outAnimation);
}

QT_END_NAMESPACE
