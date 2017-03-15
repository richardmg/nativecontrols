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

#include "quniandroidpopupmenu_p.h"
#include "quniandroidobject_p_p.h"
#include "qtuniandroidfunctions_p.h"
#include "quniandroidmenuitem_p.h"
#include "quniandroidoptional_p.h"
#include "quniandroidcontext_p.h"
#include "quniandroidview_p.h"
#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

class QUniAndroidPopupMenuPrivate : public QUniAndroidObjectPrivate
{
public:
    QUniAndroidView *anchor = nullptr;
    QUniAndroidOptional<int> gravity;
    QAndroidJniObject listener;
};

QUniAndroidPopupMenu::QUniAndroidPopupMenu(QObject *parent)
    : QUniAndroidObject(*(new QUniAndroidPopupMenuPrivate), parent)
{
}

QList<QUniAndroidMenuItem *> QUniAndroidPopupMenu::items() const
{
    QList<QUniAndroidMenuItem *> lst;
    foreach (QObject *child, children()) {
        QUniAndroidMenuItem *item = qobject_cast<QUniAndroidMenuItem *>(child);
        if (item)
            lst += item;
    }
    return lst;
}

QUniAndroidView *QUniAndroidPopupMenu::anchor() const
{
    Q_D(const QUniAndroidPopupMenu);
    return d->anchor;
}

void QUniAndroidPopupMenu::setAnchor(QUniAndroidView *anchor)
{
    Q_D(QUniAndroidPopupMenu);
    if (d->anchor == anchor)
        return;

    d->anchor = anchor;
    emit anchorChanged();
}

int QUniAndroidPopupMenu::gravity() const
{
    Q_D(const QUniAndroidPopupMenu);
    if (d->gravity.isNull())
        return 0; // TODO
    return d->gravity;
}

void QUniAndroidPopupMenu::setGravity(int value)
{
    Q_D(QUniAndroidPopupMenu);
    if (value == gravity())
        return;

    d->gravity = value;
    emit gravityChanged();
}

void QUniAndroidPopupMenu::show()
{
    Q_D(QUniAndroidPopupMenu);
    QUniAndroidView *anchor = d->anchor ? d->anchor : qobject_cast<QUniAndroidView *>(parent());
    if (!anchor) {
        qWarning() << "PopupMenu parent must be either anchored or in a view.";
        return;
    }

    QUniAndroidContext *context = anchor->context();
    if (!context) {
        qWarning() << "PopupMenu is not ready - no context.";
        return;
    }

    QAndroidJniObject c = context->instance();
    QAndroidJniObject a = anchor->instance();

    QtUniAndroid::callFunction([=]() {
        QAndroidJniObject popup;
        if (!d->gravity.isNull()) {
            popup = QAndroidJniObject("android/widget/PopupMenu",
                                      "(Landroid/content/Context;Landroid/view/View;I)V",
                                      c.object(), a.object(), d->gravity);
        } else {
            popup = QAndroidJniObject("android/widget/PopupMenu",
                                      "(Landroid/content/Context;Landroid/view/View;)V",
                                      c.object(), a.object());
        }
        inflate(popup);

        QAndroidJniObject menu = popup.callObjectMethod("getMenu", "()Landroid/view/Menu;");
        foreach (QUniAndroidMenuItem *item, items()) {
            QAndroidJniObject it = menu.callObjectMethod("add",
                                                         "(Ljava/lang/CharSequence;)Landroid/view/MenuItem;",
                                                         QAndroidJniObject::fromString(item->title()).object());
            //it.callMethod<void>("...");
        }

        popup.callMethod<void>("show");
    });
}

void QUniAndroidPopupMenu::dismiss()
{
    QtUniAndroid::callVoidMethod(instance(), "dismiss");
}

QT_END_NAMESPACE
