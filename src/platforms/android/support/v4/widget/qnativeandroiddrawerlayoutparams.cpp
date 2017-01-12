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

#include "qnativeandroiddrawerlayoutparams_p.h"
#include "qnativeandroidmarginlayoutparams_p_p.h"
#include "qnativeandroiddrawerlayout_p.h"
#include "qnativeandroidview_p.h"

QT_BEGIN_NAMESPACE

class QNativeAndroidDrawerLayoutParamsPrivate : public QNativeAndroidMarginLayoutParamsPrivate
{
public:
    int gravity = 0;
};

QNativeAndroidDrawerLayoutParams::QNativeAndroidDrawerLayoutParams(QNativeAndroidView *view)
    : QNativeAndroidMarginLayoutParams(*(new QNativeAndroidDrawerLayoutParamsPrivate), view)
{
}

int QNativeAndroidDrawerLayoutParams::gravity() const
{
    Q_D(const QNativeAndroidDrawerLayoutParams);
    return d->gravity;
}

void QNativeAndroidDrawerLayoutParams::setGravity(int gravity)
{
    Q_D(QNativeAndroidDrawerLayoutParams);
    if (d->gravity == gravity)
        return;

    d->gravity = gravity;
    invalidate();
    emit gravityChanged();
}

QAndroidJniObject QNativeAndroidDrawerLayoutParams::onCreate()
{
    Q_D(QNativeAndroidDrawerLayoutParams);
    return QAndroidJniObject("android/support/v4/widget/DrawerLayout$LayoutParams",
                             "(III)V",
                             MATCH_PARENT, MATCH_PARENT, d->gravity);
}

void QNativeAndroidDrawerLayoutParams::onInflate(QAndroidJniObject &instance)
{
    Q_D(QNativeAndroidDrawerLayoutParams);
    QNativeAndroidMarginLayoutParams::onInflate(instance);

    instance.setField<int>("gravity", d->gravity);
}

QT_END_NAMESPACE
