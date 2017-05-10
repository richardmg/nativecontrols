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
#include <QtUniUIKitControls/private/quniuikittextfielddelegate_p.h>

#define DELEGATE_GETTER_AND_SETTER(NAME) \
QJSValue QUniUIKitTextFieldDelegate::textField##NAME() const  {  return d_func()->m_textField##NAME; } \
void QUniUIKitTextFieldDelegate::setTextField##NAME(const QJSValue &value) { d_func()->m_textField##NAME = value; }

#define DELEGATE_METHOD_BOOL(NAME) \
- (BOOL)textField##NAME:(UITextField *)textField \
{ \
    QUniUIKitTextField *qtextField = static_cast<QUniUIKitTextField *>(qt_getAssociatedQObject(textField)); \
    if (!qtextField) \
        return YES; \
    QJSValue jsFunction = _delegatePrivate->m_textField##NAME; \
    if (jsFunction.isUndefined()) \
        return YES; \
    if (!jsFunction.isCallable()) { \
        qWarning("TextFieldDelegate: property 'textField" #NAME "' doesn't point to a JS function"); \
        return YES; \
    } \
    QJSValue jsTextField = qmlEngine(qtextField)->newQObject(qtextField); \
    QJSValue returnValue = jsFunction.call(QJSValueList() << jsTextField); \
    if (!returnValue.isBool()) { \
        qWarning("TextFieldDelegate: property 'textField" #NAME "' doesn't return a bool"); \
        return YES; \
    } \
    return returnValue.toBool(); \
}

#define DELEGATE_METHOD_VOID(NAME) \
- (void)textField##NAME:(UITextField *)textField \
{ \
    QUniUIKitTextField *qtextField = static_cast<QUniUIKitTextField *>(qt_getAssociatedQObject(textField)); \
    if (!qtextField) \
        return; \
    QJSValue jsFunction = _delegatePrivate->m_textField##NAME; \
    if (jsFunction.isUndefined()) \
        return; \
    if (!jsFunction.isCallable()) { \
        qWarning("TextFieldDelegate: property 'textField" #NAME "' doesn't point to a JS function"); \
        return; \
    } \
    QJSValue jsTextField = qmlEngine(qtextField)->newQObject(qtextField); \
    jsFunction.call(QJSValueList() << jsTextField); \
}

@interface QUniUITextFieldDelegate : NSObject <UITextFieldDelegate>
{
    QT_PREPEND_NAMESPACE(QUniUIKitTextFieldDelegatePrivate) *_delegatePrivate;
}
@end

@implementation QUniUITextFieldDelegate

-(id)initWithQUniUIKitTextFieldDelegatePrivate:(QT_PREPEND_NAMESPACE(QUniUIKitTextFieldDelegatePrivate) *)delegatePrivate
{
    self = [self init];
    if (self) {
        _delegatePrivate = delegatePrivate;
    }

    return self;
}

DELEGATE_METHOD_BOOL(ShouldBeginEditing)
DELEGATE_METHOD_VOID(DidBeginEditing)
DELEGATE_METHOD_BOOL(ShouldEndEditing)
DELEGATE_METHOD_VOID(DidEndEditing)
DELEGATE_METHOD_BOOL(ShouldClear)
DELEGATE_METHOD_BOOL(ShouldReturn)

@end

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

DELEGATE_GETTER_AND_SETTER(ShouldBeginEditing)
DELEGATE_GETTER_AND_SETTER(DidBeginEditing)
DELEGATE_GETTER_AND_SETTER(ShouldEndEditing)
DELEGATE_GETTER_AND_SETTER(DidEndEditing)
DELEGATE_GETTER_AND_SETTER(ShouldClear)
DELEGATE_GETTER_AND_SETTER(ShouldReturn)

#include "moc_quniuikittextfielddelegate.cpp"

QT_END_NAMESPACE
