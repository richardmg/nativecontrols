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

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QNativeWindow window;
    QNativeTabsPage tabsPage(&window);
    QNativeTabsPageTab tab1(QStringLiteral("Tab 1"), &tabsPage);
    QNativeTabsPageTab tab2(QStringLiteral("Tab 2"), &tabsPage);

    QNativeButton button(QStringLiteral("Click me"), &tab1);
    button.move(50, 100);
    QObject::connect(&button, &QNativeButton::clicked, [&button](){ button.setText(QStringLiteral("Thanks!")); });

    QNativeTextField textField(&tab1);
    textField.setPlaceholderText(QStringLiteral("TextField"));
    textField.move(button.left(), button.bottom() + 8);

    QNativeView view(&tab1);
    view.setGeometry(textField.left(), textField.bottom() + 8, 200, 200);

    QNativeButton button2("Button inside view", &view);
    button2.move(8, 0);
    QObject::connect(&button2, &QNativeButton::clicked, [&button2](){ button2.setText(QStringLiteral("Clicked!")); });

    QNativeButton buttonOnTab2(QStringLiteral("Button that moves"), &tab2);
    buttonOnTab2.move(50, 100);
    QObject::connect(&buttonOnTab2, &QNativeButton::clicked, [&buttonOnTab2](){
        buttonOnTab2.setX(buttonOnTab2.x() + 10);
    });

    window.showFullScreen();

    return app.exec();
}
