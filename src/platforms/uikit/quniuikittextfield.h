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

#ifndef QUNIUIKITTEXTFIELD_H
#define QUNIUIKITTEXTFIELD_H

#include <QtUniUIKitControls/quniuikitcontrol.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTextFieldPrivate;
class QUniUIKitTextFieldDelegate;
Q_FORWARD_DECLARE_OBJC_CLASS(UITextField);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitTextField : public QUniUIKitControl
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString placeholder READ placeholder WRITE setPlaceholder NOTIFY placeholderChanged)
    Q_PROPERTY(QUniUIKitTextFieldDelegate *delegate READ delegate WRITE setDelegate NOTIFY delegateChanged)

public:
    QUniUIKitTextField(QUniUIKitBase *parent = nullptr);
    QUniUIKitTextField(const QString &text, QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitTextField();

    UITextField *uiTextFieldHandle();

    QString text() const;
    void setText(const QString &text);

    QString placeholder() const;
    void setPlaceholder(const QString &placeholder);

    QUniUIKitTextFieldDelegate *delegate() const;
    void setDelegate(QUniUIKitTextFieldDelegate *delegate);

Q_SIGNALS:
    void textChanged(const QString &text);
    void placeholderChanged(const QString &placeholder);
    void delegateChanged(QUniUIKitTextFieldDelegate *delegate);

protected:
    QUniUIKitTextField(QUniUIKitTextFieldPrivate &dd, QUniUIKitBase *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(QUniUIKitTextField)
    Q_DISABLE_COPY(QUniUIKitTextField)
};

QT_END_NAMESPACE
#endif // QUNIUIKITTEXTFIELD_H
