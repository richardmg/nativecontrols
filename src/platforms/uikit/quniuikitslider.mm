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

#include <QtUniUIKitControls/quniuikitslider.h>
#include <QtUniUIKitControls/private/quniuikitslider_p.h>

@interface QUniUIKitSliderDelegate : NSObject {
    QT_PREPEND_NAMESPACE(QUniUIKitSliderPrivate) *_quniuikitslider;
}
@end

@implementation QUniUIKitSliderDelegate

-(id)initWithQUniUIKitSliderPrivate:(QT_PREPEND_NAMESPACE(QUniUIKitSliderPrivate) *)quniuikitslider
{
    self = [self init];
    if (self) {
        _quniuikitslider = quniuikitslider;
    }

    return self;
}

-(void)onValueChanged
{
    emit _quniuikitslider->q_func()->valueChanged(_quniuikitslider->uiSlider().value);
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitSliderPrivate::QUniUIKitSliderPrivate(int version)
    : QUniUIKitControlPrivate(version)
{
}

QUniUIKitSliderPrivate::~QUniUIKitSliderPrivate()
{
    [m_delegate release];
}

UIView *QUniUIKitSliderPrivate::createView()
{
    UISlider *uiSlider = [[UISlider alloc] initWithFrame:CGRectZero];
    [uiSlider sizeToFit];

    m_delegate = [[QUniUIKitSliderDelegate alloc] initWithQUniUIKitSliderPrivate:this];
    [uiSlider addTarget:m_delegate action:@selector(onValueChanged) forControlEvents:UIControlEventValueChanged];
    return uiSlider;
}

UISlider *QUniUIKitSliderPrivate::uiSlider() const
{
    return static_cast<UISlider *>(view());
}

QUniUIKitSlider::QUniUIKitSlider(QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitSliderPrivate(), parent)
{
}

QUniUIKitSlider::QUniUIKitSlider(QUniUIKitSliderPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitControl(dd, parent)
{
}

QUniUIKitSlider::~QUniUIKitSlider()
{
    Q_D(QUniUIKitSlider);
    [d->m_delegate release];
}

UISlider *QUniUIKitSlider::uiSliderHandle()
{
    return d_func()->uiSlider();
}

float QUniUIKitSlider::value() const
{
    return d_func()->uiSlider().value;
}

void QUniUIKitSlider::setValue(const float &newValue)
{
    if (newValue == value())
        return;

    d_func()->uiSlider().value = newValue;
    d_func()->updateIntrinsicContentSize();

    emit valueChanged(newValue);
}

#include "moc_quniuikitslider.cpp"

QT_END_NAMESPACE

