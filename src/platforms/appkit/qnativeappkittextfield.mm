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

#include <AppKit/AppKit.h>

#include <QtCore>

#include <QtNativeControls/qnativetextfield.h>
#include <QtNativeAppKitControls/qnativeappkittextfield.h>
#include <QtNativeAppKitControls/private/qnativeappkittextfield_p.h>

@interface QNativeAppKitTextFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QNativeAppKitTextFieldPrivate) *_textField;
}
@end

@implementation QNativeAppKitTextFieldDelegate

-(id)initWithQNativeAppKitTextFieldPrivate:(QT_PREPEND_NAMESPACE(QNativeAppKitTextFieldPrivate) *)textField
{
    self = [self init];
    if (self) {
        _textField = textField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QNativeAppKitTextFieldPrivate::QNativeAppKitTextFieldPrivate(int version)
    : QNativeAppKitControlPrivate(version)
{
    m_delegate = [[QNativeAppKitTextFieldDelegate alloc] initWithQNativeAppKitTextFieldPrivate:this];

    NSTextField *nsTextField = [[NSTextField alloc] init];
    nsTextField.autoresizingMask = NSViewMaxXMargin | NSViewMinYMargin;
    [nsTextField sizeToFit];

    setView(nsTextField);
}

QNativeAppKitTextFieldPrivate::~QNativeAppKitTextFieldPrivate()
{
}

void QNativeAppKitTextFieldPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeAppKitTextField);
    QNativeAppKitControlPrivate::connectSignals(base);
    q->connect(q, SIGNAL(textChanged(QString)), base, SIGNAL(textChanged(QString)));
    q->connect(q, SIGNAL(clicked()), base, SIGNAL(clicked()));
}

QNativeAppKitTextField::QNativeAppKitTextField(QNativeAppKitBase *parent)
    : QNativeAppKitControl(*new QNativeAppKitTextFieldPrivate(), parent)
{
}

QNativeAppKitTextField::QNativeAppKitTextField(const QString &text, QNativeAppKitBase *parent)
    : QNativeAppKitControl(*new QNativeAppKitTextFieldPrivate(), parent)
{
    setText(text);
}

QNativeAppKitTextField::QNativeAppKitTextField(QNativeAppKitTextFieldPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitControl(dd, parent)
{
}

QNativeAppKitTextField::~QNativeAppKitTextField()
{
    Q_D(QNativeAppKitTextField);
    [d->m_delegate release];
}

NSTextField *QNativeAppKitTextField::nsTextFieldHandle()
{
    return static_cast<NSTextField *>(d_func()->view());
}

QString QNativeAppKitTextField::text()
{
    return QString::fromNSString(nsTextFieldHandle().stringValue);
}

void QNativeAppKitTextField::setText(const QString &newText)
{
    if (newText == text())
        return;

    nsTextFieldHandle().stringValue = newText.toNSString();

    emit textChanged(newText);
}

#include "moc_qnativeappkittextfield.cpp"
