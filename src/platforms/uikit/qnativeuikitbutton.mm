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

#include <QtNativeControls/qnativebutton.h>
#include <QtNativeUIKitControls/qnativeuikitbutton.h>
#include <QtNativeUIKitControls/private/qnativeuikitbutton_p.h>

#define CASTEDBUTTON static_cast<UIButton *>(d_func()->view())

@interface QNativeUIKitButtonDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QNativeUIKitButtonPrivate) *_button;
}
@end

@implementation QNativeUIKitButtonDelegate

-(id)initWithQNativeUIKitButtonPrivate:(QT_PREPEND_NAMESPACE(QNativeUIKitButtonPrivate) *)button
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

QNativeUIKitButtonPrivate::QNativeUIKitButtonPrivate(int version)
    : QNativeUIKitControlPrivate(version)
{
    UIButton *uiButton = [[UIButton alloc] initWithFrame:CGRectZero];
    setView(uiButton);
    m_delegate = [[QNativeUIKitButtonDelegate alloc] initWithQNativeUIKitButtonPrivate:this];
    [uiButton addTarget:m_delegate action:@selector(onClicked) forControlEvents:UIControlEventTouchUpInside];
}

QNativeUIKitButtonPrivate::~QNativeUIKitButtonPrivate()
{
}

void QNativeUIKitButtonPrivate::connectSignals(QNativeBase *base)
{
    Q_Q(QNativeUIKitButton);
    QNativeUIKitControlPrivate::connectSignals(base);
    q->connect(q, SIGNAL(textChanged(QString)), base, SIGNAL(textChanged(QString)));
    q->connect(q, SIGNAL(clicked()), base, SIGNAL(clicked()));
}

QNativeUIKitButton::QNativeUIKitButton(QNativeUIKitBase *parent)
    : QNativeUIKitControl(*new QNativeUIKitButtonPrivate(), parent)
{
}

QNativeUIKitButton::QNativeUIKitButton(const QString &text, QNativeUIKitBase *parent)
    : QNativeUIKitControl(*new QNativeUIKitButtonPrivate(), parent)
{
    setText(text);
}

QNativeUIKitButton::QNativeUIKitButton(QNativeUIKitButtonPrivate &dd, QNativeUIKitBase *parent)
    : QNativeUIKitControl(dd, parent)
{
}

QNativeUIKitButton::~QNativeUIKitButton()
{
    Q_D(QNativeUIKitButton);
    [d->m_delegate release];
}

QString QNativeUIKitButton::text()
{
    return QString::fromNSString([CASTEDBUTTON titleForState:UIControlStateNormal]);
}

void QNativeUIKitButton::setText(const QString &newText)
{
    if (newText == text())
        return;

    [CASTEDBUTTON setTitle:newText.toNSString() forState:UIControlStateNormal];

    emit textChanged(newText);
}

#include "moc_qnativeuikitbutton.cpp"

QT_END_NAMESPACE

