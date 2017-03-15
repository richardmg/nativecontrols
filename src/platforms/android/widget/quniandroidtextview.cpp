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

#include "quniandroidtextview_p.h"
#include "quniandroidtextview_p_p.h"
#include "qtnativeandroidfunctions_p.h"
#include "quniandroidcolor_p.h"

QT_BEGIN_NAMESPACE

QUniAndroidTextView::QUniAndroidTextView(QUniAndroidContext *context)
    : QUniAndroidView(*(new QUniAndroidTextViewPrivate), context)
{
}

QUniAndroidTextView::QUniAndroidTextView(QUniAndroidTextViewPrivate &dd, QUniAndroidContext *context)
    : QUniAndroidView(dd, context)
{
}

QString QUniAndroidTextView::text() const
{
    Q_D(const QUniAndroidTextView);
    return d->text;
}

void QUniAndroidTextView::setText(const QString &text)
{
    Q_D(QUniAndroidTextView);
    if (d->text == text)
        return;

    d->text = text;
    QtUniAndroid::callTextMethod(instance(), "setText", text);
    emit textChanged();
}

int QUniAndroidTextView::textColor() const
{
    Q_D(const QUniAndroidTextView);
    if (d->textColor.isNull())
        return QUniAndroidColor::BLACK; // TODO
    return d->textColor;
}

void QUniAndroidTextView::setTextColor(int color)
{
    Q_D(QUniAndroidTextView);
    if (color == textColor())
        return;

    d->textColor = color;
    QtUniAndroid::callIntMethod(instance(), "setTextColor", color);
    emit textColorChanged();
}

qreal QUniAndroidTextView::textSize() const
{
    Q_D(const QUniAndroidTextView);
    if (d->textSize.isNull())
        return -1;
    return d->textSize;
}

void QUniAndroidTextView::setTextSize(qreal size)
{
    Q_D(QUniAndroidTextView);
    if (qFuzzyCompare(size, textSize()))
        return;

    d->textSize = size;
    QtUniAndroid::callRealMethod(instance(), "setTextSize", size);
    emit textSizeChanged();
}

QString QUniAndroidTextView::hint() const
{
    Q_D(const QUniAndroidTextView);
    return d->hint;
}

void QUniAndroidTextView::setHint(const QString &hint)
{
    Q_D(QUniAndroidTextView);
    if (d->hint == hint)
        return;

    d->hint = hint;
    QtUniAndroid::callTextMethod(instance(), "setHint", hint);
    emit hintChanged();
}

bool QUniAndroidTextView::isSingleLine() const
{
    Q_D(const QUniAndroidTextView);
    return d->singleLine;
}

void QUniAndroidTextView::setSingleLine(bool singleLine)
{
    Q_D(QUniAndroidTextView);
    if (d->singleLine == singleLine)
        return;

    d->singleLine = singleLine;
    QtUniAndroid::callBoolMethod(instance(), "setSingleLine", singleLine);
    emit singleLineChanged();
}

int QUniAndroidTextView::inputType() const
{
    Q_D(const QUniAndroidTextView);
    if (d->inputType.isNull())
        return 0; // TODO
    return d->inputType;
}

void QUniAndroidTextView::setInputType(int type)
{
    Q_D(QUniAndroidTextView);
    if (!d->inputType.isNull() && d->inputType == type)
        return;

    d->inputType = type;
    QtUniAndroid::callIntMethod(instance(), "setInputType", type);
    emit inputTypeChanged();
}

QAndroidJniObject QUniAndroidTextView::onCreate()
{
    return QAndroidJniObject("android/widget/TextView",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidTextView::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidTextView);
    QUniAndroidView::onInflate(instance);

    if (!d->text.isNull())
        instance.callMethod<void>("setText", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(d->text).object());
    if (!d->textColor.isNull())
        instance.callMethod<void>("setTextColor", "(I)V", d->textColor);
    if (!d->textSize.isNull())
        instance.callMethod<void>("setTextSize", "(F)V", d->textSize);
    if (!d->hint.isNull())
        instance.callMethod<void>("setHint", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(d->hint).object());
    if (d->singleLine)
        instance.callMethod<void>("setSingleLine");
    if (!d->inputType.isNull())
        instance.callMethod<void>("setInputType", "(I)V", d->inputType);
}

QT_END_NAMESPACE
