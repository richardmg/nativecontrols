/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#include "qnativeandroidactionbar_p.h"
#include "qnativeandroidobject_p_p.h"
#include "qnativeandroiddrawable_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

class QNativeAndroidActionBarPrivate : public QNativeAndroidObjectPrivate
{
    Q_DECLARE_PUBLIC(QNativeAndroidActionBar)

public:
    void updateBackground();

    bool visible = true;
    qreal elevation = 0.0;
    QString title;
    QString subtitle;
    QNativeAndroidDrawable *background = nullptr;
};

void QNativeAndroidActionBarPrivate::updateBackground()
{
    Q_Q(QNativeAndroidActionBar);
    if (!q->isValid() || !background)
        return;

    QAndroidJniObject bar = q->instance();
    QAndroidJniObject bg = background->instance();
    QtNativeAndroid::callFunction([=]() {
        bar.callMethod<void>("setBackgroundDrawable", "(Landroid/graphics/drawable/Drawable;)V", bg.object());
    });
}

QNativeAndroidActionBar::QNativeAndroidActionBar(QObject *parent)
    : QNativeAndroidObject(*(new QNativeAndroidActionBarPrivate), parent)
{
}

bool QNativeAndroidActionBar::isVisible() const
{
    Q_D(const QNativeAndroidActionBar);
    return d->visible;
}

void QNativeAndroidActionBar::setVisible(bool visible)
{
    Q_D(QNativeAndroidActionBar);
    if (visible == isVisible())
        return;

    d->visible = visible;
    if (visible)
        QtNativeAndroid::callVoidMethod(instance(), "show");
    else
        QtNativeAndroid::callVoidMethod(instance(), "hide");
    emit visibleChanged();
}

qreal QNativeAndroidActionBar::elevation() const
{
    Q_D(const QNativeAndroidActionBar);
    return d->elevation;
}

void QNativeAndroidActionBar::setElevation(qreal elevation)
{
    Q_D(QNativeAndroidActionBar);
    if (qFuzzyCompare(d->elevation, elevation))
        return;

    d->elevation = elevation;
    QtNativeAndroid::callRealMethod(instance(), "setElevation", elevation);
    emit elevationChanged();
}

QString QNativeAndroidActionBar::title() const
{
    Q_D(const QNativeAndroidActionBar);
    return d->title;
}

void QNativeAndroidActionBar::setTitle(const QString &title)
{
    Q_D(QNativeAndroidActionBar);
    if (d->title == title)
        return;

    d->title = title;
    QtNativeAndroid::callTextMethod(instance(), "setTitle", title);
    emit titleChanged();
}

QString QNativeAndroidActionBar::subtitle() const
{
    Q_D(const QNativeAndroidActionBar);
    return d->subtitle;
}

void QNativeAndroidActionBar::setSubtitle(const QString &subtitle)
{
    Q_D(QNativeAndroidActionBar);
    if (d->subtitle == subtitle)
        return;

    d->subtitle = subtitle;
    QtNativeAndroid::callTextMethod(instance(), "setSubtitle", subtitle);
    emit subtitleChanged();
}

QNativeAndroidDrawable *QNativeAndroidActionBar::background() const
{
    Q_D(const QNativeAndroidActionBar);
    return d->background;
}

void QNativeAndroidActionBar::setBackground(QNativeAndroidDrawable *background)
{
    Q_D(QNativeAndroidActionBar);
    if (d->background == background)
        return;

    if (d->background) {
        QObjectPrivate::disconnect(d->background, &QNativeAndroidObject::instanceChanged, d, &QNativeAndroidActionBarPrivate::updateBackground);
        d->background->destruct();
    }
    d->background = background;
    if (d->background) {
        QObjectPrivate::connect(d->background, &QNativeAndroidObject::instanceChanged, d, &QNativeAndroidActionBarPrivate::updateBackground);
        d->background->construct();
    }
    emit backgroundChanged();
}

void QNativeAndroidActionBar::onInflate(QAndroidJniObject &instance)
{
    Q_D(QNativeAndroidActionBar);
    instance.callMethod<void>(d->visible ? "show" : "hide");

    if (!d->title.isNull())
        instance.callMethod<void>("setTitle", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(d->title).object());
    if (!d->subtitle.isNull())
        instance.callMethod<void>("setSubtitle", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(d->subtitle).object());

    // TODO: properties
    instance.callMethod<void>("setElevation", "(F)V", d->elevation);
    instance.callMethod<void>("setDisplayHomeAsUpEnabled", "(Z)V", true);
    instance.callMethod<void>("setHomeButtonEnabled", "(Z)V", true);
}

void QNativeAndroidActionBar::objectChange(ObjectChange change)
{
    Q_D(QNativeAndroidActionBar);
    QNativeAndroidObject::objectChange(change);
    if (change == InstanceChange)
        d->updateBackground();
}

QT_END_NAMESPACE
