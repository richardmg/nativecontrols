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

@interface QUniUIKitTextFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniUIKitTextFieldPrivate) *_textField;
}
@end

@implementation QUniUIKitTextFieldDelegate

-(id)initWithQUniUIKitTextFieldPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitTextFieldPrivate) *)textField
{
    self = [self init];
    if (self) {
        _textField = textField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitTextFieldPrivate::QUniUIKitTextFieldPrivate(int version)
    : QUniUIKitControlPrivate(version)
    , m_delegate(nullptr)
{
}

QUniUIKitTextFieldPrivate::~QUniUIKitTextFieldPrivate()
{
    [m_delegate release];
}

UIView *QUniUIKitTextFieldPrivate::createView()
{
    m_delegate = [[QUniUIKitTextFieldDelegate alloc] initWithQUniUIKitTextFieldPrivate:this];

    UITextField *uiTextField = [[[UITextField alloc] init] autorelease];
    [uiTextField sizeToFit];

    return uiTextField;
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
    Q_D(QUniUIKitTextField);
    [d->m_delegate release];
}

UITextField *QUniUIKitTextField::uiTextFieldHandle()
{
    return static_cast<UITextField *>(d_func()->view());
}

QString QUniUIKitTextField::text()
{
    return QString::fromNSString(uiTextFieldHandle().text);
}

void QUniUIKitTextField::setText(const QString &newText)
{
    if (newText == text())
        return;

    uiTextFieldHandle().text = newText.toNSString();
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

QString QUniUIKitTextField::placeholderText()
{
    return QString::fromNSString(uiTextFieldHandle().placeholder);
}

void QUniUIKitTextField::setPlaceholderText(const QString &newPlaceholderText)
{
    if (newPlaceholderText == placeholderText())
        return;

    uiTextFieldHandle().placeholder = newPlaceholderText.toNSString();
    d_func()->updateImplicitSize();

    emit placeholderTextChanged(newPlaceholderText);
}

#include "moc_quniuikittextfield.cpp"
