TARGET = QtNativeControls
CONFIG += internal_module

QT += qml
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

HEADERS += \
    $$PWD/qnativecontrolsglobal.h \
    $$PWD/qnativecontrol.h

SOURCES += \
    $$PWD/qnativecontrol.cpp

MODULE_PLUGIN_TYPES = nativecontrols

load(qt_module)
