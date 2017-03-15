TARGET = QtUniAppKitControls
MODULE = uniappkitcontrols

QT += unicontrols
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

LIBS += -framework AppKit

APPKIT_CONTROLS = \
    qmlbase \
    base \
    window \
    view \
    control \
    button \
    textfield \
    searchfield \
    tabviewcontroller \
    tabviewitem \
    viewcontroller

for(c,APPKIT_CONTROLS) {
    HEADERS += quniappkit$${c}.h
    HEADERS += quniappkit$${c}_p.h
    SOURCES += quniappkit$${c}.mm
}

HEADERS += \
    quniappkitcontrolsglobal.h

load(qt_module)
