/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native UIKit Controls module of the Qt Toolkit.
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

#include <UIKit/UIKit.h>
#include <objc/runtime.h>

#include <QtCore>

#include <QtUniUIKitControls/quniuikitbase.h>
#include <QtUniUIKitControls/private/quniuikitbase_p.h>

QT_BEGIN_NAMESPACE

static const char *kIdAssociatedQObject = "qobject";

void qt_setAssociatedQObject(NSObject *nsObject, QObject *qObject)
{
    objc_setAssociatedObject(nsObject, kIdAssociatedQObject, id(qObject), OBJC_ASSOCIATION_ASSIGN);
}

QObject *qt_getAssociatedQObject(NSObject *nsObject)
{
    id ref = objc_getAssociatedObject(nsObject, kIdAssociatedQObject);
    return static_cast<QObject *>(ref);
}

QUniUIKitBasePrivate::QUniUIKitBasePrivate(int version)
    : QUniUIKitQmlBasePrivate(version)
    , m_nsObject(nullptr)
#ifdef QT_DEBUG
    , m_createNSObjectRecursionGuard(false)
#endif
{
}

QUniUIKitBasePrivate::~QUniUIKitBasePrivate()
{
    [m_nsObject release];
}

NSObject *QUniUIKitBasePrivate::nsObject() const
{
    if (!m_nsObject) {
        QUniUIKitBasePrivate *self = const_cast<QUniUIKitBasePrivate *>(this);
#ifdef QT_DEBUG
        // Check that we don't end up calling nsObject() from createNSObject(). This can
        // easily happen if we e.g create several UIViews inside createNSObject, and
        // construct parent-child relationships. The solution is to call setNSObject
        // early on from within createNSObject, before creating child views.
        Q_ASSERT(!m_createNSObjectRecursionGuard);
        self->m_createNSObjectRecursionGuard = true;
#endif
        // The common case should be that we enter this block to lazy create the NSObject
        // we wrap when someone actually needs it. This usually happens when properties
        // are assigned values, or the object becomes a parent of some other object, or
        // upon componentComplete. Only the leaf class will be responsible for creating the
        // NSObject, but all it's anchestors should afterwards get a call to setNSObject
        // so that they can initialize and sync their own local properties. For NSObjects
        // that requires property values to be known already in the constructor, it might
        // be necessary to delay creating the NSObject until all properties have been assigned
        // values. For those cases 'setNSObject' normally happens upon 'componentComplete'.
        // For subclasses that adopts an already existing NSObject, e.g to wrap read-only
        // UIView properties in other UIViews (like UITableViewCell.label), calling
        // setNSObject explicit early on, perhaps during construction, might be necessary.
        self->createNSObject();
        Q_ASSERT(m_nsObject);
    }
    return m_nsObject;
}

void QUniUIKitBasePrivate::setNSObject(NSObject *nsObject)
{
    // Currently we only support setting a backend nsobject once. If this needs to
    // change at on point, logic must be implemented, not only for releasing the old
    // backend objects, but also for reverting parent-child relationships, and ensure
    // that any associations in UIKit (including those that might exist between the
    // native controls) will be dealt with.
    Q_ASSERT(nsObject);
    Q_ASSERT_X(!m_nsObject, Q_FUNC_INFO, "setNSObject should only be called once");
    m_nsObject = [nsObject retain];
    qt_setAssociatedQObject(m_nsObject, q_func());
}

QUniUIKitBase::QUniUIKitBase(QUniUIKitBase *parent)
    :  QUniUIKitQmlBase(*new QUniUIKitBasePrivate(), parent)
{
}

QUniUIKitBase::QUniUIKitBase(QUniUIKitBasePrivate &dd, QUniUIKitBase *parent)
    :  QUniUIKitQmlBase(dd, parent)
{
}

QUniUIKitBase::~QUniUIKitBase()
{
}

void QUniUIKitBase::setParent(QUniUIKitBase *parentBase)
{
    if (parentBase == parent())
        return;

    QUniUIKitQmlBase::setParent(parentBase);
    emit parentChanged(parentBase);
}

QUniUIKitBase *QUniUIKitBase::parentBase()
{
    return qobject_cast<QUniUIKitBase *>(parent());
}

void QUniUIKitBase::componentComplete()
{
    (void)d_func()->nsObject();
}

#include "moc_quniuikitbase.cpp"

QT_END_NAMESPACE
