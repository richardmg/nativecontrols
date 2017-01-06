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

#include "qnativeandroidactivity_p.h"
#include "qnativeandroidcontextwrapper_p_p.h"
#include "qnativeandroidactionbar_p.h"
#include "qnativeandroidmenuitem_p.h"
#include "qnativeandroidmenu_p.h"
#include "qnativeandroidview_p.h"
#include "qnativeandroidwindow_p.h"
#include "qtnativeandroidfunctions_p.h"
#include <QtCore/private/qjnihelpers_p.h>
#include <QtAndroidExtras/qandroidfunctions.h>
#include <QtAndroidExtras/qandroidjnienvironment.h>

QT_BEGIN_NAMESPACE

class QNativeAndroidActivityPrivate : public QNativeAndroidContextWrapperPrivate
{
    Q_DECLARE_PUBLIC(QNativeAndroidActivity)

public:
    void setupWindow();
    void setupActionBar();
    void updateOptionsMenu();
    void invalidateOptionsMenu();
    void updateContentView();

    QNativeAndroidWindow *window = nullptr;
    QNativeAndroidView *contentView = nullptr;
    QNativeAndroidMenu *optionsMenu = nullptr;
    QNativeAndroidActionBar *actionBar = nullptr;
};

void QNativeAndroidActivityPrivate::setupWindow()
{
    Q_Q(QNativeAndroidActivity);
    if (!q->isValid())
        return;

    QAndroidJniObject activity = q->instance();
    QtNativeAndroid::callFunction([=]() {
        QAndroidJniObject wnd = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
        window->inflate(wnd);
    });
}

void QNativeAndroidActivityPrivate::setupActionBar()
{
    Q_Q(QNativeAndroidActivity);
    if (!q->isValid())
        return;

    QAndroidJniObject activity = q->instance();
    QtNativeAndroid::callFunction([=]() {
        QAndroidJniObject bar = activity.callObjectMethod("getActionBar", "()Landroid/app/ActionBar;");
        actionBar->inflate(bar);
    });
}

void QNativeAndroidActivityPrivate::updateOptionsMenu()
{
    Q_Q(QNativeAndroidActivity);
    if (!q->isValid())
        return;

    QAndroidJniObject menu;
    if (optionsMenu)
        menu = optionsMenu->instance();

    QAndroidJniObject activity = q->instance();
    QtNativeAndroid::callFunction([=]() {
        activity.callMethod<void>("setOptionsMenu", "(Lorg/qtproject/qt5/android/bindings/view/QtNativeMenu;)V", menu.object());
    });
}

void QNativeAndroidActivityPrivate::invalidateOptionsMenu()
{
    Q_Q(QNativeAndroidActivity);
    QtNativeAndroid::callVoidMethod(q->instance(), "invalidateOptionsMenu");
}

void QNativeAndroidActivityPrivate::updateContentView()
{
    Q_Q(QNativeAndroidActivity);
    if (!q->isValid())
        return;

    QAndroidJniObject content;
    if (contentView)
        content = contentView->instance();

    QAndroidJniObject activity = q->instance();
    QtNativeAndroid::callFunction([=]() {
        activity.callMethod<void>("setContentView", "(Landroid/view/View;)V", content.object());
    });
}

QNativeAndroidActivity::QNativeAndroidActivity(QObject *parent)
    : QNativeAndroidContextWrapper(*(new QNativeAndroidActivityPrivate), parent)
{
    Q_D(QNativeAndroidActivity);
    d->window = new QNativeAndroidWindow(this);

    // TODO: multiple activities?
    d->setInstance(QtAndroid::androidActivity());
}

QNativeAndroidWindow *QNativeAndroidActivity::window() const
{
    Q_D(const QNativeAndroidActivity);
    return d->window;
}

QNativeAndroidActionBar *QNativeAndroidActivity::actionBar() const
{
    Q_D(const QNativeAndroidActivity);
    return d->actionBar;
}

void QNativeAndroidActivity::setActionBar(QNativeAndroidActionBar *bar)
{
    Q_D(QNativeAndroidActivity);
    if (d->actionBar == bar)
        return;

    if (d->actionBar)
        d->actionBar->destruct();
    d->actionBar = bar;
    if (d->actionBar)
        d->setupActionBar();
}

QNativeAndroidMenu *QNativeAndroidActivity::optionsMenu() const
{
    Q_D(const QNativeAndroidActivity);
    return d->optionsMenu;
}

void QNativeAndroidActivity::setOptionsMenu(QNativeAndroidMenu *menu)
{
    Q_D(QNativeAndroidActivity);
    if (d->optionsMenu == menu)
        return;

    if (d->optionsMenu) {
        QObjectPrivate::disconnect(d->optionsMenu, &QNativeAndroidObject::instanceChanged, d, &QNativeAndroidActivityPrivate::updateOptionsMenu);
        d->optionsMenu->destruct();
    }
    d->optionsMenu = menu;
    if (d->optionsMenu) {
        QObjectPrivate::connect(d->optionsMenu, &QNativeAndroidObject::instanceChanged, d, &QNativeAndroidActivityPrivate::updateOptionsMenu);
        if (isComponentComplete())
            d->optionsMenu->construct();
    }
}

QNativeAndroidView *QNativeAndroidActivity::contentView() const
{
    Q_D(const QNativeAndroidActivity);
    return d->contentView;
}

void QNativeAndroidActivity::setContentView(QNativeAndroidView *view)
{
    Q_D(QNativeAndroidActivity);
    if (d->contentView == view)
        return;
    if (d->contentView) {
        QObjectPrivate::disconnect(d->contentView, &QNativeAndroidObject::instanceChanged, d, &QNativeAndroidActivityPrivate::updateContentView);
        d->contentView->destruct();
    }
    d->contentView = view;
    if (d->contentView) {
        view->setParent(this);
        view->setContext(this);
        QObjectPrivate::connect(d->contentView, &QNativeAndroidObject::instanceChanged, d, &QNativeAndroidActivityPrivate::updateContentView);
        if (isComponentComplete())
            d->contentView->construct();
    }
}

void QNativeAndroidActivity::start()
{
    Q_D(QNativeAndroidActivity);
    foreach (QObject *child, children()) {
        QNativeAndroidObject *object = qobject_cast<QNativeAndroidObject *>(child);
        if (object)
            object->construct();
    }

    if (d->actionBar)
        d->setupActionBar();

    if (d->window)
        d->setupWindow();
}

void QNativeAndroidActivity::classBegin()
{
    QNativeAndroidContextWrapper::classBegin();
}

void QNativeAndroidActivity::componentComplete()
{
    QNativeAndroidContextWrapper::componentComplete();
    start();
}

QT_END_NAMESPACE
