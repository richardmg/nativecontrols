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

Window {
    id: window
    visible: true

    rootViewController: TabBarController {

        ViewController {
            tabBarItem: TabBarItem {
                title: "Tab 1"
            }
            view: View {
                View {
                    y: 30
                    width: parent.width
                    height: parent.height
                    Button {
                        objectName: "myButton"
                        width: intrinsicContentWidth
                        height: intrinsicContentHeight
                        text: "click me"
                        onClicked: text = "clicked with a very long string!"
                        intrinsicContentWidth: 100
                        Component.onCompleted: {
                            print("intr w:", intrinsicContentWidth)
                            print("intr h:", intrinsicContentHeight)
                        }
                        onIntrinsicContentWidthChanged: print("new intr w:", intrinsicContentWidth)
                    }
                }
            }
        }

        ViewController {
            tabBarItem: TabBarItem {
                title: "Tab 2"
            }
            view: View {
                backgroundColor: Qt.rgba(255, 255, 0, 255)
                View {
                    y: 30
                    width: parent.width
                    height: parent.height
                    backgroundColor: Qt.rgba(0, 255, 0, 255)
                    Button {
                        width: intrinsicContentWidth
                        height: intrinsicContentHeight
                        text: "click me as well"
                        onClicked: text = "clicked!"
                        backgroundColor: Qt.rgba(0, 0, 255, 255)
                    }
                }
            }
        }

    }

}
