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

#include <QtNativeControls/qunibutton.h>
#include <QtNativeAppKitControls/quniappkitbutton.h>
#include <QtNativeAppKitControls/private/quniappkitbutton_p.h>

@interface QUniAppKitButtonDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniAppKitButtonPrivate) *_button;
}
@end

@implementation QUniAppKitButtonDelegate

-(id)initWithQUniAppKitButtonPrivate:(QT_PREPEND_NAMESPACE(QUniAppKitButtonPrivate) *)button
{
    self = [self init];
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

QUniAppKitButtonPrivate::QUniAppKitButtonPrivate(int version)
    : QUniAppKitControlPrivate(version)
    , m_delegate(nullptr)
{
}

QUniAppKitButtonPrivate::~QUniAppKitButtonPrivate()
{
}

void QUniAppKitButtonPrivate::connectSignals(QUniBase *base)
{
    Q_Q(QUniAppKitButton);
    QUniAppKitControlPrivate::connectSignals(base);
    const auto b = static_cast<QUniButton *>(base);
    q->connect(q, &QUniAppKitButton::textChanged, b, &QUniButton::textChanged);
    q->connect(q, &QUniAppKitButton::clicked, b, &QUniButton::clicked);
}

NSView *QUniAppKitButtonPrivate::createView()
{
    m_delegate = [[QUniAppKitButtonDelegate alloc] initWithQUniAppKitButtonPrivate:this];

    NSButton *nsButton = [[[NSButton alloc] init] autorelease];
    nsButton.bezelStyle = NSRoundedBezelStyle;
    nsButton.buttonType = NSMomentaryPushInButton;
    nsButton.target = m_delegate;
    nsButton.action = @selector(onClicked);
    [nsButton sizeToFit];
    return nsButton;
}

QUniAppKitButton::QUniAppKitButton(QUniAppKitBase *parent)
    : QUniAppKitControl(*new QUniAppKitButtonPrivate(), parent)
{
}

QUniAppKitButton::QUniAppKitButton(const QString &text, QUniAppKitBase *parent)
    : QUniAppKitControl(*new QUniAppKitButtonPrivate(), parent)
{
    setText(text);
}

QUniAppKitButton::QUniAppKitButton(QUniAppKitButtonPrivate &dd, QUniAppKitBase *parent)
    : QUniAppKitControl(dd, parent)
{
}

QUniAppKitButton::~QUniAppKitButton()
{
    Q_D(QUniAppKitButton);
    [d->m_delegate release];
}

NSButton *QUniAppKitButton::nsButtonHandle()
{
    return static_cast<NSButton *>(d_func()->view());
}

QString QUniAppKitButton::text()
{
    return QString::fromNSString(nsButtonHandle().title);
}

void QUniAppKitButton::setText(const QString &newText)
{
    if (newText == text())
        return;

    nsButtonHandle().title = newText.toNSString();
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

#include "moc_quniappkitbutton.cpp"

QT_END_NAMESPACE

