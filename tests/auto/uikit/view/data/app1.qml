import QtQml 2.0
import QtQuick 2.5
import Qt.UniUIKitControls 1.0

Window {
    id: window
    visible: true

    property alias rootView: rootView
    property alias contentView: contentView
    property alias button: button

    rootViewController: ViewController {
        view: View {
            id: rootView
            View {
                id: contentView
                y: 20
                width: parent.width
                height: parent.height
                Button {
                    id: button
                    text: "click me"
                    onClicked: text = "clicked!"
                }
            }
        }
    }
}
