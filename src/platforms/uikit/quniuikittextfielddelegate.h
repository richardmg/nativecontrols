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

#ifndef QUNIUIKITTEXTFIELDDELEGATE_H
#define QUNIUIKITTEXTFIELDDELEGATE_H

#include <QtQml/qjsvalue.h>
#include <QtUniUIKitControls/quniuikitbase.h>

QT_BEGIN_NAMESPACE

class QUniUIKitTextFieldDelegatePrivate;
class QUniUIKitTextField;
Q_FORWARD_DECLARE_OBJC_CLASS(NSObject);
Q_FORWARD_DECLARE_OBJC_CLASS(UITextFieldDelegate);

class Q_UNIUIKITCONTROLS_EXPORT QUniUIKitTextFieldDelegate : public QUniUIKitBase
{
    Q_OBJECT
    Q_PROPERTY(QJSValue textFieldShouldBeginEditing READ textFieldShouldBeginEditing WRITE setTextFieldShouldBeginEditing NOTIFY textFieldShouldBeginEditingChanged)
    Q_PROPERTY(QJSValue textFieldShouldEndEditing READ textFieldShouldEndEditing WRITE setTextFieldShouldEndEditing NOTIFY textFieldShouldEndEditingChanged)
    Q_PROPERTY(QJSValue textFieldShouldClear READ textFieldShouldClear WRITE setTextFieldShouldClear NOTIFY textFieldShouldClearChanged)
    Q_PROPERTY(QJSValue textFieldShouldReturn READ textFieldShouldReturn WRITE setTextFieldShouldReturn NOTIFY textFieldShouldReturnChanged)
    Q_PROPERTY(QJSValue textFieldShouldChangeCharactersInRange READ textFieldShouldChangeCharactersInRange WRITE setTextFieldShouldChangeCharactersInRange NOTIFY textFieldShouldChangeCharactersInRangeChanged)

public:
    QUniUIKitTextFieldDelegate(QUniUIKitBase *parent = nullptr);
    virtual ~QUniUIKitTextFieldDelegate();

    NSObject *uiTextFieldDelegateHandle() const;

    QJSValue textFieldShouldBeginEditing() const;
    void setTextFieldShouldBeginEditing(const QJSValue &value);

    QJSValue textFieldShouldEndEditing() const;
    void setTextFieldShouldEndEditing(const QJSValue &value);

    QJSValue textFieldShouldClear() const;
    void setTextFieldShouldClear(const QJSValue &value);

    QJSValue textFieldShouldReturn() const;
    void setTextFieldShouldReturn(const QJSValue &value);

    QJSValue textFieldShouldChangeCharactersInRange() const;
    void setTextFieldShouldChangeCharactersInRange(const QJSValue &value);

Q_SIGNALS:
    void textFieldShouldBeginEditingChanged(QUniUIKitTextFieldDelegate *delegate);
    void textFieldShouldEndEditingChanged(QUniUIKitTextFieldDelegate *delegate);
    void textFieldShouldReturnChanged(QUniUIKitTextFieldDelegate *delegate);
    void textFieldShouldClearChanged(QUniUIKitTextFieldDelegate *delegate);
    void textFieldShouldChangeCharactersInRangeChanged(QUniUIKitTextFieldDelegate *delegate);

    void textFieldDidBeginEditing(QUniUIKitTextField *textField);
    void textFieldDidEndEditing(QUniUIKitTextField *textField);
    void textFieldDidReturn(QUniUIKitTextField *textField);
    void textFieldDidClear(QUniUIKitTextField *textField);

private:
    Q_DECLARE_PRIVATE(QUniUIKitTextFieldDelegate)
    Q_DISABLE_COPY(QUniUIKitTextFieldDelegate)
};

QT_END_NAMESPACE

#endif // QUNIUIKITTEXTFIELDDELEGATE_H
