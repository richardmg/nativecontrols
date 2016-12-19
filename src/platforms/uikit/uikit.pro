TARGET = QtNativeUIKitControls
MODULE = nativeuikitcontrols

QT += nativecontrols
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

LIBS += -framework UIKit

IOS_CONTROLS = \
    base \
    window \
    control \
    button

for(c,IOS_CONTROLS) {
    HEADERS += qnativeuikit$${c}.h
    HEADERS += qnativeuikit$${c}_p.h
    SOURCES += qnativeuikit$${c}.mm
}

load(qt_module)
