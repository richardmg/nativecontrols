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

#include "quniandroidrotateanimation_p.h"
#include "quniandroidanimation_p_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidRotateAnimationPrivate : public QUniAndroidAnimationPrivate
{
public:
    qreal from = 0.0;
    qreal to = 0.0;
    qreal pivotX = 0.0;
    qreal pivotY = 0.0;
    QUniAndroidRotateAnimation::Relation pivotXType = QUniAndroidRotateAnimation::ABSOLUTE;
    QUniAndroidRotateAnimation::Relation pivotYType = QUniAndroidRotateAnimation::ABSOLUTE;
};

QUniAndroidRotateAnimation::QUniAndroidRotateAnimation(QObject *parent)
    : QUniAndroidAnimation(*(new QUniAndroidRotateAnimationPrivate), parent)
{
}

qreal QUniAndroidRotateAnimation::fromDegrees() const
{
    Q_D(const QUniAndroidRotateAnimation);
    return d->from;
}

void QUniAndroidRotateAnimation::setFromDegrees(qreal degrees)
{
    Q_D(QUniAndroidRotateAnimation);
    if (qFuzzyCompare(d->from, degrees))
        return;

    d->from = degrees;
    emit fromDegreesChanged();
}

qreal QUniAndroidRotateAnimation::toDegrees() const
{
    Q_D(const QUniAndroidRotateAnimation);
    return d->to;
}

void QUniAndroidRotateAnimation::setToDegrees(qreal degrees)
{
    Q_D(QUniAndroidRotateAnimation);
    if (qFuzzyCompare(d->to, degrees))
        return;

    d->to = degrees;
    emit toDegreesChanged();
}

qreal QUniAndroidRotateAnimation::pivotX() const
{
    Q_D(const QUniAndroidRotateAnimation);
    return d->pivotX;
}

void QUniAndroidRotateAnimation::setPivotX(qreal pivotX)
{
    Q_D(QUniAndroidRotateAnimation);
    if (qFuzzyCompare(d->pivotX, pivotX))
        return;

    d->pivotX = pivotX;
    emit pivotXChanged();
}

qreal QUniAndroidRotateAnimation::pivotY() const
{
    Q_D(const QUniAndroidRotateAnimation);
    return d->pivotY;
}

void QUniAndroidRotateAnimation::setPivotY(qreal pivotY)
{
    Q_D(QUniAndroidRotateAnimation);
    if (qFuzzyCompare(d->pivotY, pivotY))
        return;

    d->pivotY = pivotY;
    emit pivotYChanged();
}

QUniAndroidRotateAnimation::Relation QUniAndroidRotateAnimation::pivotXType() const
{
    Q_D(const QUniAndroidRotateAnimation);
    return d->pivotXType;
}

void QUniAndroidRotateAnimation::setPivotXType(Relation type)
{
    Q_D(QUniAndroidRotateAnimation);
    if (d->pivotXType == type)
        return;

    d->pivotXType = type;
    emit pivotXTypeChanged();
}

QUniAndroidRotateAnimation::Relation QUniAndroidRotateAnimation::pivotYType() const
{
    Q_D(const QUniAndroidRotateAnimation);
    return d->pivotYType;
}

void QUniAndroidRotateAnimation::setPivotYType(Relation type)
{
    Q_D(QUniAndroidRotateAnimation);
    if (d->pivotYType == type)
        return;

    d->pivotYType = type;
    emit pivotYTypeChanged();
}

QAndroidJniObject QUniAndroidRotateAnimation::onCreate()
{
    Q_D(QUniAndroidRotateAnimation);
    return QAndroidJniObject("android/view/animation/RotateAnimation",
                             "(FFIFIF)V",
                             d->from, d->to,
                             d->pivotXType, d->pivotX, d->pivotYType, d->pivotY);
}

QT_END_NAMESPACE
