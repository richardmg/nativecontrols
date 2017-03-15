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

#include "quniandroidmenuitem_p.h"
#include "quniandroidcontextual_p_p.h"
#include "qtnativeandroidfunctions_p.h"
#include "quniandroidcontext_p.h"
#include "quniandroidview_p.h"

QT_BEGIN_NAMESPACE

static bool native_onClick(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidMenuItem *item = reinterpret_cast<QUniAndroidMenuItem *>(instance);
    if (item) {
        QMetaObject::invokeMethod(item, "click", Qt::QueuedConnection);
        return true;
    }
    return false;
}

static bool native_onMenuItemActionCollapse(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidMenuItem *item = reinterpret_cast<QUniAndroidMenuItem *>(instance);
    if (item) {
        // TODO
        return true;
    }
    return false;
}

static bool native_onMenuItemActionExpand(JNIEnv *env, jobject object, jlong instance)
{
    Q_UNUSED(env);
    Q_UNUSED(object);
    QUniAndroidMenuItem *item = reinterpret_cast<QUniAndroidMenuItem *>(instance);
    if (item) {
        // TODO
        return true;
    }
    return false;
}

static void registerNativeMenuItemMethods(jobject item)
{
    JNINativeMethod methods[] {{"onClick", "(J)Z", reinterpret_cast<void *>(native_onClick)},
                               {"onMenuItemActionCollapse", "(J)Z", reinterpret_cast<void *>(native_onMenuItemActionCollapse)},
                               {"onMenuItemActionExpand", "(J)Z", reinterpret_cast<void *>(native_onMenuItemActionExpand)}};

    QAndroidJniEnvironment env;
    jclass cls = env->GetObjectClass(item);
    env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(cls);
}

class QUniAndroidMenuItemPrivate : public QUniAndroidContextualPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidMenuItem)

public:
    void updateActionView();

    QString title;
    bool enabled = true;
    bool visible = true;
    bool checkable = false;
    bool checked = false;
    int showAs = 0; // TODO: SHOW_AS_ACTION_NEVER
    QUniAndroidView *actionView = nullptr;
};

void QUniAndroidMenuItemPrivate::updateActionView()
{
    Q_Q(QUniAndroidMenuItem);
    if (!q->isValid() || !actionView)
        return;

    QAndroidJniObject item = q->instance();
    QAndroidJniObject view = actionView->instance();
    QtNativeAndroid::callFunction([=]() {
        item.callMethod<void>("setActionView", "(Landroid/view/View;)V", view.object());
    });
}

QUniAndroidMenuItem::QUniAndroidMenuItem(QObject *parent)
    : QUniAndroidContextual(*(new QUniAndroidMenuItemPrivate), parent)
{
}

QString QUniAndroidMenuItem::title() const
{
    Q_D(const QUniAndroidMenuItem);
    return d->title;
}

void QUniAndroidMenuItem::setTitle(const QString &title)
{
    Q_D(QUniAndroidMenuItem);
    if (d->title == title)
        return;

    d->title = title;
    QtNativeAndroid::callTextMethod(instance(), "setTitle", title);
    emit titleChanged();
}

bool QUniAndroidMenuItem::isEnabled() const
{
    Q_D(const QUniAndroidMenuItem);
    return d->enabled;
}

void QUniAndroidMenuItem::setEnabled(bool enabled)
{
    Q_D(QUniAndroidMenuItem);
    if (d->enabled == enabled)
        return;

    d->enabled = enabled;
    QtNativeAndroid::callBoolMethod(instance(), "setEnabled", enabled);
    emit enabledChanged();
}

bool QUniAndroidMenuItem::isVisible() const
{
    Q_D(const QUniAndroidMenuItem);
    return d->visible;
}

