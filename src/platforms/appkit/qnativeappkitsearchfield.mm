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

#include <QtNativeControls/qnativesearchfield.h>
#include <QtNativeAppKitControls/qnativeappkitsearchfield.h>
#include <QtNativeAppKitControls/private/qnativeappkitsearchfield_p.h>

@interface QNativeAppKitSearchFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QNativeAppKitSearchFieldPrivate) *_textField;
}
@end

@implementation QNativeAppKitSearchFieldDelegate

-(id)initWithQNativeAppKitSearchFieldPrivate:(QT_PREPEND_NAMESPACE(QNativeAppKitSearchFieldPrivate) *)textField
{
    self = [self init];
    if (self) {
        _textField = textField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QNativeAppKitSearchFieldPrivate::QNativeAppKitSearchFieldPrivate(int version)
    : QNativeAppKitControlPrivate(version)
{
    m_delegate = [[QNativeAppKitSearchFieldDelegate alloc] initWithQNativeAppKitSearchFieldPrivate:this];

    NSSearchField *nsSearchField = [[[NSSearchField alloc] init] autorelease];
    [nsSearchField sizeToFit];

    setView(nsSearchField);
}

QNativeAppKitSearchFieldPrivate::~QNativeAppKitSearchFieldPrivate()
{
}

void QNativeAppKitSearchFieldPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeAppKitSearchField);
    QNativeAppKitControlPrivate::connectSignals(base);
    const auto b = static_cast<QNativeSearchField *>(base);
    q->connect(q, &QNativeAppKitSearchField::textChanged,
               b, &QNativeSearchField::textChanged);
    q->connect(q, &QNativeAppKitSearchField::placeholderTextChanged,
               b, &QNativeSearchField::placeholderTextChanged);
}

QNativeAppKitSearchField::QNativeAppKitSearchField(QNativeAppKitBase *parent)
    : QNativeAppKitControl(*new QNativeAppKitSearchFieldPrivate(), parent)
{
}

QNativeAppKitSearchField::QNativeAppKitSearchField(const QString &text, QNativeAppKitBase *parent)
    : QNativeAppKitControl(*new QNativeAppKitSearchFieldPrivate(), parent)
{
    setText(text);
}

QNativeAppKitSearchField::QNativeAppKitSearchField(QNativeAppKitSearchFieldPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitControl(dd, parent)
{
}

QNativeAppKitSearchField::~QNativeAppKitSearchField()
{
    Q_D(QNativeAppKitSearchField);
    [d->m_delegate release];
}

NSSearchField *QNativeAppKitSearchField::nsSearchFieldHandle()
{
    return static_cast<NSSearchField *>(d_func()->view());
}

QString QNativeAppKitSearchField::text()
{
    return QString::fromNSString(nsSearchFieldHandle().stringValue);
}

void QNativeAppKitSearchField::setText(const QString &newText)
{
    if (newText == text())
        return;

    nsSearchFieldHandle().stringValue = newText.toNSString();
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

QString QNativeAppKitSearchField::placeholderText()
{
    return QString::fromNSString(nsSearchFieldHandle().placeholderString);
}

void QNativeAppKitSearchField::setPlaceholderText(const QString &newPlaceholderText)
{
    if (newPlaceholderText == placeholderText())
        return;

    nsSearchFieldHandle().placeholderString = newPlaceholderText.toNSString();
    d_func()->updateImplicitSize();

    emit placeholderTextChanged(newPlaceholderText);
}

#include "moc_qnativeappkitsearchfield.cpp"
