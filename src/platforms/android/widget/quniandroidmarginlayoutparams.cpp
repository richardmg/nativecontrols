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

#include "quniandroidmarginlayoutparams_p.h"
#include "quniandroidmarginlayoutparams_p_p.h"
#include "quniandroidview_p.h"

QT_BEGIN_NAMESPACE

QUniAndroidMarginLayoutParams::QUniAndroidMarginLayoutParams(QUniAndroidView *view)
    : QUniAndroidLayoutParams(*(new QUniAndroidMarginLayoutParamsPrivate), view)
{
}

QUniAndroidMarginLayoutParams::QUniAndroidMarginLayoutParams(QUniAndroidMarginLayoutParamsPrivate &dd, QUniAndroidView *view)
    : QUniAndroidLayoutParams(dd, view)
{
}

int QUniAndroidMarginLayoutParams::margin() const
{
    Q_D(const QUniAndroidMarginLayoutParams);
    if (d->margin.isNull())
        return 0;
    return d->margin;
}

void QUniAndroidMarginLayoutParams::setMargin(int margin)
{
    Q_D(QUniAndroidMarginLayoutParams);
    if (!d->margin.isNull() && d->margin == margin)
        return;

    d->margin = margin;
    invalidate();
    emit marginChanged();
}

int QUniAndroidMarginLayoutParams::topMargin() const
{
    Q_D(const QUniAndroidMarginLayoutParams);
    if (d->topMargin.isNull())
        return margin();
    return d->topMargin;
}

void QUniAndroidMarginLayoutParams::setTopMargin(int margin)
{
    Q_D(QUniAndroidMarginLayoutParams);
    if (!d->topMargin.isNull() && d->topMargin == margin)
        return;

    d->topMargin = margin;
    invalidate();
    emit topMarginChanged();
}

int QUniAndroidMarginLayoutParams::leftMargin() const
{
    Q_D(const QUniAndroidMarginLayoutParams);
    if (d->leftMargin.isNull())
        return margin();
    return d->leftMargin;
}

void QUniAndroidMarginLayoutParams::setLeftMargin(int margin)
{
    Q_D(QUniAndroidMarginLayoutParams);
    if (!d->leftMargin.isNull() && d->leftMargin == margin)
        return;

    d->leftMargin = margin;
    invalidate();
    emit leftMarginChanged();
}

int QUniAndroidMarginLayoutParams::rightMargin() const
{
    Q_D(const QUniAndroidMarginLayoutParams);
    if (d->rightMargin.isNull())
        return margin();
    return d->rightMargin;
}

void QUniAndroidMarginLayoutParams::setRightMargin(int margin)
{
    Q_D(QUniAndroidMarginLayoutParams);
    if (!d->rightMargin.isNull() && d->rightMargin == margin)
        return;

    d->rightMargin = margin;
    invalidate();
    emit rightMarginChanged();
}

int QUniAndroidMarginLayoutParams::bottomMargin() const
{
    Q_D(const QUniAndroidMarginLayoutParams);
    if (d->bottomMargin.isNull())
        return margin();
    return d->bottomMargin;
}

void QUniAndroidMarginLayoutParams::setBottomMargin(int margin)
{
    Q_D(QUniAndroidMarginLayoutParams);
    if (!d->bottomMargin.isNull() && d->bottomMargin == margin)
        return;

    d->bottomMargin = margin;
    invalidate();
    emit bottomMarginChanged();
}

QAndroidJniObject QUniAndroidMarginLayoutParams::onCreate()
{
    return QAndroidJniObject("android/view/ViewGroup$MarginLayoutParams",
                             "(II)V",
                             MATCH_PARENT, MATCH_PARENT);
}

void QUniAndroidMarginLayoutParams::onInflate(QAndroidJniObject &instance)
{
    QUniAndroidLayoutParams::onInflate(instance);

    instance.callMethod<void>("setMargins",
                              "(IIII)V",
                              leftMargin(),
                              topMargin(),
                              rightMargin(),
                              bottomMargin());
}

QT_END_NAMESPACE
