TARGET = QtNativeUIKitControls
MODULE = nativeuikitcontrols

QT += nativecontrols
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII Q_NATIVEUIKITCONTROLS_EXPORT

LIBS += -framework CoreGraphics -framework Foundation -framework UIKit

IOS_CONTROLS = \
    base \
    window \
    control \
    button \
    textfield

for(c,IOS_CONTROLS) {
    HEADERS += qnativeuikit$${c}.h
    HEADERS += qnativeuikit$${c}_p.h
    SOURCES += qnativeuikit$${c}.mm
}

HEADERS += \
    qnativeuikitcontrolsglobal.h

load(qt_module)
