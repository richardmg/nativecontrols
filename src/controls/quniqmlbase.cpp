/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native Controls module of the Qt Toolkit.
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

#include <QtUniControls/quniqmlbase.h>
#include <QtUniControls/private/quniqmlbase_p.h>
#include <QtUniControls/private/qunibase_p.h>

QT_BEGIN_NAMESPACE

QUniQmlBasePrivate::QUniQmlBasePrivate(int version)
    : QObjectPrivate(version)
{
}

QUniQmlBasePrivate::~QUniQmlBasePrivate()
{
}

void QUniQmlBasePrivate::appendChild(QQmlListProperty<QObject> *list, QObject *child)
{
    // Note that QtDeclarative undermines QObject::setParent, meaning that we
    // don't get a QChildEvent when a qml object becomes a parent of another
    // qml object. 'appendChild' is the only callback we get when the parent changes.
    QObject *qparent = list->object;
    QUniBase *quniParent = static_cast<QUniBase *>(qparent);
    QUniBase *quniChild = qobject_cast<QUniBase *>(child);

    if (quniChild) {
        quniChild->setParent(quniParent);
        static_cast<QUniBasePrivate *>(QObjectPrivate::get(quniChild))->syncPlatformParent();
    } else {
        // The child doesn't belong to QUni. Check
        // if the platform understands how to parent it
        if (!quniParent->addNativeChild(child)) {
            // ...otherwise we fall back to normal QObject parenting
            child->setParent(qparent);
        }
    }
}

QQmlListProperty<QObject> QUniQmlBasePrivate::data()
{
    return QQmlListProperty<QObject>(q_func(), 0, appendChild, 0, 0, 0);
}

bool QUniQmlBasePrivate::isComplete()
{
    // todo: hook up to QQmlParserStatus
   return true;
}

QUniQmlBase::QUniQmlBase(QUniQmlBase *parent)
    : QObject(parent)
{
}

QUniQmlBase::QUniQmlBase(QUniQmlBasePrivate &dd, QUniQmlBase *parent)
    : QObject(dd, parent)
{
}

QUniQmlBase::~QUniQmlBase()
{
    // delete children in m_data?
}

#include "moc_quniqmlbase.cpp"

QT_END_NAMESPACE
