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

@interface QUniUIKitButtonDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniUIKitButtonPrivate) *_button;
}
@end

@implementation QUniUIKitButtonDelegate

-(id)initWithQUniUIKitButtonPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitButtonPrivate) *)button
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

QUniUIKitButtonPrivate::QUniUIKitButtonPrivate(int version)
    : QUniUIKitControlPrivate(version)
    , m_delegate(nullptr)
{
}

QUniUIKitButtonPrivate::~QUniUIKitButtonPrivate()
{
    [m_delegate release];
}

UIView *QUniUIKitButtonPrivate::createView()
{
    UIButton *uiButton = [[UIButton alloc] initWithFrame:CGRectZero];
    [uiButton setTitleColor:uiButton.tintColor forState:UIControlStateNormal];
    [uiButton sizeToFit];

    m_delegate = [[QUniUIKitButtonDelegate alloc] initWithQUniUIKitButtonPrivate:this];
    [uiButton addTarget:m_delegate action:@selector(onClicked) forControlEvents:UIControlEventTouchUpInside];
    return uiButton;
}

UIButton *QUniUIKitButtonPrivate::uiButton() const
{
    return static_cast<UIButton *>(view());
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

QString QUniUIKitButton::text() const
{
    return QString::fromNSString([d_func()->uiButton() titleForState:UIControlStateNormal]);
}

void QUniUIKitButton::setText(const QString &newText)
{
    if (newText == text())
        return;

    [uiButtonHandle() setTitle:newText.toNSString() forState:UIControlStateNormal];
    d_func()->updateImplicitSize();

    emit textChanged(newText);
}

#include "moc_quniuikitbutton.cpp"

QT_END_NAMESPACE

