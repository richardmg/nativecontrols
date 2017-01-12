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

#include "qnativeandroidcontextual_p.h"
#include "qnativeandroidcontextual_p_p.h"
#include "qnativeandroidcontext_p.h"
#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

static QNativeAndroidContext *findContext(QNativeAndroidObject *object)
{
    QNativeAndroidContext *context = qobject_cast<QNativeAndroidContext *>(object);
    QObject *p = object->parent();
    while (p && !context) {
        QNativeAndroidContextual *contextual = qobject_cast<QNativeAndroidContextual *>(p);
        if (contextual)
            context = contextual->context();
        p = p->parent();
    }
    return context;
}

bool QNativeAndroidContextualPrivate::initContext(QNativeAndroidContext *context)
{
    Q_Q(QNativeAndroidContextual);
    if (!context)
        context = findContext(q);
    q->setContext(context);
    return context;
}

void QNativeAndroidContextualPrivate::propagateContext()
{
    Q_Q(QNativeAndroidContextual);
    foreach (QObject *child, q->children()) {
        QNativeAndroidContextual *contextual = qobject_cast<QNativeAndroidContextual *>(child);
        if (contextual)
            contextual->setContext(context);
    }
}

void QNativeAndroidContextualPrivate::_q_resolveContext()
{
    Q_Q(QNativeAndroidContextual);
    if (!context) {
        q->setContext(findContext(q));
        if (!context)
            qWarning() << "QNativeAndroidContextual: could not resolve context for" << q;
    }
}

QNativeAndroidContextual::QNativeAndroidContextual(QObject *parent)
    : QNativeAndroidObject(*(new QNativeAndroidContextualPrivate), parent)
{
    Q_D(QNativeAndroidContextual);
    if (!d->initContext())
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QNativeAndroidContextual::QNativeAndroidContextual(QNativeAndroidContext* context, QObject *parent)
    : QNativeAndroidObject(*(new QNativeAndroidContextualPrivate), parent || context == this ? parent : context)
{
    Q_D(QNativeAndroidContextual);
    if (!d->initContext(context))
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QNativeAndroidContextual::QNativeAndroidContextual(QNativeAndroidContextualPrivate &dd, QObject *parent)
    : QNativeAndroidObject(dd, parent)
{
    Q_D(QNativeAndroidContextual);
    if (!d->initContext())
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QNativeAndroidContextual::QNativeAndroidContextual(QNativeAndroidContextualPrivate &dd, QNativeAndroidContext *context, QObject *parent)
    : QNativeAndroidObject(dd, parent)
{
    Q_D(QNativeAndroidContextual);
    if (!d->initContext(context))
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QAndroidJniObject QNativeAndroidContextual::ctx() const
{
    Q_D(const QNativeAndroidContextual);
    if (!d->context)
        return QAndroidJniObject();
    return d->context->instance();
}

QNativeAndroidContext *QNativeAndroidContextual::context() const
{
    Q_D(const QNativeAndroidContextual);
    return d->context;
}

void QNativeAndroidContextual::setContext(QNativeAndroidContext *context)
{
    Q_D(QNativeAndroidContextual);
    if (d->context == context)
        return;

    d->context = context;
    d->propagateContext();
    emit contextChanged();
}

void QNativeAndroidContextual::componentComplete()
{
    Q_D(QNativeAndroidContextual);
    QNativeAndroidObject::componentComplete();
    d->propagateContext();
}

QT_END_NAMESPACE

#include "moc_qnativeandroidcontextual_p.cpp"
