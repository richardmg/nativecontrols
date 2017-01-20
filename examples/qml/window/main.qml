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
import Qt.NativeControls 1.0

NativeWindow {
    id: theWindow
//    width: 480
//    height: 640
    visible: true

    property int windowAvailableWidth: theWindow.width - 48

    Button {
        id: theButton
        x: 20
        y: 20
        text: "Click me"
        onClicked: text ="You clicked me!"
        onWidthChanged: print("theButton width:" + width)
        onHeightChanged: print("theButton height:" + height)
        onImplicitWidthChanged: print("theButton implicit width:" + implicitWidth)
        onImplicitHeightChanged: print("theButton implicit height:" + implicitHeight)
//        Android.bgStyle: Android.bgBlue
//        Ios.subLabel: "subLabel"
    }

    TextField {
        id: theTextField1
        x: 20
        y: theButton.bottom + 8
        width: windowAvailableWidth / 2
        placeholderText: "Enter some text..."
        onWidthChanged: print("theTextField1 width:" + width)
        onHeightChanged: print("theTextField1 height:" + height)
        onImplicitWidthChanged: print("theTextField1 implicit width:" + implicitWidth)
        onImplicitHeightChanged: print("theTextField1 implicit height:" + implicitHeight)
    }

    SearchField {
        id: theSearchField1
        x: theTextField1.right + 8
        y: theButton.bottom + 8
        width: windowAvailableWidth / 2
        onWidthChanged: print("theSearchField1 width:" + width)
        onHeightChanged: print("theSearchField1 height:" + height)
        onImplicitWidthChanged: print("theSearchField1 implicit width:" + implicitWidth)
        onImplicitHeightChanged: print("theSearchField1 implicit height:" + implicitHeight)
    }

    StyledButton {
        id: platformStyledButton
        x: 20
        y: theSearchField1.bottom + 8
    }

    View {
        id: view
        x: 20
        y: theSearchField1.bottom + 50 // get NaN if binding to theSearchField1
        width: 200
        height: 100
        Button {
            x: 20
            text: "Child button"
            onClicked: text = "Clicked!"
        }
    }

    Component.onCompleted: print("Application window completed" + theTextField1.height + " " + theSearchField1.height)

//	+ios {
//
//	}
//
//  +android {
//
//  }
//
//  +controls2 {
//      contentItem: Item {}
//  }
}
