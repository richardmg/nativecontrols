import QtQml 2.0
import QtQuick 2.5
import Qt.UniUIKitControls 1.0

Window {
    id: window
    visible: true

    property alias rootView: rootView
    property alias contentView: contentView
    property alias childView: childView

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
    }
}
