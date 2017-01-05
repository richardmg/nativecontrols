/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
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

#include <QtNativeControls/qnativetextfield.h>
#include <QtNativeUIKitControls/qnativeuikittextfield.h>
#include <QtNativeUIKitControls/private/qnativeuikittextfield_p.h>

@interface QNativeUIKitTextFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QNativeUIKitTextFieldPrivate) *_textField;
}
@end

@implementation QNativeUIKitTextFieldDelegate

-(id)initWithQNativeUIKitTextFieldPrivate:(QT_PREPEND_NAMESPACE(QNativeUIKitTextFieldPrivate) *)textField
{
    self = [self init];
    if (self) {
        _textField = textField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QNativeUIKitTextFieldPrivate::QNativeUIKitTextFieldPrivate(int version)
    : QNativeUIKitControlPrivate(version)
{
    m_delegate = [[QNativeUIKitTextFieldDelegate alloc] initWithQNativeUIKitTextFieldPrivate:this];

    UITextField *uiTextField = [[[UITextField alloc] init] autorelease];
    [uiTextField sizeToFit];

    setView(uiTextField);
}

QNativeUIKitTextFieldPrivate::~QNativeUIKitTextFieldPrivate()
{
    [m_delegate release];
}

void QNativeUIKitTextFieldPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeUIKitTextField);
    QNativeUIKitControlPrivate::connectSignals(base);
    const auto b = static_cast<QNativeTextField *>(base);
    q->connect(q, &QNativeUIKitTextField::textChanged,
               b, &QNativeTextField::textChanged);
    q->connect(q, &QNativeUIKitTextField::placeholderTextChanged,
               b, &QNativeTextField::placeholderTextChanged);
}

QNativeUIKitTextField::QNativeUIKitTextField(QNativeUIKitBase *parent)
    : QNativeUIKitControl(*new QNativeUIKitTextFieldPrivate(), parent)
{
}

QNativeUIKitTextField::QNativeUIKitTextField(const QString &text, QNativeUIKitBase *parent)
    : QNativeUIKitControl(*new QNativeUIKitTextFieldPrivate(), parent)
{
    setText(text);
}

QNativeUIKitTextField::QNativeUIKitTextField(QNativeUIKitTextFieldPrivate &dd, QNativeUIKitBase *parent)
    : QNativeUIKitControl(dd, parent)
{
}

QNativeUIKitTextField::~QNativeUIKitTextField()
{
    Q_D(QNativeUIKitTextField);
    [d->m_delegate release];
}

UITextField *QNativeUIKitTextField::uiTextFieldHandle()
{
    return static_cast<UITextField *>(d_func()->view());
}

QString QNativeUIKitTextField::text()
{
    return QString::fromNSString(uiTextFieldHandle().text);
}

void QNativeUIKitTextField::setText(const QString &newText)
{
    if (newText == text())
        return;

    uiTextFieldHandle().text = newText.toNSString();

    emit textChanged(newText);
}

QString QNativeUIKitTextField::placeholderText()
{
    return QString::fromNSString(uiTextFieldHandle().placeholder);
}

void QNativeUIKitTextField::setPlaceholderText(const QString &newPlaceholderText)
{
    if (newPlaceholderText == placeholderText())
        return;

    uiTextFieldHandle().placeholder = newPlaceholderText.toNSString();

    emit placeholderTextChanged(newPlaceholderText);
}

#include "moc_qnativeuikittextfield.cpp"
