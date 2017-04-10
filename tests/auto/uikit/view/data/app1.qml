import QtQml 2.0
import QtQuick 2.5
import Qt.UniUIKitControls 1.0

Window {
    id: window
    visible: true

    property alias rootView: rootView
    property alias contentView: contentView
    property alias childView: childView
    property alias orphanView: orphanView

    rootViewController: ViewController {
        view: View {
            id: rootView
            View {
                id: contentView
                y: 20
                width: parent.width
                height: parent.height
                View {
                    id: childView
                    implicitWidth: 100
                    implicitHeight: 100
                }
            }
        }

        View {
            id: orphanView
            onParentChanged: {
                width = parent.hasOwnProperty("width") ? Qt.binding(function() { return parent.width; }) : 0;
                height = parent.hasOwnProperty("height") ? Qt.binding(function() { return parent.height; }) : 0;
            }
        }
    }
}
