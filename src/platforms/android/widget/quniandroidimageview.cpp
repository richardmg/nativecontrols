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

#include "quniandroidimageview_p.h"
#include "quniandroidview_p_p.h"
#include "quniandroidoptional_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidImageViewPrivate : public QUniAndroidViewPrivate
{
public:
    QUrl uri;
    int resource = 0;
    QUniAndroidOptional<int> tint;
};

QUniAndroidImageView::QUniAndroidImageView(QUniAndroidContext *context)
    : QUniAndroidView(*(new QUniAndroidImageViewPrivate), context)
{
}

QUrl QUniAndroidImageView::imageURI() const
{
    Q_D(const QUniAndroidImageView);
    return d->uri;
}

void QUniAndroidImageView::setImageURI(const QUrl &uri)
{
    Q_D(QUniAndroidImageView);
    if (d->uri == uri)
        return;

    d->uri = uri;
    if (isValid()) {
        QAndroidJniObject v = instance();
        QAndroidJniObject u = getUri();
        QtNativeAndroid::callFunction([=]() {
            v.callMethod<void>("setImageURI", "(Landroid/net/Uri;)V", u.object());
        });
    }
    emit imageURIChanged();
}

int QUniAndroidImageView::imageResource() const
{
    Q_D(const QUniAndroidImageView);
    return d->resource;
}

void QUniAndroidImageView::setImageResource(int resource)
{
    Q_D(QUniAndroidImageView);
    if (d->resource == resource)
        return;

    d->resource = resource;
    QtNativeAndroid::callIntMethod(instance(), "setImageResource", resource);
    emit imageResourceChanged();
}

int QUniAndroidImageView::imageTintColor() const
{
    Q_D(const QUniAndroidImageView);
    if (d->tint.isNull())
        return 0; // TODO
    return d->tint;
}

void QUniAndroidImageView::setImageTintColor(int color)
{
    Q_D(QUniAndroidImageView);
    if (!d->tint.isNull() && d->tint == color)
        return;

    d->tint = color;
    if (isValid()) {
        QAndroidJniObject view = instance();
        QtNativeAndroid::callFunction([=]() {
            QAndroidJniObject tint = QAndroidJniObject::callStaticObjectMethod("android/content/res/ColorStateList",
                                                                               "valueOf",
                                                                               "(I)Landroid/content/res/ColorStateList;",
                                                                               color);
            view.callMethod<void>("setImageTintList", "(Landroid/content/res/ColorStateList;)v", tint.object());
        });
    }
    emit imageTintColorChanged();
}

QAndroidJniObject QUniAndroidImageView::onCreate()
{
    return QAndroidJniObject("android/widget/ImageView",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidImageView::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidImageView);
    QUniAndroidView::onInflate(instance);

    if (d->uri.isValid())
        instance.callMethod<void>("setImageURI", "(Landroid/net/Uri;)V", getUri().object());
    if (d->resource > 0)
        instance.callMethod<void>("setImageResource", "(I)V", d->resource);
    if (!d->tint.isNull()) {
        QAndroidJniObject tint = QAndroidJniObject::callStaticObjectMethod("android/content/res/ColorStateList",
                                                                           "valueOf",
                                                                           "(I)Landroid/content/res/ColorStateList;",
                                                                           d->tint);
        instance.callMethod<void>("setImageTintList", "(Landroid/content/res/ColorStateList;)v", tint.object());
    }
}

QAndroidJniObject QUniAndroidImageView::getUri() const
{
    Q_D(const QUniAndroidImageView);
    QAndroidJniObject str = QAndroidJniObject::fromString(d->uri.toString());
    return QAndroidJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", str.object());
}

QT_END_NAMESPACE
