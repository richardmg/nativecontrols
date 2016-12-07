TARGET = QtNativeControls
MODULE = nativecontrols
CONFIG += internal_module

QT += qml
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

HEADERS += \
    $$PWD/qnativecontrolsglobal_p.h \
    $$PWD/qnativecontrol.h

SOURCES += \
    $$PWD/qnativecontrol.cpp

include(nativecontrols.pri)
load(qt_module)
