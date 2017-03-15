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

#include "quniandroidactionbar_p.h"
#include "quniandroidobject_p_p.h"
#include "quniandroiddrawable_p.h"
#include "qtuniandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidActionBarPrivate : public QUniAndroidObjectPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidActionBar)

public:
    void updateBackground();

    bool visible = true;
    qreal elevation = 0.0;
    QString title;
    QString subtitle;
    QUniAndroidDrawable *background = nullptr;
};

void QUniAndroidActionBarPrivate::updateBackground()
{
    Q_Q(QUniAndroidActionBar);
    if (!q->isValid() || !background)
        return;

    QAndroidJniObject bar = q->instance();
    QAndroidJniObject bg = background->instance();
    QtUniAndroid::callFunction([=]() {
        bar.callMethod<void>("setBackgroundDrawable", "(Landroid/graphics/drawable/Drawable;)V", bg.object());
    });
}

QUniAndroidActionBar::QUniAndroidActionBar(QObject *parent)
    : QUniAndroidObject(*(new QUniAndroidActionBarPrivate), parent)
{
}

bool QUniAndroidActionBar::isVisible() const
{
    Q_D(const QUniAndroidActionBar);
    return d->visible;
}

void QUniAndroidActionBar::setVisible(bool visible)
{
    Q_D(QUniAndroidActionBar);
    if (visible == isVisible())
        return;

    d->visible = visible;
    if (visible)
        QtUniAndroid::callVoidMethod(instance(), "show");
    else
        QtUniAndroid::callVoidMethod(instance(), "hide");
    emit visibleChanged();
}

qreal QUniAndroidActionBar::elevation() const
{
    Q_D(const QUniAndroidActionBar);
    return d->elevation;
}

void QUniAndroidActionBar::setElevation(qreal elevation)
{
    Q_D(QUniAndroidActionBar);
    if (qFuzzyCompare(d->elevation, elevation))
        return;

    d->elevation = elevation;
    QtUniAndroid::callRealMethod(instance(), "setElevation", elevation);
    emit elevationChanged();
}

QString QUniAndroidActionBar::title() const
{
    Q_D(const QUniAndroidActionBar);
    return d->title;
}

void QUniAndroidActionBar::setTitle(const QString &title)
{
    Q_D(QUniAndroidActionBar);
    if (d->title == title)
        return;

    d->title = title;
    QtUniAndroid::callTextMethod(instance(), "setTitle", title);
    emit titleChanged();
}

QString QUniAndroidActionBar::subtitle() const
{
    Q_D(const QUniAndroidActionBar);
    return d->subtitle;
}

void QUniAndroidActionBar::setSubtitle(const QString &subtitle)
{
    Q_D(QUniAndroidActionBar);
    if (d->subtitle == subtitle)
        return;

    d->subtitle = subtitle;
    QtUniAndroid::callTextMethod(instance(), "setSubtitle", subtitle);
    emit subtitleChanged();
}

QUniAndroidDrawable *QUniAndroidActionBar::background() const
{
    Q_D(const QUniAndroidActionBar);
    return d->background;
}

void QUniAndroidActionBar::setBackground(QUniAndroidDrawable *background)
{
    Q_D(QUniAndroidActionBar);
    if (d->background == background)
        return;

    if (d->background) {
        QObjectPrivate::disconnect(d->background, &QUniAndroidObject::instanceChanged, d, &QUniAndroidActionBarPrivate::updateBackground);
        d->background->destruct();
    }
    d->background = background;
    if (d->background) {
        QObjectPrivate::connect(d->background, &QUniAndroidObject::instanceChanged, d, &QUniAndroidActionBarPrivate::updateBackground);
        d->background->construct();
    }
    emit backgroundChanged();
}

void QUniAndroidActionBar::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidActionBar);
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

void QUniAndroidActionBar::objectChange(ObjectChange change)
{
    Q_D(QUniAndroidActionBar);
    QUniAndroidObject::objectChange(change);
    if (change == InstanceChange)
        d->updateBackground();
}

QT_END_NAMESPACE
