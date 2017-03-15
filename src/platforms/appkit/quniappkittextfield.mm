/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Native AppKit Controls module of the Qt Toolkit.
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

#include <AppKit/AppKit.h>

#include <QtCore>

#include <QtNativeControls/qunitextfield.h>
#include <QtNativeAppKitControls/quniappkittextfield.h>
#include <QtNativeAppKitControls/private/quniappkittextfield_p.h>

@interface QUniAppKitTextFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniAppKitTextFieldPrivate) *_textField;
}
@end

@implementation QUniAppKitTextFieldDelegate

-(id)initWithQUniAppKitTextFieldPrivate:(QT_PREPEND_NAMESPACE(QUniAppKitTextFieldPrivate) *)textField
{
    self = [self init];
    if (self) {
        _textField = textField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QUniAppKitTextFieldPrivate::QUniAppKitTextFieldPrivate(int version)
    : QUniAppKitControlPrivate(version)
    , m_delegate(nullptr)
{
}

QUniAppKitTextFieldPrivate::~QUniAppKitTextFieldPrivate()
{
}

void QUniAppKitTextFieldPrivate::connectSignals(QUniBase *base)
{
    Q_Q(QUniAppKitTextField);
    QUniAppKitControlPrivate::connectSignals(base);
    const auto b = static_cast<QUniTextField *>(base);
    q->connect(q, &QUniAppKitTextField::textChanged,
               b, &QUniTextField::textChanged);
    q->connect(q, &QUniAppKitTextField::placeholderTextChanged,
               b, &QUniTextField::placeholderTextChanged);
}

NSView *QUniAppKitTextFieldPrivate::createView()
{
    m_delegate = [[QUniAppKitTextFieldDelegate alloc] initWithQUniAppKitTextFieldPrivate:this];

    NSTextField *nsTextField = [[[NSTextField alloc] init] autorelease];
    [nsTextField sizeToFit];

    return nsTextField;
}

QUniAppKitTextField::QUniAppKitTextField(QUniAppKitBase *parent)
    : QUniAppKitControl(*new QUniAppKitTextFieldPrivate(), parent)
{
}

QUniAppKitTextField::QUniAppKitTextField(const QString &text, QUniAppKitBase *parent)
    : QUniAppKitControl(*new QUniAppKitTextFieldPrivate(), parent)
{
    setText(text);
}

QUniAppKitTextField::QUniAppKitTextField(QUniAppKitTextFieldPrivate &dd, QUniAppKitBase *parent)
    : QUniAppKitControl(dd, parent)
{
}

QUniAppKitTextField::~QUniAppKitTextField()
{
    Q_D(QUniAppKitTextField);
    [d->m_delegate release];
}

NSTextField *QUniAppKitTextField::nsTextFieldHandle()
{
    return static_cast<NSTextField *>(d_func()->view());
}

QString QUniAppKitTextField::text()
{
    return QString::fromNSString(nsTextFieldHandle().stringValue);
}

void QUniAppKitTextField::setText(const QString &newText)
{
    if (newText == text())
        return;

    nsTextFieldHandle().stringValue = newText.toNSString();
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

QString QUniAppKitTextField::placeholderText()
{
    return QString::fromNSString(nsTextFieldHandle().placeholderString);
}

void QUniAppKitTextField::setPlaceholderText(const QString &newPlaceholderText)
{
    if (newPlaceholderText == placeholderText())
        return;

    nsTextFieldHandle().placeholderString = newPlaceholderText.toNSString();
    d_func()->updateImplicitSize();

    emit placeholderTextChanged(newPlaceholderText);
}

#include "moc_quniappkittextfield.cpp"
