import QtQml 2.0
import QtQuick 2.5
import Qt.UniUIKitControls 1.0

Window {
    id: window
    visible: true

    property alias rootView: rootView
    property alias contentView: contentView
    property alias childView: childView
    property alias childView2: childView2
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
                    intrinsicContentWidth: 100
                    intrinsicContentHeight: 100
                }
                View {
                    id: childView2
                    width: intrinsicContentWidth
                    intrinsicContentWidth: contentView.width
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
