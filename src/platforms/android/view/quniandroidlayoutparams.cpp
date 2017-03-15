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

#include "quniandroidlayoutparams_p.h"
#include "quniandroidlayoutparams_p_p.h"
#include "qtuniandroidfunctions_p.h"
#include "quniandroidview_p.h"

QT_BEGIN_NAMESPACE

QUniAndroidLayoutParams::QUniAndroidLayoutParams(QUniAndroidView *view)
    : QUniAndroidObject(*(new QUniAndroidLayoutParamsPrivate), view)
{
    Q_D(QUniAndroidLayoutParams);
    d->view = view;
    view->setLayoutParams(this);
}

QUniAndroidLayoutParams::QUniAndroidLayoutParams(QUniAndroidLayoutParamsPrivate &dd, QUniAndroidView *view)
    : QUniAndroidObject(dd, view)
{
    Q_D(QUniAndroidLayoutParams);
    d->view = view;
    view->setLayoutParams(this);
}

QUniAndroidLayoutParams *QUniAndroidLayoutParams::qmlAttachedProperties(QObject *object)
{
    QUniAndroidView *view = qobject_cast<QUniAndroidView*>(object);
    if (view)
        return new QUniAndroidLayoutParams(view);
    return 0;
}

int QUniAndroidLayoutParams::width() const
{
    Q_D(const QUniAndroidLayoutParams);
    if (d->width.isNull())
        return MATCH_PARENT;
    return d->width;
}

void QUniAndroidLayoutParams::setWidth(int value)
{
    Q_D(QUniAndroidLayoutParams);
    if (value == width())
        return;

    d->width = value;
    invalidate();
    emit widthChanged();
}

int QUniAndroidLayoutParams::height() const
{
    Q_D(const QUniAndroidLayoutParams);
    if (d->height.isNull())
        return MATCH_PARENT;
    return d->height;
}

void QUniAndroidLayoutParams::setHeight(int value)
{
    Q_D(QUniAndroidLayoutParams);
    if (value == height())
        return;

    d->height = value;
    invalidate();
    emit heightChanged();
}

void QUniAndroidLayoutParams::invalidate()
{
    Q_D(QUniAndroidLayoutParams);
    if (!d->dirty && isValid()) {
        d->dirty = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::LayoutRequest));
    }
}

QAndroidJniObject QUniAndroidLayoutParams::onCreate()
{
    return QAndroidJniObject("android/view/ViewGroup$LayoutParams",
                             "(II)V",
                             MATCH_PARENT, MATCH_PARENT);
}

void QUniAndroidLayoutParams::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidLayoutParams);
    if (!d->width.isNull())
        instance.setField<int>("width", d->width);
    if (!d->height.isNull())
        instance.setField<int>("height", d->height);
}

bool QUniAndroidLayoutParams::event(QEvent *event)
{
    Q_D(QUniAndroidLayoutParams);
    if (event->type() == QEvent::LayoutRequest) {
        if (d->dirty && isValid()) {
            construct();
            d->dirty = false;
        }
    }
    return QUniAndroidObject::event(event);
}

QT_END_NAMESPACE
