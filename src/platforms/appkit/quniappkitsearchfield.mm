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

#include <QtNativeControls/qunisearchfield.h>
#include <QtNativeAppKitControls/quniappkitsearchfield.h>
#include <QtNativeAppKitControls/private/quniappkitsearchfield_p.h>

@interface QUniAppKitSearchFieldDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniAppKitSearchFieldPrivate) *_textField;
}
@end

@implementation QUniAppKitSearchFieldDelegate

-(id)initWithQUniAppKitSearchFieldPrivate:(QT_PREPEND_NAMESPACE(QUniAppKitSearchFieldPrivate) *)textField
{
    self = [self init];
    if (self) {
        _textField = textField;
    }

    return self;
}

@end

QT_BEGIN_NAMESPACE

QUniAppKitSearchFieldPrivate::QUniAppKitSearchFieldPrivate(int version)
    : QUniAppKitControlPrivate(version)
    , m_delegate(nullptr)
{
}

QUniAppKitSearchFieldPrivate::~QUniAppKitSearchFieldPrivate()
{
}

void QUniAppKitSearchFieldPrivate::connectSignals(QUniBase *base)
{
    Q_Q(QUniAppKitSearchField);
    QUniAppKitControlPrivate::connectSignals(base);
    const auto b = static_cast<QUniSearchField *>(base);
    q->connect(q, &QUniAppKitSearchField::textChanged,
               b, &QUniSearchField::textChanged);
    q->connect(q, &QUniAppKitSearchField::placeholderTextChanged,
               b, &QUniSearchField::placeholderTextChanged);
}

NSView *QUniAppKitSearchFieldPrivate::createView()
{
    m_delegate = [[QUniAppKitSearchFieldDelegate alloc] initWithQUniAppKitSearchFieldPrivate:this];

    NSSearchField *nsSearchField = [[[NSSearchField alloc] init] autorelease];
    [nsSearchField sizeToFit];

    return nsSearchField;
}

QUniAppKitSearchField::QUniAppKitSearchField(QUniAppKitBase *parent)
    : QUniAppKitControl(*new QUniAppKitSearchFieldPrivate(), parent)
{
}

QUniAppKitSearchField::QUniAppKitSearchField(const QString &text, QUniAppKitBase *parent)
    : QUniAppKitControl(*new QUniAppKitSearchFieldPrivate(), parent)
{
    setText(text);
}

QUniAppKitSearchField::QUniAppKitSearchField(QUniAppKitSearchFieldPrivate &dd, QUniAppKitBase *parent)
    : QUniAppKitControl(dd, parent)
{
}

QUniAppKitSearchField::~QUniAppKitSearchField()
{
    Q_D(QUniAppKitSearchField);
    [d->m_delegate release];
}

NSSearchField *QUniAppKitSearchField::nsSearchFieldHandle()
{
    return static_cast<NSSearchField *>(d_func()->view());
}

QString QUniAppKitSearchField::text()
{
    return QString::fromNSString(nsSearchFieldHandle().stringValue);
}

void QUniAppKitSearchField::setText(const QString &newText)
{
    if (newText == text())
        return;

    nsSearchFieldHandle().stringValue = newText.toNSString();
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

QString QUniAppKitSearchField::placeholderText()
{
    return QString::fromNSString(nsSearchFieldHandle().placeholderString);
}

void QUniAppKitSearchField::setPlaceholderText(const QString &newPlaceholderText)
{
    if (newPlaceholderText == placeholderText())
        return;

    nsSearchFieldHandle().placeholderString = newPlaceholderText.toNSString();
    d_func()->updateImplicitSize();

    emit placeholderTextChanged(newPlaceholderText);
}

#include "moc_quniappkitsearchfield.cpp"
