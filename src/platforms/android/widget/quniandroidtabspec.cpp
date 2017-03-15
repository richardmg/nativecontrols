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

#include "quniandroidtabspec_p.h"
#include "quniandroidtabhost_p.h"
#include "quniandroidview_p.h"
#include "qtnativeandroidfunctions_p.h"
#include <QtAndroidExtras/qandroidjniobject.h>
#include <QtCore/private/qobject_p.h>

QT_BEGIN_NAMESPACE

class QUniAndroidTabSpecPrivate : public QObjectPrivate
{
public:
    QString label;
};

QUniAndroidTabSpec::QUniAndroidTabSpec(QUniAndroidView *view)
    : QObject(*(new QUniAndroidTabSpecPrivate), view)
{
    QUniAndroidView *parent = qobject_cast<QUniAndroidView *>(view->parent());
    if (parent)
        parent->setIdentifier(16908305); // TODO: android.R.id.tabcontent
}

QUniAndroidTabSpec *QUniAndroidTabSpec::qmlAttachedProperties(QObject *object)
{
    QUniAndroidView *view = qobject_cast<QUniAndroidView*>(object);
    if (view)
        return new QUniAndroidTabSpec(view);
    return 0;
}

QString QUniAndroidTabSpec::label() const
{
    Q_D(const QUniAndroidTabSpec);
    return d->label;
}

void QUniAndroidTabSpec::setLabel(const QString &label)
{
    Q_D(QUniAndroidTabSpec);
    if (d->label == label)
        return;

    d->label = label;
    // TODO: invalidate
    emit labelChanged();
}

void QUniAndroidTabSpec::setup(QAndroidJniObject &host, int index)
{
    Q_D(QUniAndroidTabSpec);
    int id = -1;
    QUniAndroidView *content = qobject_cast<QUniAndroidView *>(parent());
    if (content)
        id = content->identifier();

    QtNativeAndroid::callFunction([=]() {
        QAndroidJniObject spec = host.callObjectMethod("newTabSpec",
                                                       "(Ljava/lang/String;)Landroid/widget/TabHost$TabSpec;",
                                                       QAndroidJniObject::fromString(QString::number(index)).object());

        spec.callObjectMethod("setIndicator",
                             "(Ljava/lang/CharSequence;)Landroid/widget/TabHost$TabSpec;",
                             QAndroidJniObject::fromString(d->label).object());

        if (id != -1) {
            spec.callObjectMethod("setContent",
                                  "(I)Landroid/widget/TabHost$TabSpec;",
                                  id);
        }

        host.callMethod<void>("addTab", "(Landroid/widget/TabHost$TabSpec;)V", spec.object());
    });
}

QT_END_NAMESPACE
