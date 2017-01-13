/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
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

#include <QtNativeControls/qnativeqobjectbase.h>
#include <QtNativeControls/private/qnativeqobjectbase_p.h>

QT_BEGIN_NAMESPACE

QNativeQObjectBasePrivate::QNativeQObjectBasePrivate(int version)
    : QObjectPrivate(version)
{
}

QNativeQObjectBasePrivate::~QNativeQObjectBasePrivate()
{
}

void QNativeQObjectBasePrivate::appendChild(QQmlListProperty<QObject> *list, QObject *objectChild)
{
    QNativeQObjectBase *parent = qobject_cast<QNativeQObjectBase *>(list->object);
    QNativeQObjectBase *child = qobject_cast<QNativeQObjectBase *>(objectChild);
    child->setParent(parent);
    // Upon construction, the parent (self) might have be set from QObject private
    // constructor, which means that the QChildEvent was sendt before the child
    // was fully constructed (as is correct, according to childEvent docs). So
    // we sync here an extra time to work around that case.
    //child->d_func()->syncPlatformParent();
}

QQmlListProperty<QObject> QNativeQObjectBasePrivate::data()
{
    return QQmlListProperty<QObject>(q_func(), 0, appendChild, 0, 0, 0);
}

bool QNativeQObjectBasePrivate::isComplete()
{
    // todo: hook up to QQmlParserStatus
   return true;
}

QNativeQObjectBase::QNativeQObjectBase(QNativeQObjectBase *parent)
    : QObject(parent)
{
}

QNativeQObjectBase::QNativeQObjectBase(QNativeQObjectBasePrivate &dd, QNativeQObjectBase *parent)
    : QObject(dd, parent)
{
}

QNativeQObjectBase::~QNativeQObjectBase()
{
    // delete children in m_data?
}

#include "moc_qnativeqobjectbase.cpp"

QT_END_NAMESPACE
