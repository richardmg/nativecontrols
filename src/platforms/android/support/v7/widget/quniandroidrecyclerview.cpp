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

#include "quniandroidrecyclerview_p.h"
#include "quniandroidviewgroup_p_p.h"
#include "quniandroidrecycleradapter_p.h"
#include "qtnativeandroidfunctions_p.h"

QT_BEGIN_NAMESPACE

class QUniAndroidRecyclerViewPrivate : public QUniAndroidViewGroupPrivate
{
    Q_DECLARE_PUBLIC(QUniAndroidRecyclerView)

public:
    void updateAdapter();

    QUniAndroidRecyclerAdapter *adapter = nullptr;
    QAndroidJniObject layoutManager;
};

void QUniAndroidRecyclerViewPrivate::updateAdapter()
{
    Q_Q(QUniAndroidRecyclerView);
    if (!q->isValid() || !adapter)
        return;

    QAndroidJniObject view = q->instance();
    QAndroidJniObject ad = adapter->instance();
    QtUniAndroid::callFunction([=]() {
        view.callMethod<void>("setAdapter", "(Landroid/support/v7/widget/RecyclerView$Adapter;)V", ad.object());
    });
}

QUniAndroidRecyclerView::QUniAndroidRecyclerView(QUniAndroidContext *context)
    : QUniAndroidViewGroup(*(new QUniAndroidRecyclerViewPrivate), context)
{
}

QUniAndroidRecyclerAdapter *QUniAndroidRecyclerView::adapter() const
{
    Q_D(const QUniAndroidRecyclerView);
    return d->adapter;
}

void QUniAndroidRecyclerView::setAdapter(QUniAndroidRecyclerAdapter *adapter)
{
    Q_D(QUniAndroidRecyclerView);
    if (d->adapter == adapter)
        return;

    if (d->adapter) {
        d->adapter->setContext(0);
        QObjectPrivate::disconnect(d->adapter, &QUniAndroidObject::instanceChanged, d, &QUniAndroidRecyclerViewPrivate::updateAdapter);
        d->adapter->destruct();
    }
    d->adapter = adapter;
    if (d->adapter) {
        d->adapter->setContext(context());
        QObjectPrivate::connect(d->adapter, &QUniAndroidObject::instanceChanged, d, &QUniAndroidRecyclerViewPrivate::updateAdapter);
        if (isValid())
            d->adapter->construct();
    }
    emit adapterChanged();
}

QAndroidJniObject QUniAndroidRecyclerView::onCreate()
{
    return QAndroidJniObject("android/support/v7/widget/RecyclerView",
                             "(Landroid/content/Context;)V",
                             ctx().object());
}

void QUniAndroidRecyclerView::onInflate(QAndroidJniObject& instance)
{
    Q_D(QUniAndroidRecyclerView);
    d->layoutManager = QAndroidJniObject("android/support/v7/widget/LinearLayoutManager",
                                        "(Landroid/content/Context;)V",
                                        ctx().object());

    instance.callMethod<void>("setLayoutManager",
                              "(Landroid/support/v7/widget/RecyclerView$LayoutManager;)V",
                              d->layoutManager.object());

    QUniAndroidViewGroup::onInflate(instance);
}

void QUniAndroidRecyclerView::objectChange(ObjectChange change)
{
    Q_D(QUniAndroidRecyclerView);
    QUniAndroidViewGroup::objectChange(change);
    if (change == InstanceChange)
        d->updateAdapter();
}

QT_END_NAMESPACE
