TARGET = nativecontrols 
TARGETPATH = Qt/NativeControls
IMPORT_VERSION = 1.0

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private 

CONFIG += no_cxx_module

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

#HEADERS += \
#    foo.h

SOURCES += \
    plugin.cpp

RESOURCES += \
    qqc2macosstyleplugin.qrc

OTHER_FILES += \
    qmldir

load(qml_plugin)
