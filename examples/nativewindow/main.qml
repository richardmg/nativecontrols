import QtQuick 2.1
import Qt.NativeControls 1.0

ApplicationWindow {
//    width: 480
//    height: 640
    visible: true

    Control {
        Component.onCompleted: print("Outer control completed")

        Control {
            Component.onCompleted: print("Inner control completed")

        }
    }

    Button {

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
