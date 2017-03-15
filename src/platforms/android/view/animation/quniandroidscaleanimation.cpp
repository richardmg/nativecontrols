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

#include "quniandroidscaleanimation_p.h"
#include "quniandroidanimation_p_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidScaleAnimationPrivate : public QUniAndroidAnimationPrivate
{
public:
    qreal fromX = 0.0;
    qreal fromY = 0.0;
    qreal toX = 0.0;
    qreal toY = 0.0;
    qreal pivotX = 0.0;
    qreal pivotY = 0.0;
    QUniAndroidScaleAnimation::Relation pivotXType = QUniAndroidScaleAnimation::ABSOLUTE;
    QUniAndroidScaleAnimation::Relation pivotYType = QUniAndroidScaleAnimation::ABSOLUTE;
};

QUniAndroidScaleAnimation::QUniAndroidScaleAnimation(QObject *parent)
    : QUniAndroidAnimation(*(new QUniAndroidScaleAnimationPrivate), parent)
{
}

qreal QUniAndroidScaleAnimation::fromXScale() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->fromX;
}

void QUniAndroidScaleAnimation::setFromXScale(qreal x)
{
    Q_D(QUniAndroidScaleAnimation);
    if (qFuzzyCompare(d->fromX, x))
        return;

    d->fromX = x;
    emit fromXScaleChanged();
}

qreal QUniAndroidScaleAnimation::fromYScale() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->fromY;
}

void QUniAndroidScaleAnimation::setFromYScale(qreal y)
{
    Q_D(QUniAndroidScaleAnimation);
    if (qFuzzyCompare(d->fromY, y))
        return;

    d->fromY = y;
    emit fromYScaleChanged();
}

qreal QUniAndroidScaleAnimation::toXScale() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->toX;
}

void QUniAndroidScaleAnimation::setToXScale(qreal x)
{
    Q_D(QUniAndroidScaleAnimation);
    if (qFuzzyCompare(d->toX, x))
        return;

    d->toX = x;
    emit toXScaleChanged();
}

qreal QUniAndroidScaleAnimation::toYScale() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->toY;
}

void QUniAndroidScaleAnimation::setToYScale(qreal y)
{
    Q_D(QUniAndroidScaleAnimation);
    if (qFuzzyCompare(d->toY, y))
        return;

    d->toY = y;
    emit toYScaleChanged();
}

qreal QUniAndroidScaleAnimation::pivotX() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->pivotX;
}

void QUniAndroidScaleAnimation::setPivotX(qreal pivotX)
{
    Q_D(QUniAndroidScaleAnimation);
    if (qFuzzyCompare(d->pivotX, pivotX))
        return;

    d->pivotX = pivotX;
    emit pivotXChanged();
}

qreal QUniAndroidScaleAnimation::pivotY() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->pivotY;
}

void QUniAndroidScaleAnimation::setPivotY(qreal pivotY)
{
    Q_D(QUniAndroidScaleAnimation);
    if (qFuzzyCompare(d->pivotY, pivotY))
        return;

    d->pivotY = pivotY;
    emit pivotYChanged();
}

QUniAndroidAnimation::Relation QUniAndroidScaleAnimation::pivotXType() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->pivotXType;
}

void QUniAndroidScaleAnimation::setPivotXType(Relation type)
{
    Q_D(QUniAndroidScaleAnimation);
    if (d->pivotXType == type)
        return;

    d->pivotXType = type;
    emit pivotXTypeChanged();
}

QUniAndroidAnimation::Relation QUniAndroidScaleAnimation::pivotYType() const
{
    Q_D(const QUniAndroidScaleAnimation);
    return d->pivotYType;
}

void QUniAndroidScaleAnimation::setPivotYType(Relation type)
{
    Q_D(QUniAndroidScaleAnimation);
    if (d->pivotYType == type)
        return;

    d->pivotYType = type;
    emit pivotYTypeChanged();
}

QAndroidJniObject QUniAndroidScaleAnimation::onCreate()
{
    Q_D(QUniAndroidScaleAnimation);
    return QAndroidJniObject("android/view/animation/ScaleAnimation",
                             "(FFFFIFIF)V",
                             d->fromX, d->toX, d->fromY, d->toY,
                             d->pivotXType, d->pivotX, d->pivotYType, d->pivotY);
}

QT_END_NAMESPACE
