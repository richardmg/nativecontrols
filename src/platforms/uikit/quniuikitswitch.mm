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

#include <QtUniUIKitControls/quniuikitswitch.h>
#include <QtUniUIKitControls/private/quniuikitswitch_p.h>
#include <QtUniUIKitControls/private/quniuikitpropertymacros_p.h>

@interface QUniUISwitch : UISwitch
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>
@end

@implementation QUniUISwitch
#define QUNI_INTERFACE_IMPLEMENTATION
#include <QtUniUIKitControls/private/quniuikitview_nsobject_p.h>

-(void)onValueChanged
{
    Q_Q_NSOBJECT(QUniUIKitSwitch);
    emit q->onChanged(q->on());
}

@end

QT_BEGIN_NAMESPACE

QUniUIKitSwitchPrivate::QUniUIKitSwitchPrivate(int version)
    : QUniUIKitControlPrivate(version)
{
}

QUniUIKitSwitchPrivate::~QUniUIKitSwitchPrivate()
{
}

void QUniUIKitSwitchPrivate::createNSObject()
{
    setNSObject([[[QUniUISwitch alloc] initWithFrame:CGRectZero] autorelease]);
}

void QUniUIKitSwitchPrivate::setNSObject(NSObject *nsObject)
{
    QUniUIKitControlPrivate::setNSObject(nsObject);
    QUniUISwitch *switchobj = static_cast<QUniUISwitch *>(nsObject);
    [switchobj addTarget:switchobj action:@selector(onValueChanged) forControlEvents:UIControlEventValueChanged];
}

UISwitch *QUniUIKitSwitchPrivate::uiSwitch() const
{
    return static_cast<UISwitch *>(view());
}

QUniUIKitSwitch::QUniUIKitSwitch(QUniUIKitBase *parent)
    : QUniUIKitControl(*new QUniUIKitSwitchPrivate(), parent)
{
}

QUniUIKitSwitch::QUniUIKitSwitch(QUniUIKitSwitchPrivate &dd, QUniUIKitBase *parent)
    : QUniUIKitControl(dd, parent)
{
}

QUniUIKitSwitch::~QUniUIKitSwitch()
{
}

UISwitch *QUniUIKitSwitch::uiSwitchHandle()
{
    return d_func()->uiSwitch();
}

SYNTHESIZE_QPROPERTY_CALLBACK(on, On, bool, uiSwitch(), QUniUIKitSwitch)

void QUniUIKitSwitch::setOnAnimated(const bool &newValue)
{
    if (newValue == on())
        return;

    [d_func()->uiSwitch() setOn:newValue animated:YES];
}

#include "moc_quniuikitswitch.cpp"

QT_END_NAMESPACE

