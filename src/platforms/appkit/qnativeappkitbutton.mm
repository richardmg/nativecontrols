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

#include <QtNativeControls/qnativebutton.h>
#include <QtNativeAppKitControls/qnativeappkitbutton.h>
#include <QtNativeAppKitControls/private/qnativeappkitbutton_p.h>

@interface QNativeAppKitButtonDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QNativeAppKitButtonPrivate) *_button;
}
@end

@implementation QNativeAppKitButtonDelegate

-(id)initWithQNativeAppKitButtonPrivate:(QT_PREPEND_NAMESPACE(QNativeAppKitButtonPrivate) *)button
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

QNativeAppKitButtonPrivate::QNativeAppKitButtonPrivate(int version)
    : QNativeAppKitControlPrivate(version)
{
    m_delegate = [[QNativeAppKitButtonDelegate alloc] initWithQNativeAppKitButtonPrivate:this];

    NSButton *nsButton = [[[NSButton alloc] init] autorelease];
    nsButton.bezelStyle = NSRoundedBezelStyle;
    nsButton.buttonType = NSMomentaryPushInButton;
    nsButton.target = m_delegate;
    nsButton.action = @selector(onClicked);
    [nsButton sizeToFit];

    setView(nsButton);
}

QNativeAppKitButtonPrivate::~QNativeAppKitButtonPrivate()
{
}

void QNativeAppKitButtonPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeAppKitButton);
    QNativeAppKitControlPrivate::connectSignals(base);
    const auto b = static_cast<QNativeButton *>(base);
    q->connect(q, &QNativeAppKitButton::textChanged, b, &QNativeButton::textChanged);
    q->connect(q, &QNativeAppKitButton::clicked, b, &QNativeButton::clicked);
}

QNativeAppKitButton::QNativeAppKitButton(QNativeAppKitBase *parent)
    : QNativeAppKitControl(*new QNativeAppKitButtonPrivate(), parent)
{
}

QNativeAppKitButton::QNativeAppKitButton(const QString &text, QNativeAppKitBase *parent)
    : QNativeAppKitControl(*new QNativeAppKitButtonPrivate(), parent)
{
    setText(text);
}

QNativeAppKitButton::QNativeAppKitButton(QNativeAppKitButtonPrivate &dd, QNativeAppKitBase *parent)
    : QNativeAppKitControl(dd, parent)
{
}

QNativeAppKitButton::~QNativeAppKitButton()
{
    Q_D(QNativeAppKitButton);
    [d->m_delegate release];
}

NSButton *QNativeAppKitButton::nsButtonHandle()
{
    return static_cast<NSButton *>(d_func()->view());
}

QString QNativeAppKitButton::text()
{
    return QString::fromNSString(nsButtonHandle().title);
}

void QNativeAppKitButton::setText(const QString &newText)
{
    if (newText == text())
        return;

    nsButtonHandle().title = newText.toNSString();
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

#include "moc_qnativeappkitbutton.cpp"

QT_END_NAMESPACE

