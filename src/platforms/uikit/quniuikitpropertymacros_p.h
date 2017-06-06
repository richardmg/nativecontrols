/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Templates 2 module of the Qt Toolkit.
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

#ifndef QUNIUIKITPROPERTYMACROS_H
#define QUNIUIKITPROPERTYMACROS_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtUniUIKitControls/private/quniuikitbase_p.h>

// We often expect properties in QML to contain functions that
// we can forward calls to when UIKit query our delegates for
// information. But since it's so common to assign values directly
// to properties in QML, we need to check for this as well.
// To avoid reimplement the same pattern over and over, we
// encapsulate this into a set of helper macros.
#define GET_PROPERTY_QJSVALUE_BEGIN(PROPERTY_NAME, QT_TYPE, FIRST_ARG) \
    Q_AND_D_NSOBJECT2(QT_TYPE, self); \
    QJSValue property = d->PROPERTY_NAME; \
    if (property.isCallable()) { \
        Q_AND_D_NSOBJECT4(QT_TYPE, FIRST_ARG, q##FIRST_ARG, d##FIRST_ARG); \
        QQmlEngine *engine = qmlEngine(q); \
        QJSValueList args; \
        args << engine->newQObject(q##FIRST_ARG);

#define GET_PROPERTY_QJSVALUE_END \
        property = property.call(args); \
    }

// Convenience macro for cases where the QML function
// only takes one argument (the owner of the delegate)
#define GET_PROPERTY_QJSVALUE(PROPERTY_NAME, QT_TYPE, FIRST_ARG) \
    GET_PROPERTY_QJSVALUE_BEGIN(PROPERTY_NAME, QT_TYPE, FIRST_ARG) \
    GET_PROPERTY_QJSVALUE_END

#define SYNTHESIZE_QPROPERTY_QJSVALUE(LOWER, UPPER, CONVERT, CLASS) \
QJSValue CLASS::LOWER() const  { \
    return d_func()->m_##LOWER; \
} \
void CLASS::set##UPPER(const QJSValue &value) { \
    Q_D(CLASS); \
    auto prevValue = d->m_##LOWER.CONVERT(); \
    d->m_##LOWER = value; \
    if (prevValue != value.CONVERT()) \
        emit LOWER##Changed(this); \
}

#define SYNTHESIZE_QPROPERTY_GETTER_CACHED(LOWER, TYPE, CLASS) \
TYPE CLASS::LOWER() const \
{ \
    return d_func()->m_##LOWER; \
}

#define SYNTHESIZE_QPROPERTY_SETTER_CACHED(LOWER, UPPER, TYPE, CLASS) \
void CLASS::set##UPPER(const TYPE &newValue) \
{ \
    Q_D(CLASS); \
    if (d->m_##LOWER == newValue) \
        return; \
\
    d->m_##LOWER = newValue; \
    if (!d->isNSObjectCreated()) \
        return; \
\
    d->sync##UPPER(); \
}

#define SYNTHESIZE_QPROPERTY_CACHED(LOWER, UPPER, TYPE, CLASS) \
SYNTHESIZE_QPROPERTY_GETTER_CACHED(LOWER, TYPE, CLASS) \
SYNTHESIZE_QPROPERTY_SETTER_CACHED(LOWER, UPPER, TYPE, CLASS)

#define SYNTHESIZE_QPROPERTY_GETTER_CACHED_POINTER(LOWER, TYPE, CLASS) \
TYPE *CLASS::LOWER() const \
{ \
    return d_func()->m_##LOWER; \
}

#define SYNTHESIZE_QPROPERTY_SETTER_CACHED_POINTER(LOWER, UPPER, TYPE, CLASS) \
void CLASS::set##UPPER(TYPE *newValue) \
{ \
    Q_D(CLASS); \
    if (d->m_##LOWER == newValue) \
        return; \
\
    d->m_##LOWER = newValue; \
    if (!d->isNSObjectCreated()) \
        return; \
\
    d->sync##UPPER(); \
    emit LOWER##Changed(newValue); \
}

#define SYNTHESIZE_QPROPERTY_CACHED_POINTER(LOWER, UPPER, TYPE, CLASS) \
SYNTHESIZE_QPROPERTY_GETTER_CACHED_POINTER(LOWER, TYPE, CLASS) \
SYNTHESIZE_QPROPERTY_SETTER_CACHED_POINTER(LOWER, UPPER, TYPE, CLASS)

#endif // QUNIUIKITPROPERTYMACROS_H