void QUniAndroidMenuItem::setVisible(bool visible)
{
    Q_D(QUniAndroidMenuItem);
    if (d->visible == visible)
        return;

    d->visible = visible;
    QtNativeAndroid::callBoolMethod(instance(), "setVisible", visible);
    if (isValid() && context())
        QMetaObject::invokeMethod(context(), "invalidateOptionsMenu");
    emit visibleChanged();
}

bool QUniAndroidMenuItem::isCheckable() const
{
    Q_D(const QUniAndroidMenuItem);
    return d->checkable;
}

void QUniAndroidMenuItem::setCheckable(bool checkable)
{
    Q_D(QUniAndroidMenuItem);
    if (d->checkable == checkable)
        return;

    d->checkable = checkable;
    QtNativeAndroid::callBoolMethod(instance(), "setCheckable", checkable);
    emit checkableChanged();
}

bool QUniAndroidMenuItem::isChecked() const
{
    Q_D(const QUniAndroidMenuItem);
    return d->checked;
}

void QUniAndroidMenuItem::setChecked(bool checked)
{
    Q_D(QUniAndroidMenuItem);
    if (d->checked == checked)
        return;

    d->checked = checked;
    QtNativeAndroid::callBoolMethod(instance(), "setChecked", checked);
    emit checkedChanged();
}

int QUniAndroidMenuItem::showAs() const
{
    Q_D(const QUniAndroidMenuItem);
    return d->showAs;
}

void QUniAndroidMenuItem::setShowAs(int showAs)
{
    Q_D(QUniAndroidMenuItem);
    if (d->showAs == showAs)
        return;

    d->showAs = showAs;
    QtNativeAndroid::callIntMethod(instance(), "setShowAs", showAs);
    emit showAsChanged();
}

QUniAndroidView *QUniAndroidMenuItem::actionView() const
{
    Q_D(const QUniAndroidMenuItem);
    return d->actionView;
}

void QUniAndroidMenuItem::setActionView(QUniAndroidView *view)
{
    Q_D(QUniAndroidMenuItem);
    if (d->actionView == view)
        return;

    if (d->actionView) {
        QObjectPrivate::disconnect(d->actionView, &QUniAndroidObject::instanceChanged, d, &QUniAndroidMenuItemPrivate::updateActionView);
        d->actionView->destruct();
    }
    d->actionView = view;
    if (d->actionView) {
        QObjectPrivate::connect(d->actionView, &QUniAndroidObject::instanceChanged, d, &QUniAndroidMenuItemPrivate::updateActionView);
        if (isValid())
            d->actionView->construct();
    }
    emit actionViewChanged();
}

QAndroidJniObject QUniAndroidMenuItem::onCreate()
{
    return QAndroidJniObject("org/qtproject/qt5/android/bindings/view/QtNativeMenuItem",
                             "(J)V",
                             reinterpret_cast<jlong>(this));
}

void QUniAndroidMenuItem::onInflate(QAndroidJniObject &instance)
{
    Q_D(QUniAndroidMenuItem);
    instance.callMethod<void>("setTitle", "(Ljava/lang/CharSequence;)V", QAndroidJniObject::fromString(d->title).object());
    instance.callMethod<void>("setEnabled", "(Z)V", d->enabled);
    instance.callMethod<void>("setVisible", "(Z)V", d->visible);
    instance.callMethod<void>("setCheckable", "(Z)V", d->checkable);
    instance.callMethod<void>("setChecked", "(Z)V", d->enabled);
    instance.callMethod<void>("setShowAs", "(I)V", d->showAs);

    static bool nativeMethodsRegistered = false;
    if (!nativeMethodsRegistered) {
        registerNativeMenuItemMethods(instance.object());
        nativeMethodsRegistered = true;
    }
}

void QUniAndroidMenuItem::objectChange(ObjectChange change)
{
    Q_D(QUniAndroidMenuItem);
    QUniAndroidContextual::objectChange(change);
    if (change == InstanceChange)
        d->updateActionView();
}

QT_END_NAMESPACE
