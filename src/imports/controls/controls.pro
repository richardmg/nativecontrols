TARGET = qmlunicontrols
TARGETPATH = Qt/NativeControls
IMPORT_VERSION = 1.0

QT += qml unicontrols
QT_PRIVATE += core-private gui-private qml-private quick-private 

CONFIG += no_cxx_module

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

SOURCES += \
    qmlunicontrolsplugin.cpp

OTHER_FILES += \
    qmldir

load(qml_plugin)
