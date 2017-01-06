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
        height: 22
        placeholderText: "Enter some text..."
        onWidthChanged: print("theTextField1 width:" + width)
        onHeightChanged: print("theTextField1 height:" + height)
        onImplicitWidthChanged: print("theTextField1 implicit width:" + implicitWidth)
        onImplicitHeightChanged: print("theTextField1 implicit height:" + implicitHeight)
    }

    SearchField {
        x: theTextField1.right + 8
        y: theButton.bottom + 8
        width: windowAvailableWidth / 2
        height: 22
    }

    Component.onCompleted: print("Application window completed")

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
