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

#include "quniandroidpathinterpolator_p.h"
#include "quniandroidinterpolator_p_p.h"
#include "quniandroidoptional_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidPathInterpolatorPrivate : public QUniAndroidInterpolatorPrivate
{
public:
    QUniAndroidOptional<qreal> controlX;
    QUniAndroidOptional<qreal> controlY;
    QUniAndroidOptional<qreal> controlX2;
    QUniAndroidOptional<qreal> controlY2;
};

QUniAndroidPathInterpolator::QUniAndroidPathInterpolator(QObject *parent)
    : QUniAndroidInterpolator(*(new QUniAndroidPathInterpolatorPrivate), parent)
{
}

qreal QUniAndroidPathInterpolator::controlX() const
{
    Q_D(const QUniAndroidPathInterpolator);
    if (d->controlX.isNull())
        return 0.0;
    return d->controlX;
}

void QUniAndroidPathInterpolator::setControlX(qreal x)
{
    Q_D(QUniAndroidPathInterpolator);
    if (!d->controlX.isNull() && qFuzzyCompare(d->controlX, x))
        return;

    d->controlX = x;
    emit controlXChanged();
}

qreal QUniAndroidPathInterpolator::controlY() const
{
    Q_D(const QUniAndroidPathInterpolator);
    if (d->controlY.isNull())
        return 0.0;
    return d->controlY;
}

void QUniAndroidPathInterpolator::setControlY(qreal y)
{
    Q_D(QUniAndroidPathInterpolator);
    if (!d->controlY.isNull() && qFuzzyCompare(d->controlY, y))
        return;

    d->controlY = y;
    emit controlYChanged();
}

qreal QUniAndroidPathInterpolator::controlX2() const
{
    Q_D(const QUniAndroidPathInterpolator);
    if (d->controlX2.isNull())
        return 0.0;
    return d->controlX2;
}

void QUniAndroidPathInterpolator::setControlX2(qreal x)
{
    Q_D(QUniAndroidPathInterpolator);
    if (!d->controlX2.isNull() && qFuzzyCompare(d->controlX2, x))
        return;

    d->controlX2 = x;
    emit controlX2Changed();
}

qreal QUniAndroidPathInterpolator::controlY2() const
{
    Q_D(const QUniAndroidPathInterpolator);
    if (d->controlY2.isNull())
        return 0.0;
    return d->controlY2;
}

void QUniAndroidPathInterpolator::setControlY2(qreal y)
{
    Q_D(QUniAndroidPathInterpolator);
    if (!d->controlY2.isNull() && qFuzzyCompare(d->controlY2, y))
        return;

    d->controlY2 = y;
    emit controlY2Changed();
}

QAndroidJniObject QUniAndroidPathInterpolator::onCreate()
{
    Q_D(QUniAndroidPathInterpolator);
    if (!d->controlX.isNull() && !d->controlY.isNull() && !d->controlX2.isNull() && !d->controlY2.isNull())
        return QAndroidJniObject("android/view/animation/PathInterpolator",
                                 "(FFFF)V",
                                 d->controlX,
                                 d->controlY,
                                 d->controlX2,
                                 d->controlY2);

    if (!d->controlX.isNull() && !d->controlY.isNull())
        return QAndroidJniObject("android/view/animation/PathInterpolator",
                                 "(FF)V",
                                 d->controlX,
                                 d->controlY);

    return QAndroidJniObject();
}

QT_END_NAMESPACE
