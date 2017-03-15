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

#include "quniandroidalertdialog_p.h"
#include "quniandroiddialog_p_p.h"
#include "qtuniandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidAlertDialogPrivate : public QUniAndroidDialogPrivate
{
public:
    QString title;
    QString message;
};

QUniAndroidAlertDialog::QUniAndroidAlertDialog(QObject *parent)
    : QUniAndroidDialog(*(new QUniAndroidAlertDialogPrivate), parent)
{
}

QString QUniAndroidAlertDialog::title() const
{
    Q_D(const QUniAndroidAlertDialog);
    return d->title;
}

void QUniAndroidAlertDialog::setTitle(const QString &title)
{
    Q_D(QUniAndroidAlertDialog);
    if (d->title == title)
        return;

    d->title = title;
    QtUniAndroid::callTextMethod(instance(), "setTitle", title);
    emit titleChanged();
}

QString QUniAndroidAlertDialog::message() const
{
    Q_D(const QUniAndroidAlertDialog);
    return d->message;
}

void QUniAndroidAlertDialog::setMessage(const QString &message)
{
    Q_D(QUniAndroidAlertDialog);
    if (d->message != message)
        return;

    d->message = message;
    QtUniAndroid::callTextMethod(instance(), "setMessage", message);
    emit messageChanged();
}

QAndroidJniObject QUniAndroidAlertDialog::onCreate()
{
    return QAndroidJniObject("android/app/AlertDialog",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidAlertDialog::onInflate(QAndroidJniObject& instance)
{
    Q_D(QUniAndroidAlertDialog);
    QUniAndroidDialog::onInflate(instance);

    if (!d->title.isNull())
        instance.callMethod<void>("setTitle", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(d->title).object());
    if (!d->message.isNull())
        instance.callMethod<void>("setMessage", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(d->message).object());
}

QT_END_NAMESPACE
