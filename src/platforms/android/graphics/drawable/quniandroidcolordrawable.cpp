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

#include "quniandroidcolordrawable_p.h"
#include "quniandroiddrawable_p_p.h"
#include "qtuniandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidColorDrawablePrivate : public QUniAndroidDrawablePrivate
{
public:
    int color = 0;
};

QUniAndroidColorDrawable::QUniAndroidColorDrawable(QObject *parent)
    : QUniAndroidDrawable(*(new QUniAndroidColorDrawablePrivate), parent)
{
}

QUniAndroidColorDrawable::QUniAndroidColorDrawable(int color, QObject *parent)
    : QUniAndroidDrawable(*(new QUniAndroidColorDrawablePrivate), parent)
{
    Q_D(QUniAndroidColorDrawable);
    d->color = color;
}

int QUniAndroidColorDrawable::color() const
{
    Q_D(const QUniAndroidColorDrawable);
    return d->color;
}

void QUniAndroidColorDrawable::setColor(int color)
{
    Q_D(QUniAndroidColorDrawable);
    if (d->color == color)
        return;

    d->color = color;
    QtUniAndroid::callIntMethod(instance(), "setColor", color);
    emit colorChanged();
}

QAndroidJniObject QUniAndroidColorDrawable::onCreate()
{
    return QAndroidJniObject("android/graphics/drawable/ColorDrawable");
}

void QUniAndroidColorDrawable::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidColorDrawable);
    QUniAndroidDrawable::onInflate(instance);

    instance.callMethod<void>("setColor", "(I)V", d->color);
}

QT_END_NAMESPACE
