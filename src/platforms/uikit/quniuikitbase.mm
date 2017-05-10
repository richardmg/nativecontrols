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
#ifdef QT_DEBUG
    , m_createNSObjectRecursionGuard(false)
#endif
{
}

QUniUIKitBasePrivate::~QUniUIKitBasePrivate()
{
    [m_nsObject release];
}

NSObject *QUniUIKitBasePrivate::nsObject()
{
    if (!m_nsObject) {
#ifdef QT_DEBUG
        // Check that we don't end up calling nsObject() from createNSObject(). This can
        // easily happen if we e.g create several UIViews inside createNSObject, and
        // construct parent-child relationships. The solution is to call setNSObject
        // early on from within createNSObject, before creating child views.
        Q_ASSERT(!m_createNSObjectRecursionGuard);
        m_createNSObjectRecursionGuard = true;
#endif
        // The common case should be that we enter this block to lazy create the UIView
        // we wrap when someone actually needs it (which is usually when properties
        // are assigned values, or another QUniUIKitView is set as child). But for
        // subclasses that adopts an already existing NSObject, e.g to wrap read-only
        // UIView properties in other UIViews (like UITableViewCell.label), calling
        // setNSObject early on is necessary.
        createNSObject();
        Q_ASSERT(m_nsObject);
    }
    return m_nsObject;
}

NSObject *QUniUIKitBasePrivate::nsObject() const
{
    return const_cast<QUniUIKitBasePrivate *>(this)->nsObject();
}

void QUniUIKitBasePrivate::setNSObject(NSObject *nsObject)
{
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

#include "moc_quniuikitbase.cpp"

QT_END_NAMESPACE
