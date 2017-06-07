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

#include <QtUniUIKitControls/quniuikittextfield.h>
#include <QtUniUIKitControls/private/quniuikittextfield_p.h>
#include <QtUniUIKitControls/quniuikittextfielddelegate.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

QUniUITextFieldStaticDelegate *QUniUIKitTextFieldPrivate::s_delegate = nullptr;

@interface QUniUITextFieldStaticDelegate : NSObject
@end

@implementation QUniUITextFieldStaticDelegate

-(id)init
{
    self = [super init];
    if (self) {
        [[NSNotificationCenter defaultCenter]
            addObserver:self
            selector:@selector(textFieldDidChange:)
            name:UITextFieldTextDidChangeNotification object:nil];
    }

    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter]
        removeObserver:self
        name:UITextFieldTextDidChangeNotification object:nil];
    [super dealloc];
}

- (void)textFieldDidChange:(NSNotification *)notification
{
    Q_AND_D_NSOBJECT2(QUniUIKitTextField, notification.object);
    d->updateIntrinsicContentSize();
    emit q->textChanged(q->text());
}

@end

// --------------------------------------------------------------------------

@interface QUniUITextField : UITextField
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>
@end

@implementation QUniUITextField
#define QUNI_INTERFACE_IMPLEMENTATION
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>
@end

// --------------------------------------------------------------------------

QT_BEGIN_NAMESPACE

QUniUIKitTextFieldPrivate::QUniUIKitTextFieldPrivate(int version)
    : QUniUIKitControlPrivate(version)
    , m_delegate(nullptr)
{
    if (!s_delegate)
        s_delegate = [QUniUITextFieldStaticDelegate new];
}

QUniUIKitTextFieldPrivate::~QUniUIKitTextFieldPrivate()
{
}

UITextField *QUniUIKitTextFieldPrivate::textField() const
{
    return static_cast<UITextField *>(nsObject());
}

void QUniUIKitTextFieldPrivate::createNSObject()
{
    setNSObject([[[QUniUITextField alloc] init] autorelease]);
}

QUniUIKitTextField::QUniUIKitTextField(QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitTextFieldPrivate(), parent)
{
}

QUniUIKitTextField::QUniUIKitTextField(const QString &text, QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitTextFieldPrivate(), parent)
{
    setText(text);
}

QUniUIKitTextField::QUniUIKitTextField(QUniUIKitTextFieldPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitControl(dd, parent)
{
}

QUniUIKitTextField::~QUniUIKitTextField()
{
}

UITextField *QUniUIKitTextField::uiTextFieldHandle()
{
    return d_func()->textField();
}

SYNTHESIZE_QPROPERTY_CALLBACK_QSTRING(text, Text, textField(), QUniUIKitTextField)
SYNTHESIZE_QPROPERTY_INTRINSIC_QSTRING(placeholder, Placeholder, textField(), QUniUIKitTextField)

QUniUIKitTextFieldDelegate *QUniUIKitTextField::delegate() const
{
    return d_func()->m_delegate;
}

void QUniUIKitTextField::setDelegate(QUniUIKitTextFieldDelegate *delegate)
{
    Q_D(QUniUIKitTextField);
    if (d->m_delegate == delegate)
        return;

    d->m_delegate = delegate;
    uiTextFieldHandle().delegate = static_cast<id<UITextFieldDelegate>>(delegate->uiTextFieldDelegateHandle());
    emit delegateChanged(delegate);
}

#include "moc_quniuikittextfield.cpp"
