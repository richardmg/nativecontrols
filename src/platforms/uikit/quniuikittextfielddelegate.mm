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

#include <QtCore>
#include <QtQml/qqmlengine.h>

#include <QtUniUIKitControls/quniuikittextfielddelegate.h>
#include <QtUniUIKitControls/quniuikittextfield.h>
#include <QtUniUIKitControls/quniuikitindexpath.h>
#include <QtUniUIKitControls/quniuikittableviewcell.h>
#include <QtUniUIKitControls/quniuikitrange.h>
#include <QtUniUIKitControls/private/quniuikittextfielddelegate_p.h>
#include <QtUniUIKitControls/private/quniuikittextfield_p.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

#define QUNIUITEXTFIELDDELEGATE_METHOD_BOOL(NAME) \
- (BOOL)textField##NAME:(UITextField *)textField \
{ \
    GET_PROPERTY_QJSVALUE(m_textField##NAME, QUniUIKitTextFieldDelegate, textField) \
    return property.isUndefined() ? YES : property.toBool(); \
}

#define QUNIUITEXTFIELDDELEGATE_METHOD_EMIT(NAME) \
- (void)textField##NAME:(UITextField *)textField \
{ \
    Q_Q_NSOBJECT2(QUniUIKitTextField, textField); \
    emit q->delegate()->textField##NAME(q); \
}

// --------------------------------------------------------------------------

@interface QUniUITextFieldDelegate : NSObject <UITextFieldDelegate>
@property (nonatomic, readwrite) QUniUIKitBase *q;
@end

@implementation QUniUITextFieldDelegate

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    GET_PROPERTY_QJSVALUE_BEGIN(m_textFieldShouldChangeCharactersInRange, QUniUIKitTextFieldDelegate, textField)
        QUniUIKitRange qrange(range.location, range.length);
        args << engine->newQObject(&qrange);
        args << engine->toScriptValue(QString::fromNSString(string));
    GET_PROPERTY_QJSVALUE_END
    return property.isUndefined() ? true : property.toBool();
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    // We special case textFieldShouldReturn since we want to emit a textFieldDidReturn as well
    GET_PROPERTY_QJSVALUE(m_textFieldShouldReturn, QUniUIKitTextFieldDelegate, textField)
    bool shouldReturn = property.isUndefined() ? true : property.toBool();
    if (shouldReturn) {
        Q_AND_D_NSOBJECT4(QUniUIKitTextField, textField, qtextField, dtextField);
        emit q->textFieldDidReturn(qtextField);
    }
    return shouldReturn;
}

QUNIUITEXTFIELDDELEGATE_METHOD_BOOL(ShouldBeginEditing)
QUNIUITEXTFIELDDELEGATE_METHOD_BOOL(ShouldEndEditing)
QUNIUITEXTFIELDDELEGATE_METHOD_BOOL(ShouldClear)
QUNIUITEXTFIELDDELEGATE_METHOD_EMIT(DidBeginEditing)
QUNIUITEXTFIELDDELEGATE_METHOD_EMIT(DidEndEditing)

@end

// --------------------------------------------------------------------------

QT_BEGIN_NAMESPACE

QUniUIKitTextFieldDelegatePrivate::QUniUIKitTextFieldDelegatePrivate(int version)
    : QUniUIKitBasePrivate(version)
{
}

QUniUIKitTextFieldDelegatePrivate::~QUniUIKitTextFieldDelegatePrivate()
{
}

void QUniUIKitTextFieldDelegatePrivate::createNSObject()
{
    setNSObject([[QUniUITextFieldDelegate new] autorelease]);
}

QUniUIKitTextFieldDelegate::QUniUIKitTextFieldDelegate(QUniUIKitBase *parent)
    : QUniUIKitBase(*new QUniUIKitTextFieldDelegatePrivate(), parent)
{
}

QUniUIKitTextFieldDelegate::~QUniUIKitTextFieldDelegate()
{
}

NSObject *QUniUIKitTextFieldDelegate::uiTextFieldDelegateHandle() const
{
    return d_func()->nsObject();
}

SYNTHESIZE_QPROPERTY_QJSVALUE(textFieldShouldBeginEditing, TextFieldShouldBeginEditing, toBool, QUniUIKitTextFieldDelegate)
SYNTHESIZE_QPROPERTY_QJSVALUE(textFieldShouldEndEditing, TextFieldShouldEndEditing, toBool, QUniUIKitTextFieldDelegate)
SYNTHESIZE_QPROPERTY_QJSVALUE(textFieldShouldClear, TextFieldShouldClear, toBool, QUniUIKitTextFieldDelegate)
SYNTHESIZE_QPROPERTY_QJSVALUE(textFieldShouldReturn, TextFieldShouldReturn, toBool, QUniUIKitTextFieldDelegate)
SYNTHESIZE_QPROPERTY_QJSVALUE(textFieldShouldChangeCharactersInRange, TextFieldShouldChangeCharactersInRange, toBool, QUniUIKitTextFieldDelegate)

#include "moc_quniuikittextfielddelegate.cpp"

QT_END_NAMESPACE
