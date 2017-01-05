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
        width: 100
        height: 21
        text: "Click me"
        onClicked: text = "You clicked me!"
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
