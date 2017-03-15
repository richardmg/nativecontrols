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

#include "quniandroidtranslateanimation_p.h"
#include "quniandroidanimation_p_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidTranslateAnimationPrivate : public QUniAndroidAnimationPrivate
{
public:
    qreal fromX = 0.0;
    qreal fromY = 0.0;
    qreal toX = 0.0;
    qreal toY = 0.0;
    QUniAndroidTranslateAnimation::Relation fromXType = QUniAndroidTranslateAnimation::ABSOLUTE;
    QUniAndroidTranslateAnimation::Relation fromYType = QUniAndroidTranslateAnimation::ABSOLUTE;
    QUniAndroidTranslateAnimation::Relation toXType = QUniAndroidTranslateAnimation::ABSOLUTE;
    QUniAndroidTranslateAnimation::Relation toYType = QUniAndroidTranslateAnimation::ABSOLUTE;
};

QUniAndroidTranslateAnimation::QUniAndroidTranslateAnimation(QObject *parent)
    : QUniAndroidAnimation(*(new QUniAndroidTranslateAnimationPrivate), parent)
{
}

qreal QUniAndroidTranslateAnimation::fromX() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->fromX;
}

void QUniAndroidTranslateAnimation::setFromX(qreal x)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (qFuzzyCompare(d->fromX, x))
        return;

    d->fromX = x;
    emit fromXChanged();
}

qreal QUniAndroidTranslateAnimation::fromY() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->fromY;
}

void QUniAndroidTranslateAnimation::setFromY(qreal y)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (qFuzzyCompare(d->fromY, y))
        return;

    d->fromY = y;
    emit fromYChanged();
}

qreal QUniAndroidTranslateAnimation::toX() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->toX;
}

void QUniAndroidTranslateAnimation::setToX(qreal x)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (qFuzzyCompare(d->toX, x))
        return;

    d->toX = x;
    emit toXChanged();
}

qreal QUniAndroidTranslateAnimation::toY() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->toY;
}

void QUniAndroidTranslateAnimation::setToY(qreal y)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (qFuzzyCompare(d->toY, y))
        return;

    d->toY = y;
    emit toYChanged();
}

QUniAndroidAnimation::Relation QUniAndroidTranslateAnimation::fromXType() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->fromXType;
}

void QUniAndroidTranslateAnimation::setFromXType(Relation type)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (d->fromXType == type)
        return;

    d->fromXType = type;
    emit fromXTypeChanged();
}

QUniAndroidAnimation::Relation QUniAndroidTranslateAnimation::fromYType() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->fromYType;
}

void QUniAndroidTranslateAnimation::setFromYType(Relation type)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (d->fromYType == type)
        return;

    d->fromYType = type;
    emit fromYTypeChanged();
}

QUniAndroidAnimation::Relation QUniAndroidTranslateAnimation::toXType() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->toXType;
}

void QUniAndroidTranslateAnimation::setToXType(Relation type)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (d->toXType == type)
        return;

    d->toXType = type;
    emit toXTypeChanged();
}

QUniAndroidAnimation::Relation QUniAndroidTranslateAnimation::toYType() const
{
    Q_D(const QUniAndroidTranslateAnimation);
    return d->toYType;
}

void QUniAndroidTranslateAnimation::setToYType(Relation type)
{
    Q_D(QUniAndroidTranslateAnimation);
    if (d->toYType == type)
        return;

    d->toYType = type;
    emit toYTypeChanged();
}

QAndroidJniObject QUniAndroidTranslateAnimation::onCreate()
{
    Q_D(QUniAndroidTranslateAnimation);
    return QAndroidJniObject("android/view/animation/TranslateAnimation",
                             "(IFIFIFIF)V",
                             d->fromXType, d->fromX, d->toXType, d->toX,
                             d->fromYType, d->fromY, d->toYType, d->toY);
}

QT_END_NAMESPACE
