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
#include <QtNativeControls>

#if defined(Q_OS_MACOS)
#include <QtNativeAppKitControls>
#include <AppKit/AppKit.h>
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_TVOS)
#include <QtNativeUIKitControls>
#include <UIKit/UIKit.h>
#endif

void main_objc(QNativeWindow &window, QNativeButton &nativeButton)
{
#if defined(Q_OS_MACOS)
    // Add QNativeAppKitButton as a direct child of QNativeWindow
    QNativeAppKitButton *nativeAppKitButton1 = new QNativeAppKitButton();
    nativeAppKitButton1->setParent(&window);
    nativeAppKitButton1->move(nativeButton.left(), nativeButton.bottom());
    nativeAppKitButton1->nsButtonHandle().title = @"QNativeAppKitButton 1";
    QObject::connect(nativeAppKitButton1, &QNativeAppKitButton::clicked,
                     [nativeAppKitButton1](){ nativeAppKitButton1->setText(QStringLiteral("Clicked!")); });

    // You can also go the other way, creating a QNativeButton as a direct child of QNativeAppKitWindow
    QNativeButton *nativeButton2 = new QNativeButton("QNativeButton 2");
    nativeButton2->setParent(window.platformHandle());
    nativeButton2->move(nativeAppKitButton1->geometry().left(), nativeAppKitButton1->geometry().bottom());
    QObject::connect(nativeButton2, &QNativeButton::clicked,
                     [nativeButton2](){ nativeButton2->setText(QStringLiteral("Clicked!")); });

    if (QNativeAppKitWindow *nativeAppKitWindow = dynamic_cast<QNativeAppKitWindow *>(window.platformHandle())) {
        QNativeAppKitButton *nativeAppKitButton2 = new QNativeAppKitButton(nativeAppKitWindow);
        nativeAppKitButton2->move(nativeButton2->geometry().left(), nativeButton2->geometry().bottom());
        QObject::connect(nativeAppKitButton2, &QNativeAppKitButton::clicked,
                         [nativeAppKitButton2](){ nativeAppKitButton2->setText(QStringLiteral("Clicked!")); });

        NSButton *nsButton = nativeAppKitButton2->nsButtonHandle();
        nsButton.title = @"Click me";
#if QT_OSX_PLATFORM_SDK_EQUAL_OR_ABOVE(101202)
        if ([[NSProcessInfo processInfo] isOperatingSystemAtLeastVersion:(NSOperatingSystemVersion){10, 12, 2}])
            nsButton.bezelColor = [NSColor redColor];
#endif

        NSWindow *nsWindow = nativeAppKitWindow->nsWindowHandle();
        nsWindow.backgroundColor = [NSColor blueColor];
    }
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_TVOS)

    // Add QNativeUIKitButton as a direct child of QNativeWindow
    QNativeUIKitButton *nativeUIKitButton1 = new QNativeUIKitButton();
    nativeUIKitButton1->setParent(&window);
    nativeUIKitButton1->move(nativeButton.left(), nativeButton.bottom());
    [nativeUIKitButton1->uiButtonHandle() setTitle:@"QNativeUIKitButton 1" forState:UIControlStateNormal];
    QObject::connect(nativeUIKitButton1, &QNativeUIKitButton::clicked,
                     [nativeUIKitButton1](){ nativeUIKitButton1->setText(QStringLiteral("Clicked!")); });

    // You can also go the other way, creating a QNativeButton as a direct child of QNativeUIKitWindow
    QNativeButton *nativeButton2 = new QNativeButton("QNativeButton 2");
    nativeButton2->setParent(window.platformHandle());
    nativeButton2->move(nativeUIKitButton1->geometry().left(), nativeUIKitButton1->geometry().bottom());
    QObject::connect(nativeButton2, &QNativeButton::clicked,
                     [nativeButton2](){ nativeButton2->setText(QStringLiteral("Clicked!")); });

    // Add another QNativeUIKitButton as a child of QNativeUIKitWindow, but this time more explicit
    if (QNativeUIKitWindow *nativeUIKitWindow = dynamic_cast<QNativeUIKitWindow *>(window.platformHandle())) {
        QNativeUIKitButton *nativeUIKitButton2 = new QNativeUIKitButton(nativeUIKitWindow);
        nativeUIKitButton2->move(nativeButton2->geometry().left(), nativeButton2->geometry().bottom());
        QObject::connect(nativeUIKitButton2, &QNativeUIKitButton::clicked,
                         [nativeUIKitButton2](){ nativeUIKitButton2->setText(QStringLiteral("Clicked!")); });

        UIButton *uiButton = nativeUIKitButton2->uiButtonHandle();
        [uiButton setTitle:@"QNativeUIKitButton 2" forState:UIControlStateNormal];
        uiButton.tintColor = [UIColor redColor];

        UIWindow *uiWindow = nativeUIKitWindow->uiWindowHandle();
        uiWindow.backgroundColor = [UIColor blueColor];
    }

#endif
}
