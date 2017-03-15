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

#include "quniandroidalphaanimation_p.h"
#include "quniandroidanimation_p_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidAlphaAnimationPrivate : public QUniAndroidAnimationPrivate
{
public:
    qreal fromAlpha = 0.0;
    qreal toAlpha = 0.0;
};

QUniAndroidAlphaAnimation::QUniAndroidAlphaAnimation(QObject *parent)
    : QUniAndroidAnimation(*(new QUniAndroidAlphaAnimationPrivate), parent)
{
}

qreal QUniAndroidAlphaAnimation::fromAlpha() const
{
    Q_D(const QUniAndroidAlphaAnimation);
    return d->fromAlpha;
}

void QUniAndroidAlphaAnimation::setFromAlpha(qreal alpha)
{
    Q_D(QUniAndroidAlphaAnimation);
    if (qFuzzyCompare(d->fromAlpha, alpha))
        return;

    d->fromAlpha = alpha;
    emit fromAlphaChanged();
}

qreal QUniAndroidAlphaAnimation::toAlpha() const
{
    Q_D(const QUniAndroidAlphaAnimation);
    return d->toAlpha;
}

void QUniAndroidAlphaAnimation::setToAlpha(qreal alpha)
{
    Q_D(QUniAndroidAlphaAnimation);
    if (qFuzzyCompare(d->toAlpha, alpha))
        return;

    d->toAlpha = alpha;
    emit toAlphaChanged();
}

QAndroidJniObject QUniAndroidAlphaAnimation::onCreate()
{
    Q_D(QUniAndroidAlphaAnimation);
    return QAndroidJniObject("android/view/animation/AlphaAnimation",
                             "(FF)V",
                             d->fromAlpha, d->toAlpha);
}

QT_END_NAMESPACE
