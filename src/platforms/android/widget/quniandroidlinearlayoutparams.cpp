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

#include "quniandroidlinearlayoutparams_p.h"
#include "quniandroidmarginlayoutparams_p_p.h"
#include "quniandroidview_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidLinearLayoutParamsPrivate : public QUniAndroidMarginLayoutParamsPrivate
{
public:
    QUniAndroidOptional<int> gravity;
    QUniAndroidOptional<qreal> weight;
};

QUniAndroidLinearLayoutParams::QUniAndroidLinearLayoutParams(QUniAndroidView *view)
    : QUniAndroidMarginLayoutParams(*(new QUniAndroidLinearLayoutParamsPrivate), view)
{
}

int QUniAndroidLinearLayoutParams::gravity() const
{
    Q_D(const QUniAndroidLinearLayoutParams);
    if (d->gravity.isNull())
        return 0; // TODO
    return d->gravity;
}

void QUniAndroidLinearLayoutParams::setGravity(int value)
{
    Q_D(QUniAndroidLinearLayoutParams);
    if (value == gravity())
        return;

    d->gravity = value;
    invalidate();
    emit gravityChanged();
}

qreal QUniAndroidLinearLayoutParams::weight() const
{
    Q_D(const QUniAndroidLinearLayoutParams);
    if (d->weight.isNull())
        return 0.0; // TODO
    return d->weight;
}

void QUniAndroidLinearLayoutParams::setWeight(qreal value)
{
    Q_D(QUniAndroidLinearLayoutParams);
    if (value == weight())
        return;

    d->weight = value;
    invalidate();
    emit weightChanged();
}

QAndroidJniObject QUniAndroidLinearLayoutParams::onCreate()
{
    return QAndroidJniObject("android/widget/LinearLayout$LayoutParams",
                             "(II)V",
                             MATCH_PARENT, MATCH_PARENT);
}

void QUniAndroidLinearLayoutParams::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidLinearLayoutParams);
    QUniAndroidMarginLayoutParams::onInflate(instance);

    if (!d->gravity.isNull())
        instance.setField<jint>("gravity", d->gravity);
    if (!d->weight.isNull())
        instance.setField<jfloat>("weight", d->weight);
}

QT_END_NAMESPACE
