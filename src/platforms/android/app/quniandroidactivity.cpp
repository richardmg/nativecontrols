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

#include "quniandroidactivity_p.h"
#include "quniandroidcontextwrapper_p_p.h"
#include "quniandroidactionbar_p.h"
#include "quniandroidmenuitem_p.h"
#include "quniandroidmenu_p.h"
#include "quniandroidview_p.h"
#include "quniandroidwindow_p.h"
#include "qtnativeandroidfunctions_p.h"
#include <QtCore/private/qjnihelpers_p.h>
#include <QtAndroidExtras/qandroidfunctions.h>
#include <QtAndroidExtras/qandroidjnienvironment.h>

QT_BEGIN_NAMESPACE

class QUniAndroidActivityPrivate : public QUniAndroidContextWrapperPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidActivity)

public:
    void setupWindow();
    void setupActionBar();
    void updateOptionsMenu();
    void invalidateOptionsMenu();
    void updateContentView();

    QUniAndroidWindow *window = nullptr;
    QUniAndroidView *contentView = nullptr;
    QUniAndroidMenu *optionsMenu = nullptr;
    QUniAndroidActionBar *actionBar = nullptr;
};

void QUniAndroidActivityPrivate::setupWindow()
{
    Q_Q(QUniAndroidActivity);
    if (!q->isValid())
        return;

    QAndroidJniObject activity = q->instance();
    QtNativeAndroid::callFunction([=]() {
        QAndroidJniObject wnd = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
        window->inflate(wnd);
    });
}

void QUniAndroidActivityPrivate::setupActionBar()
{
    Q_Q(QUniAndroidActivity);
    if (!q->isValid())
        return;

    QAndroidJniObject activity = q->instance();
    QtNativeAndroid::callFunction([=]() {
        QAndroidJniObject bar = activity.callObjectMethod("getActionBar", "()Landroid/app/ActionBar;");
        actionBar->inflate(bar);
    });
}

void QUniAndroidActivityPrivate::updateOptionsMenu()
{
    Q_Q(QUniAndroidActivity);
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

void QUniAndroidActivityPrivate::invalidateOptionsMenu()
{
    Q_Q(QUniAndroidActivity);
    QtNativeAndroid::callVoidMethod(q->instance(), "invalidateOptionsMenu");
}

void QUniAndroidActivityPrivate::updateContentView()
{
    Q_Q(QUniAndroidActivity);
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

QUniAndroidActivity::QUniAndroidActivity(QObject *parent)
    : QUniAndroidContextWrapper(*(new QUniAndroidActivityPrivate), parent)
{
    Q_D(QUniAndroidActivity);
    d->window = new QUniAndroidWindow(this);

    // TODO: multiple activities?
    d->setInstance(QtAndroid::androidActivity());
}

QUniAndroidWindow *QUniAndroidActivity::window() const
{
    Q_D(const QUniAndroidActivity);
    return d->window;
}

QUniAndroidActionBar *QUniAndroidActivity::actionBar() const
{
    Q_D(const QUniAndroidActivity);
    return d->actionBar;
}

void QUniAndroidActivity::setActionBar(QUniAndroidActionBar *bar)
{
    Q_D(QUniAndroidActivity);
    if (d->actionBar == bar)
        return;

    if (d->actionBar)
        d->actionBar->destruct();
    d->actionBar = bar;
    if (d->actionBar)
        d->setupActionBar();
}

QUniAndroidMenu *QUniAndroidActivity::optionsMenu() const
{
    Q_D(const QUniAndroidActivity);
    return d->optionsMenu;
}

void QUniAndroidActivity::setOptionsMenu(QUniAndroidMenu *menu)
{
    Q_D(QUniAndroidActivity);
    if (d->optionsMenu == menu)
        return;

    if (d->optionsMenu) {
        QObjectPrivate::disconnect(d->optionsMenu, &QUniAndroidObject::instanceChanged, d, &QUniAndroidActivityPrivate::updateOptionsMenu);
        d->optionsMenu->destruct();
    }
    d->optionsMenu = menu;
    if (d->optionsMenu) {
        QObjectPrivate::connect(d->optionsMenu, &QUniAndroidObject::instanceChanged, d, &QUniAndroidActivityPrivate::updateOptionsMenu);
        if (isComponentComplete())
            d->optionsMenu->construct();
    }
}

QUniAndroidView *QUniAndroidActivity::contentView() const
{
    Q_D(const QUniAndroidActivity);
    return d->contentView;
}

void QUniAndroidActivity::setContentView(QUniAndroidView *view)
{
    Q_D(QUniAndroidActivity);
    if (d->contentView == view)
        return;
    if (d->contentView) {
        QObjectPrivate::disconnect(d->contentView, &QUniAndroidObject::instanceChanged, d, &QUniAndroidActivityPrivate::updateContentView);
        d->contentView->destruct();
    }
    d->contentView = view;
    if (d->contentView) {
        view->setParent(this);
        view->setContext(this);
        QObjectPrivate::connect(d->contentView, &QUniAndroidObject::instanceChanged, d, &QUniAndroidActivityPrivate::updateContentView);
        if (isComponentComplete())
            d->contentView->construct();
    }
}

void QUniAndroidActivity::start()
{
    Q_D(QUniAndroidActivity);
    foreach (QObject *child, children()) {
        QUniAndroidObject *object = qobject_cast<QUniAndroidObject *>(child);
        if (object)
            object->construct();
    }

    if (d->actionBar)
        d->setupActionBar();

    if (d->window)
        d->setupWindow();
}

void QUniAndroidActivity::classBegin()
{
    QUniAndroidContextWrapper::classBegin();
}

void QUniAndroidActivity::componentComplete()
{
    QUniAndroidContextWrapper::componentComplete();
    start();
}

QT_END_NAMESPACE
