/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#ifndef QNATIVETEXTFIELD_H
#define QNATIVETEXTFIELD_H

#include <QtNativeControls/qnativecontrol.h>
#include <QtNativeControls/qnativecontrolsglobal.h>

QT_BEGIN_NAMESPACE

class QNativeTextFieldPrivate;
class QNativePlatformTextField;

class Q_NATIVECONTROLS_EXPORT QNativeTextField : public QNativeControl
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)

public:
    explicit QNativeTextField(QNativeBase *parent = nullptr);
    explicit QNativeTextField(const QString &text, QNativeBase *parent = nullptr);
    virtual ~QNativeTextField();

    QString text();
    void setText(const QString &text);

    QString placeholderText();
    void setPlaceholderText(const QString &placeholderText);

Q_SIGNALS:
    void textChanged(const QString &text);
    void placeholderTextChanged(const QString &placeholderText);

protected:
    QNativeTextField(QNativeTextFieldPrivate &dd, QNativeBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QNativeTextField)
    Q_DISABLE_COPY(QNativeTextField)
};

QT_END_NAMESPACE

#endif // QNATIVETEXTFIELD_H
