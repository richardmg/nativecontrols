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
    GET_PROPERTY_QJSVALUE(_delegatePrivate->m_textField##NAME, QUniUIKitTextField, textField) \
    return property.isUndefined() ? YES : property.toBool(); \
}

#define QUNIUITEXTFIELDDELEGATE_METHOD_EMIT(NAME) \
- (void)textField##NAME:(UITextField *)textField \
{ \
    QUniUIKitTextField *qtextField = static_cast<QUniUIKitTextField *>(qt_getAssociatedQObject(textField)); \
    emit _delegatePrivate->q_func()->textField##NAME(qtextField); \
}

// --------------------------------------------------------------------------

@interface QUniUITextFieldDelegate : NSObject <UITextFieldDelegate>
{
    QT_PREPEND_NAMESPACE(QUniUIKitTextFieldDelegatePrivate) *_delegatePrivate;
}
@end

@implementation QUniUITextFieldDelegate

-(id)initWithQUniUIKitTextFieldDelegatePrivate:(QT_PREPEND_NAMESPACE(QUniUIKitTextFieldDelegatePrivate) *)delegatePrivate
{
    self = [super init];
    if (self) {
        _delegatePrivate = delegatePrivate;
    }

    return self;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    GET_PROPERTY_QJSVALUE_BEGIN(_delegatePrivate->m_textFieldShouldChangeCharactersInRange, QUniUIKitTextField, textField)
        QUniUIKitRange qrange(range.location, range.length);
        args << engine->newQObject(&qrange);
        args << engine->toScriptValue(QString::fromNSString(string));
    GET_PROPERTY_QJSVALUE_END
    return property.isUndefined() ? true : property.toBool();
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    // We special case textFieldShouldReturn since we want to emit a textFieldDidReturn as well
    GET_PROPERTY_QJSVALUE(_delegatePrivate->m_textFieldShouldReturn, QUniUIKitTextField, textField)
    bool shouldReturn = property.isUndefined() ? true : property.toBool();
    if (shouldReturn)
        emit _delegatePrivate->q_func()->textFieldDidReturn(associatedQObject);
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
    , m_delegate([[QUniUITextFieldDelegate alloc] initWithQUniUIKitTextFieldDelegatePrivate:this])
{
}

QUniUIKitTextFieldDelegatePrivate::~QUniUIKitTextFieldDelegatePrivate()
{
    [m_delegate release];
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
    return d_func()->m_delegate;
}

IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTextFieldDelegate, textFieldShouldBeginEditing, setTextFieldShouldBeginEditing, toBool)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTextFieldDelegate, textFieldShouldEndEditing, setTextFieldShouldEndEditing, toBool)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTextFieldDelegate, textFieldShouldClear, setTextFieldShouldClear, toBool)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTextFieldDelegate, textFieldShouldReturn, setTextFieldShouldReturn, toBool)
IMPLEMENT_PROPERTY_QJSVALUE(QUniUIKitTextFieldDelegate, textFieldShouldChangeCharactersInRange, setTextFieldShouldChangeCharactersInRange, toBool)

#include "moc_quniuikittextfielddelegate.cpp"

QT_END_NAMESPACE
