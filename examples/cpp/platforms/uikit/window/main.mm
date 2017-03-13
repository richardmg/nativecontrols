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

#include <UIKit/UIKit.h>

#include <QtGui>
#include <QtNativeUIKitControls>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QNativeUIKitWindow window;
    QNativeUIKitTabBarController tabBarController(&window);

    QNativeUIKitViewController tab1(&tabBarController);
    QNativeUIKitViewController tab2(&tabBarController);
    tab1.setTabBarItem(new QNativeUIKitTabBarItem(QStringLiteral("Tab1"), &tab1));
    tab2.setTabBarItem(new QNativeUIKitTabBarItem(QStringLiteral("Tab2"), &tab2));
    tabBarController.setViewControllers(QList<QNativeUIKitViewController *>() << &tab1 << &tab2);

    QNativeUIKitView *contentView = tab1.view();
    float margin = 0;

    QNativeUIKitButton button(QStringLiteral("Click me"), contentView);
    button.move(50, 100);
    QObject::connect(&button, &QNativeUIKitButton::clicked, [&button](){ button.setText(QStringLiteral("Thanks!")); });

    QNativeUIKitTextField textField(contentView);
    textField.setPlaceholderText(QStringLiteral("TextField"));
    textField.move(button.left(), button.bottom() + margin);
    textField.resize(200, textField.implicitSize().height());

    QNativeUIKitView view(contentView);
    view.setGeometry(button.left(), textField.geometry().bottom() + margin, 200, 200);

    QNativeUIKitButton button2("Child button", &view);
    button2.move(0, 0);
    QObject::connect(&button2, &QNativeUIKitButton::clicked, [&button2](){ button2.setText(QStringLiteral("Clicked!")); });

    QNativeUIKitTextField textField2(contentView);
    textField2.setPlaceholderText(QStringLiteral("TextField 2"));
    textField2.move(button.left(), 300);
//    textField2.resize(200, textField.implicitSize().height());

    window.showFullScreen();
    return app.exec();
}
