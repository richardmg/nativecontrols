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

#include "quniandroidarrayadapter_p.h"
#include "quniandroidbaseadapter_p_p.h"
#include "quniandroidadapterview_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidArrayAdapterPrivate : public QUniAndroidBaseAdapterPrivate
{
public:
    int style = 17367043; // TODO: android.R.layout.simple_list_item_1
    QStringList array;
};

QUniAndroidArrayAdapter::QUniAndroidArrayAdapter(QObject *parent)
    : QUniAndroidBaseAdapter(*(new QUniAndroidArrayAdapterPrivate), parent)
{
}

int QUniAndroidArrayAdapter::style() const
{
    Q_D(const QUniAndroidArrayAdapter);
    return d->style;
}

void QUniAndroidArrayAdapter::setStyle(int style)
{
    Q_D(QUniAndroidArrayAdapter);
    if (d->style == style)
        return;

    d->style = style;
    emit styleChanged();
}

QStringList QUniAndroidArrayAdapter::array() const
{
    Q_D(const QUniAndroidArrayAdapter);
    return d->array;
}

void QUniAndroidArrayAdapter::setArray(const QStringList &array)
{
    Q_D(QUniAndroidArrayAdapter);
    if (d->array == array)
        return;

    d->array = array; // TODO: sync
    emit countChanged();
    emit arrayChanged();
}

int QUniAndroidArrayAdapter::count() const
{
    Q_D(const QUniAndroidArrayAdapter);
    return d->array.count();
}

QString QUniAndroidArrayAdapter::getItem(int position) const
{
    Q_D(const QUniAndroidArrayAdapter);
    return d->array.value(position);
}

void QUniAndroidArrayAdapter::clear()
{
    Q_D(QUniAndroidArrayAdapter);
    if (d->array.isEmpty())
        return;

    d->array.clear(); // TODO: sync
    emit countChanged();
    emit arrayChanged();
}

QAndroidJniObject QUniAndroidArrayAdapter::onCreate()
{
    Q_D(QUniAndroidArrayAdapter);
    return QAndroidJniObject("android/widget/ArrayAdapter",
                             "(Landroid/content/Context;I)V",
                             ctx().object(),
                             d->style);
}

void QUniAndroidArrayAdapter::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidArrayAdapter);
    QUniAndroidBaseAdapter::onInflate(instance);

    foreach (const QString &str, d->array)
        instance.callMethod<void>("add", "(Ljava/lang/Object;)V", QAndroidJniObject::fromString(str).object());
}

QT_END_NAMESPACE
