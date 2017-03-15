TARGET = qmluniuikitcontrols
TARGETPATH = Qt/NativeUIKitControls
IMPORT_VERSION = 1.0

QT += qml uniuikitcontrols
QT_PRIVATE += core-private gui-private qml-private quick-private

CONFIG += no_cxx_module

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

SOURCES += \
    qmluniuikitcontrolsplugin.cpp

OTHER_FILES += \
    qmldir

load(qml_plugin)
