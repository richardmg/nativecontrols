/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtUniControls>

#if defined(Q_OS_MACOS)
#include <QtUniAppKitControls>
#include <AppKit/AppKit.h>
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_TVOS)
#include <QtUniUIKitControls>
#include <UIKit/UIKit.h>
#endif

void main_objc(QUniWindow &window, QUniButton &nativeButton)
{
#if defined(Q_OS_MACOS)
    // Create a platform specific button, and add it as a child of the
    // window using the QUniWindow::addNativeChild() function.
    QUniAppKitButton *nativeAppKitButton1 = new QUniAppKitButton;
    nativeAppKitButton1->move(nativeButton.left(), nativeButton.bottom());
    nativeAppKitButton1->nsButtonHandle().title = @"QUniAppKitButton";

    QObject::connect(nativeAppKitButton1, &QUniAppKitButton::clicked,
                     [nativeAppKitButton1](){ nativeAppKitButton1->setText(QStringLiteral("Clicked!")); });
    window.addNativeChild(nativeAppKitButton1);

    // Add a native switch as well
    NSButton *switchButton = [[[NSButton alloc] initWithFrame:CGRectZero] autorelease];
    [switchButton setButtonType:NSSwitchButton];
    switchButton.frame = CGRectMake(nativeAppKitButton1->left(), nativeAppKitButton1->bottom(), 0, 0);
    [switchButton sizeToFit];
    window.addNativeChild("NSView", switchButton);

    // You can also go the other way, creating a QUniButton as a direct child of another NSView.
    // Note that switchButton.frame is specified with origo bottom-left, as opposed to
    // Qt geometry, which is specified with origo top-left
    QUniButton *nativeButton2 = new QUniButton("QUniButton 2");
    float y = window.height() - switchButton.frame.origin.y - switchButton.frame.size.height;
    nativeButton2->move(switchButton.frame.origin.x, y);
    QObject::connect(nativeButton2, &QUniButton::clicked,
                     [nativeButton2](){ nativeButton2->setText(QStringLiteral("Clicked!")); });
    nativeButton2->setNativeParent("NSView", switchButton.superview);
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_TVOS)
    // Create a platform specific button, and add it as a child of the
    // window using the QUniWindow::addNativeChild() function.
    QUniUIKitButton *nativeUIKitButton1 = new QUniUIKitButton;
    nativeUIKitButton1->move(nativeButton.left(), nativeButton.bottom());
    [nativeUIKitButton1->uiButtonHandle() setTitle:@"QUniUIKitButton" forState:UIControlStateNormal];
    QObject::connect(nativeUIKitButton1, &QUniUIKitButton::clicked,
                     [nativeUIKitButton1](){ nativeUIKitButton1->setText(QStringLiteral("Clicked!")); });
    window.addNativeChild(nativeUIKitButton1);

    // Add a native UISwitch as well
    UISwitch *uiSwitch = [[[UISwitch alloc] initWithFrame:CGRectZero] autorelease];
    uiSwitch.frame = CGRectMake(nativeUIKitButton1->left(), nativeUIKitButton1->bottom(), 0, 0);
    [uiSwitch sizeToFit];
    window.addNativeChild("UIView", uiSwitch);

    // You can also go the other way, creating a QUniButton
    // as a direct child of another UIView.
    QUniButton *nativeButton2 = new QUniButton("QUniButton 2");
    nativeButton2->move(uiSwitch.frame.origin.x, uiSwitch.frame.origin.y + uiSwitch.bounds.size.height);
    QObject::connect(nativeButton2, &QUniButton::clicked,
                     [nativeButton2](){ nativeButton2->setText(QStringLiteral("Clicked!")); });
    nativeButton2->setNativeParent("UIView", uiSwitch.superview);
#endif
}
