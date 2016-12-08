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

#ifndef QMLNATIVECONTROL_H
#define QMLNATIVECONTROL_H

#include <QtCore/qobject.h>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqmlparserstatus.h>

QT_BEGIN_NAMESPACE

class QmlNativeControl : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> children READ children)

    Q_CLASSINFO("DefaultProperty", "children")
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit QmlNativeControl(QObject *parent = nullptr);
    virtual ~QmlNativeControl() {};

    virtual void classBegin() override {};
    virtual void componentComplete() override {};

    QQmlListProperty<QObject> children();

private:
    QList<QObject *> m_children;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QmlNativeControl)

#endif // QMLNATIVECONTROL_H
