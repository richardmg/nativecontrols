TARGET = QtNativeAppKitControls
MODULE = nativeappkitcontrols

QT += nativecontrols
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII QT_BUILD_NATIVEAPPKITCONTROLS_LIB

LIBS += -framework AppKit

APPKIT_CONTROLS = \
    base \
    window \
    control \
    button \
    textfield \
    searchfield

for(c,APPKIT_CONTROLS) {
    HEADERS += qnativeappkit$${c}.h
    HEADERS += qnativeappkit$${c}_p.h
    SOURCES += qnativeappkit$${c}.mm
}

HEADERS += \
    qnativeappkitcontrolsglobal.h

load(qt_module)
