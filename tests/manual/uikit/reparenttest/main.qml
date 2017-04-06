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
import Qt.UniUIKitControls 1.0

Window {
    id: window
    visible: true
    objectName: "top window"

    rootViewController: ViewController {
        id: controller1
        view: View {
            id: view1
            Button {
                id: button0
                x: (parent.width - width) / 2
                y: (parent.height - height) / 2
                text: "Set rootViewController to controller2"
                onClicked: rootViewController = controller2
            }
        }
    }

    ViewController {
        id: controller2
        view: View {
            id: view2

            Button {
                id: button1
                x: (parent.width - width) / 2
                y: 100
                text: "Steal view from controller1"
                onClicked: {
                    // Doing controller2.view = controller1.view is not allowed in
                    // UIKit, and will cause an exception. So you need to do the following:
                    var view = controller1.view
                    controller1.view = null
                    controller2.view = view

                    button0.text = "Success!"
                }
            }

            Button {
                id: button2
                x: (parent.width - width) / 2
                y: button1.bottom + 10
                text: "Parent slider in"
                onClicked: {
                    if (slider.parent !== view2) {
                        slider.parent = view2
                        text = "Parent slider out"
                    } else {
                        slider.parent = controller2
                        text = "Parent slider in"
                    }
                }
            }
        }

        Slider {
            id: slider
            x: 20
            y: button2.bottom + 10
            width: parent.width - (x * 2)
        }
    }

}
