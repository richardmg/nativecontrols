TARGET = QtNativeControls
MODULE = nativecontrols
MODULE_PLUGIN_TYPES = nativecontrols

QT += qml
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

NATIVE_CONTROLS = \
    base \
    window \
    control \
    button \
    textfield \
    searchfield

for(c,NATIVE_CONTROLS) {
    HEADERS += qnative$${c}.h
    HEADERS += qnative$${c}_p.h
    HEADERS += platform/qnativeplatform$${c}.h
    SOURCES += qnative$${c}.cpp
}

HEADERS += \
    qnativecontrolsglobal.h \
    qnativeplatformmanager_p.h \
    platform/qnativecontrolsplatformplugin.h

SOURCES += \
    qnativeplatformmanager.cpp

load(qt_module)
