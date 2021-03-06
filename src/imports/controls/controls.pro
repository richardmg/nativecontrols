TARGET = qmlnativecontrols
TARGETPATH = Qt/NativeControls
IMPORT_VERSION = 1.0

QT += qml nativecontrols
QT_PRIVATE += core-private gui-private qml-private quick-private 

CONFIG += no_cxx_module

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

HEADERS += \
    qmlnativeapplicationwindow_p.h \
    qmlnativebutton_p.h \
    qmlnativecontrol_p.h

SOURCES += \
    qtnativecontrolsplugin.cpp \
    qmlnativecontrol.cpp \
    qmlnativeapplicationwindow.cpp \
    qmlnativebutton.cpp

OTHER_FILES += \
    qmldir

load(qml_plugin)
