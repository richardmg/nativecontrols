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

#include <QtUniUIKitControls/quniuikitbutton.h>
#include <QtUniUIKitControls/private/quniuikitbutton_p.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

@interface QUniUIKitButtonDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniUIKitButtonPrivate) *_button;
}
@end

@implementation QUniUIKitButtonDelegate

-(id)initWithQUniUIKitButtonPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitButtonPrivate) *)button
{
    self = [super init];
    if (self) {
        _button = button;
    }

    return self;
}

-(void)onClicked
{
    emit _button->q_func()->clicked();
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitButtonPrivate::QUniUIKitButtonPrivate(int version)
    : QUniUIKitControlPrivate(version)
    , m_delegate(nullptr)
    , m_buttonType(QUniUIKitButton::ButtonTypeCustom)
{
    // Avoid mapping enum values directly to UIKit enum values in the enum
    // declaration, since then we require all users of the header file to compile as obj-c++.
    Q_ASSERT(int(QUniUIKitButton::ButtonTypeCustom) == int(UIButtonTypeCustom));
}

QUniUIKitButtonPrivate::~QUniUIKitButtonPrivate()
{
    [m_delegate release];
}

void QUniUIKitButtonPrivate::createNSObject()
{
    UIButton *uiButton = [UIButton buttonWithType:m_buttonType.staticCast<UIButtonType>()];
    [uiButton setTitleColor:uiButton.tintColor forState:UIControlStateNormal];
    [uiButton sizeToFit];

    m_delegate = [[QUniUIKitButtonDelegate alloc] initWithQUniUIKitButtonPrivate:this];
    [uiButton addTarget:m_delegate action:@selector(onClicked) forControlEvents:UIControlEventTouchUpInside];
    [uiButton autorelease];
    setNSObject(uiButton);
}

void QUniUIKitButtonPrivate::setNSObject(NSObject *nsObject)
{
    QUniUIKitControlPrivate::setNSObject(nsObject);
    syncText();
}

UIButton *QUniUIKitButtonPrivate::uiButton() const
{
    return static_cast<UIButton *>(view());
}

void QUniUIKitButtonPrivate::syncText()
{
    [uiButton() setTitle:m_text.staticCast<QString>().toNSString() forState:UIControlStateNormal];
    updateIntrinsicContentSize();
}

void QUniUIKitButtonPrivate::syncButtonType()
{
    qWarning("Button: buttonType cannot change once the backing UIButton has been created!");
}

QUniUIKitButton::QUniUIKitButton(QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitButtonPrivate(), parent)
{
}

QUniUIKitButton::QUniUIKitButton(const QString &text, QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitButtonPrivate(), parent)
{
    setText(text);
}

QUniUIKitButton::QUniUIKitButton(QUniUIKitButtonPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitControl(dd, parent)
{
}

QUniUIKitButton::~QUniUIKitButton()
{
}

UIButton *QUniUIKitButton::uiButtonHandle()
{
    return d_func()->uiButton();
}

SYNTHESIZE_QPROPERTY_CACHED(text, Text, QString, QUniUIKitButton)
SYNTHESIZE_QPROPERTY_CACHED(buttonType, ButtonType, QUniUIKitButton::ButtonType, QUniUIKitButton)

#include "moc_quniuikitbutton.cpp"

QT_END_NAMESPACE

