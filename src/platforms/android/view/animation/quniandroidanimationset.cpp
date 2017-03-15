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

#include "quniandroidanimationset_p.h"
#include "quniandroidanimation_p_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidAnimationSetPrivate : public QUniAndroidAnimationPrivate
{
public:
    bool shareInterpolator = false;
};

QUniAndroidAnimationSet::QUniAndroidAnimationSet(QObject *parent)
    : QUniAndroidAnimation(*(new QUniAndroidAnimationSetPrivate), parent)
{
}

bool QUniAndroidAnimationSet::shareInterpolator() const
{
    Q_D(const QUniAndroidAnimationSet);
    return d->shareInterpolator;
}

void QUniAndroidAnimationSet::setShareInterpolator(bool share)
{
    Q_D(QUniAndroidAnimationSet);
    if (d->shareInterpolator == share)
        return;

    d->shareInterpolator = share;
    emit shareInterpolatorChanged();
}

QAndroidJniObject QUniAndroidAnimationSet::onCreate()
{
    Q_D(QUniAndroidAnimationSet);
    return QAndroidJniObject("android/view/animation/AnimationSet",
                             "(Z)V",
                             d->shareInterpolator);
}

void QUniAndroidAnimationSet::onInflate(QAndroidJniObject &instance)
{
    QUniAndroidAnimation::onInflate(instance);

    foreach (QObject *object, children()) {
        QUniAndroidAnimation *child = qobject_cast<QUniAndroidAnimation *>(object);
        if (child) {
            QAndroidJniObject animation = child->instance();
            if (animation.isValid())
                instance.callMethod<void>("addAnimation", "(Landroid/view/animation/Animation;)V", animation.object());
        }
    }
}

QT_END_NAMESPACE
