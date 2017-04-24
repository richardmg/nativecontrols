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
#include <QtUniUIKitControls>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QUniUIKitWindow window;
    QUniUIKitTabBarController tabBarController(&window);
    window.setRootViewController(&tabBarController);

    QUniUIKitViewController tab1(&tabBarController);
    QUniUIKitViewController tab2(&tabBarController);
    tab1.setTabBarItem(new QUniUIKitTabBarItem(QStringLiteral("Tab1"), &tab1));
    tab2.setTabBarItem(new QUniUIKitTabBarItem(QStringLiteral("Tab2"), &tab2));
    tabBarController.setViewControllers(QList<QUniUIKitViewController *>() << &tab1 << &tab2);

    QUniUIKitView *contentViewTab1 = tab1.view();
    QUniUIKitView *contentViewTab2 = tab2.view();
    float margin = 0;

    QUniUIKitButton button(QStringLiteral("Click me"), contentViewTab1);
    button.setGeometry(50, 100, button.intrinsicContentWidth(), button.intrinsicContentHeight());
    button.move(50, 100);
    QObject::connect(&button, &QUniUIKitButton::clicked, [&button](){ button.setText(QStringLiteral("Thanks!")); });

    QUniUIKitTextField textField(contentViewTab1);
    textField.setPlaceholderText(QStringLiteral("TextField"));
    textField.setGeometry(button.left(), button.bottom() + margin, 200, textField.intrinsicContentHeight());

    QUniUIKitView view(contentViewTab1);
    view.setGeometry(button.left(), textField.geometry().bottom() + margin, 200, 200);

    QUniUIKitButton button2("Child button", &view);
    button2.setGeometry(0, 0, button2.intrinsicContentWidth(), button2.intrinsicContentHeight());
    QObject::connect(&button2, &QUniUIKitButton::clicked, [&button2](){ button2.setText(QStringLiteral("Clicked!")); });

    QUniUIKitSlider slider(contentViewTab2);
    slider.setGeometry(50, 50, window.width() - 100, slider.intrinsicContentHeight());
    QObject::connect(&slider, &QUniUIKitSlider::valueChanged, [&slider](){ qDebug() << "new value:" << slider.value(); });

    QUniUIKitTextField textField2(contentViewTab1);
    textField2.setPlaceholderText(QStringLiteral("TextField 2"));
    textField2.move(button.left(), 300);
    textField2.resize(200, textField2.intrinsicContentHeight());

    window.showFullScreen();
    return app.exec();
}
