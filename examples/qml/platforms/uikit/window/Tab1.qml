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

import QtQml 2.0
import QtQuick 2.5
import Qt.UniUIKitControls 1.0

ViewController {
    id: tab1

    tabBarItem: TabBarItem {
        title: "Tab 1"
    }

    view: View {
        View {
            y: 30
            width: parent.width
            height: parent.height

            Button {
                id: addTabButton
                objectName: "addTabButton"
                text: "Add another tab"
                x: 10
                width: parent.width - (x * 2)
                onClicked: tabBarController.viewControllers.push(newTab.createObject())
            }

            TextField {
                id: tabLabel
                width: parent.width - (x * 2)
                x: 10
                y: addTabButton.bottom + 10
                text: "Tab 1"
                backgroundColor: Qt.rgba(sliderRed.value, sliderGreen.value, sliderBlue.value, 1)
                alpha: sliderAlpha.value

                delegate: TextFieldDelegate {
                    onTextFieldDidReturn: {
                        tab1.tabBarItem.title = tabLabel.text
                        textField.firstResponder = false;
                    }
                    textFieldShouldChangeCharactersInRange: function(textField, range, str) { return str !== 'x'; }
                    textFieldShouldReturn: tabLabel.text !== "Foo"
                }
            }

            Slider {
                id: sliderRed
                x: 50
                y: tabLabel.bottom + 10
                width: parent.width - (x * 2)
                value: 1
            }

            Slider {
                id: sliderGreen
                x: sliderRed.x
                y: sliderRed.bottom + 10
                width: sliderRed.width
                value: 1
            }

            Slider {
                id: sliderBlue
                x: sliderRed.x
                y: sliderGreen.bottom + 10
                width: sliderRed.width
                value: 1
            }

            Slider {
                id: sliderAlpha
                x: sliderRed.x
                y: sliderBlue.bottom + 10
                width: sliderRed.width
                value: 1
            }

            Button {
                id: buttonContactAdd
                buttonType: Button.ButtonTypeContactAdd
                text: "ButtonTypeContactAdd"
                x: 10
                y: sliderAlpha.bottom + 10
            }

            Button {
                id: buttonInfoDark
                buttonType: Button.ButtonTypeInfoDark
                text: "ButtonTypeInfoDark"
                x: 10
                y: buttonContactAdd.bottom + 10
            }

            Button {
                id: buttonInfoLight
                buttonType: Button.ButtonTypeInfoLight
                text: "ButtonTypeInfoLight"
                x: 10
                y: buttonInfoDark.bottom + 10
            }

            Button {
                id: buttonRoundedRect
                buttonType: Button.ButtonTypeRoundedRect
                text: "ButtonTypeRoundedRect"
                x: 10
                y: buttonInfoLight.bottom + 10
            }

            Button {
                id: buttonSystem
                buttonType: Button.ButtonTypeSystem
                text: "ButtonTypeSystem"
                x: 10
                y: buttonRoundedRect.bottom + 10
            }

            Label {
                id: normalLabel
                text: "Normal label";
                x: 10
                y: buttonSystem.bottom + 10
            }

            Switch {
                x: 10
                y: normalLabel.bottom + 10
            }

            Component {
                id: newTab
                NewTab {}
            }
        }
    }
}
