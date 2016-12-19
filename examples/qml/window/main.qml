import QtQml 2.0
import Qt.NativeControls 1.0

NativeWindow {
//    width: 480
//    height: 640
//    visible: true

    Button {
        x: 10
        y: 50
        width: 100
        height: 30
        text: "Click me"
        onClicked: text = "You clicked me!"
//        Android.bgStyle: Android.bgBlue
//        Ios.subLabel: "subLabel"
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
