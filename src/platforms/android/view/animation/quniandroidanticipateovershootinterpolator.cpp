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

#include "quniandroidanticipateovershootinterpolator_p.h"
#include "quniandroidinterpolator_p_p.h"
#include "quniandroidoptional_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidAnticipateOvershootInterpolatorPrivate : public QUniAndroidInterpolatorPrivate
{
public:
    QUniAndroidOptional<qreal> tension;
    QUniAndroidOptional<qreal> extraTension;
};

QUniAndroidAnticipateOvershootInterpolator::QUniAndroidAnticipateOvershootInterpolator(QObject *parent)
    : QUniAndroidInterpolator(*(new QUniAndroidAnticipateOvershootInterpolatorPrivate), parent)
{
}

qreal QUniAndroidAnticipateOvershootInterpolator::tension() const
{
    Q_D(const QUniAndroidAnticipateOvershootInterpolator);
    if (d->tension.isNull())
        return 1.0;
    return d->tension;
}

void QUniAndroidAnticipateOvershootInterpolator::setTension(qreal tension)
{
    Q_D(QUniAndroidAnticipateOvershootInterpolator);
    if (!d->tension.isNull() && qFuzzyCompare(d->tension, tension))
        return;

    d->tension = tension;
    emit tensionChanged();
}

qreal QUniAndroidAnticipateOvershootInterpolator::extraTension() const
{
    Q_D(const QUniAndroidAnticipateOvershootInterpolator);
    if (d->extraTension.isNull())
        return 1.0;
    return d->extraTension;
}

void QUniAndroidAnticipateOvershootInterpolator::setExtraTension(qreal tension)
{
    Q_D(QUniAndroidAnticipateOvershootInterpolator);
    if (!d->extraTension.isNull() && qFuzzyCompare(d->extraTension, tension))
        return;

    d->extraTension = tension;
    emit extraTensionChanged();
}

QAndroidJniObject QUniAndroidAnticipateOvershootInterpolator::onCreate()
{
    Q_D(QUniAndroidAnticipateOvershootInterpolator);
    if (d->tension.isNull() && d->extraTension.isNull())
        return QAndroidJniObject("android/view/animation/AnticipateOvershootInterpolator");

    if (!d->tension.isNull())
        return QAndroidJniObject("android/view/animation/AnticipateOvershootInterpolator",
                                 "(F)V",
                                 d->tension);

    return QAndroidJniObject("android/view/animation/AnticipateOvershootInterpolator",
                             "(FF)V",
                             d->tension,
                             d->extraTension);
}

QT_END_NAMESPACE
