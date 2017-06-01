/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Copyright (C) 2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Marc Mutz <marc.mutz@kdab.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt QML IOS module of the Qt Toolkit.
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

#ifndef QUNIUIKITOPTIONAL_P_H
#define QUNIUIKITOPTIONAL_P_H

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

#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

template <typename T>
class QUniUIKitOptional
{
public:
    QUniUIKitOptional() : value(), m_isExplicit(false) {}
    explicit QUniUIKitOptional(const T &t) : value(t), m_isExplicit(true) {}
    explicit QUniUIKitOptional(T &&t) : value(std::move(t)), m_isExplicit(true) {}
    QUniUIKitOptional &operator=(const T &o) { value = o; m_isExplicit = true; return *this; }

    void reset(const T &o) { value = o; m_isExplicit = false; }

    operator T&() Q_DECL_NOTHROW { return value; }
    operator const T&() const Q_DECL_NOTHROW { return value; }

    bool isNull() const Q_DECL_NOTHROW { return !m_isExplicit; }
    bool isNotNull() const Q_DECL_NOTHROW { return m_isExplicit; }
    bool hasExplicitValue() const Q_DECL_NOTHROW { return m_isExplicit; }

    template <typename C>
    C staticCast() { return static_cast<C>(value); }

protected:
    T value;
    bool m_isExplicit;
};

template <typename T>
class QUniUIKitFallibleOptional : public QUniUIKitOptional<T>
{
public:
    // This subclass will remember all explicit assignments, but at the same
    // time, allow you to set a different (temporary) read value. The reason
    // for this need is that sometimes QML will assign a value that a component
    // for some reason currently cannot accept, but that might end up valid later
    // when other properties change.
    // E.g setting a value for a slider that is outside its range might fail, and
    // force a different (read) value to be used. But if the range later
    // change, this optional rememebers the original write value, which gives
    // you a chance to re-set it once more.
    QUniUIKitFallibleOptional() : QUniUIKitOptional<T>(), m_writeValue() {}
    explicit QUniUIKitFallibleOptional(const T &t) : QUniUIKitOptional<T>(t), m_writeValue(t) {}
    explicit QUniUIKitFallibleOptional(T &&t) : QUniUIKitOptional<T>(t), m_writeValue(t) {}

    QUniUIKitFallibleOptional &operator=(const T &o)
    {
        // Using the assigment operator is seen as an explicit assignment. In
        // that case, we update both the read-, and write (t) value.
        m_writeValue = o;
        QUniUIKitOptional<T>::operator=(o);
        return *this;
    }

    void reset(const T &o)
    {
        QUniUIKitOptional<T>::reset(o);
        m_writeValue = o;
    }

    void setReadValue(const T &o) {
        // Setting a read value will not affect whether or
        // not this optional has an explicit assignment.
        this->value = o;
    }

    T writeValue() const { return m_writeValue; }
    T readValue() const { return this->value; }

protected:
    T m_writeValue;
};

template <typename T>
inline bool operator==(const QUniUIKitOptional<T> &lhs, const QUniUIKitOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(static_cast<const T&>(lhs) == static_cast<const T&>(rhs)))
{ return lhs.isNull() == rhs.isNull() && !lhs.isNull() && static_cast<const T&>(lhs) == static_cast<const T&>(rhs); }

template <typename T>
inline bool operator==(const QUniUIKitOptional<T> &lhs, const T &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(static_cast<const T&>(lhs) == rhs))
{ return !lhs.isNull() && static_cast<const T&>(lhs) == rhs; }

template <typename T>
inline bool operator==(const T &lhs, const QUniUIKitOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == static_cast<const T&>(rhs)))
{ return !rhs.isNull() && lhs == static_cast<const T&>(rhs); }

template <typename T>
inline bool operator!=(const QUniUIKitOptional<T> &lhs, const QUniUIKitOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == rhs))
{ return !operator==(lhs, rhs); }

template <typename T>
inline bool operator!=(const QUniUIKitOptional<T> &lhs, const T &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == rhs))
{ return !operator==(lhs, rhs); }

template <typename T>
inline bool operator!=(const T &lhs, const QUniUIKitOptional<T> &rhs)
    Q_DECL_NOEXCEPT_EXPR(noexcept(lhs == rhs))
{ return !operator==(lhs, rhs); }

QT_END_NAMESPACE

#endif // QUNIUIKITOPTIONAL_P_H
