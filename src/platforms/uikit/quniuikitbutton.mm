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

@interface QUniUIButton : UIButton
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>
@end

@implementation QUniUIButton
#define QUNI_INTERFACE_IMPLEMENTATION
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>

-(void)onClicked
{
    Q_Q_NSOBJECT(QUniUIKitButton);
    emit q->clicked();
}
@end

QT_BEGIN_NAMESPACE

QUniUIKitButtonPrivate::QUniUIKitButtonPrivate(int version)
    : QUniUIKitControlPrivate(version)
    , m_buttonType(QUniUIKitButton::ButtonTypeCustom)
{
    // Avoid mapping enum values directly to UIKit enum values in the enum
    // declaration, since then we require all users of the header file to compile as obj-c++.
    Q_ASSERT(int(QUniUIKitButton::ButtonTypeCustom) == int(UIButtonTypeCustom));
}

QUniUIKitButtonPrivate::~QUniUIKitButtonPrivate()
{
}

void QUniUIKitButtonPrivate::createNSObject()
{
    setNSObject([[QUniUIButton buttonWithType:m_buttonType.staticCast<UIButtonType>()] autorelease]);
}

void QUniUIKitButtonPrivate::setNSObject(NSObject *nsObject)
{
    QUniUIKitControlPrivate::setNSObject(nsObject);

    QUniUIButton *button = static_cast<QUniUIButton *>(nsObject);
    [button addTarget:button action:@selector(onClicked) forControlEvents:UIControlEventTouchUpInside];
    [button setTitleColor:button.tintColor forState:UIControlStateNormal];

    syncText();
}

UIButton *QUniUIKitButtonPrivate::uiButton() const
{
    return static_cast<UIButton *>(view());
}

void QUniUIKitButtonPrivate::syncText()
{
    if (!m_text.hasExplicitValue())
        return;

    [uiButton() setTitle:m_text.staticCast<QString>().toNSString() forState:UIControlStateNormal];
    updateIntrinsicContentSize();
    emit q_func()->textChanged(m_text);
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

