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

#include "quniandroidcontextual_p.h"
#include "quniandroidcontextual_p_p.h"
#include "quniandroidcontext_p.h"
#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

static QUniAndroidContext *findContext(QUniAndroidObject *object)
{
    QUniAndroidContext *context = qobject_cast<QUniAndroidContext *>(object);
    QObject *p = object->parent();
    while (p && !context) {
        QUniAndroidContextual *contextual = qobject_cast<QUniAndroidContextual *>(p);
        if (contextual)
            context = contextual->context();
        p = p->parent();
    }
    return context;
}

bool QUniAndroidContextualPrivate::initContext(QUniAndroidContext *context)
{
    Q_Q(QUniAndroidContextual);
    if (!context)
        context = findContext(q);
    q->setContext(context);
    return context;
}

void QUniAndroidContextualPrivate::propagateContext()
{
    Q_Q(QUniAndroidContextual);
    foreach (QObject *child, q->children()) {
        QUniAndroidContextual *contextual = qobject_cast<QUniAndroidContextual *>(child);
        if (contextual)
            contextual->setContext(context);
    }
}

void QUniAndroidContextualPrivate::_q_resolveContext()
{
    Q_Q(QUniAndroidContextual);
    if (!context) {
        q->setContext(findContext(q));
        if (!context)
            qWarning() << "QUniAndroidContextual: could not resolve context for" << q;
    }
}

QUniAndroidContextual::QUniAndroidContextual(QObject *parent)
    : QUniAndroidObject(*(new QUniAndroidContextualPrivate), parent)
{
    Q_D(QUniAndroidContextual);
    if (!d->initContext())
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QUniAndroidContextual::QUniAndroidContextual(QUniAndroidContext* context, QObject *parent)
    : QUniAndroidObject(*(new QUniAndroidContextualPrivate), parent || context == this ? parent : context)
{
    Q_D(QUniAndroidContextual);
    if (!d->initContext(context))
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QUniAndroidContextual::QUniAndroidContextual(QUniAndroidContextualPrivate &dd, QObject *parent)
    : QUniAndroidObject(dd, parent)
{
    Q_D(QUniAndroidContextual);
    if (!d->initContext())
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QUniAndroidContextual::QUniAndroidContextual(QUniAndroidContextualPrivate &dd, QUniAndroidContext *context, QObject *parent)
    : QUniAndroidObject(dd, parent)
{
    Q_D(QUniAndroidContextual);
    if (!d->initContext(context))
        QMetaObject::invokeMethod(this, "_q_resolveContext", Qt::QueuedConnection);
}

QAndroidJniObject QUniAndroidContextual::ctx() const
{
    Q_D(const QUniAndroidContextual);
    if (!d->context)
        return QAndroidJniObject();
    return d->context->instance();
}

QUniAndroidContext *QUniAndroidContextual::context() const
{
    Q_D(const QUniAndroidContextual);
    return d->context;
}

void QUniAndroidContextual::setContext(QUniAndroidContext *context)
{
    Q_D(QUniAndroidContextual);
    if (d->context == context)
        return;

    d->context = context;
    d->propagateContext();
    emit contextChanged();
}

void QUniAndroidContextual::componentComplete()
{
    Q_D(QUniAndroidContextual);
    QUniAndroidObject::componentComplete();
    d->propagateContext();
}

QT_END_NAMESPACE

#include "moc_quniandroidcontextual_p.cpp"
