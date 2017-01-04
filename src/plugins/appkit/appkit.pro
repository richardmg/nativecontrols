TARGET = qnativeappkit

QT += nativecontrols nativeappkitcontrols
QT_PRIVATE += core-private nativeappkitcontrols-private

SOURCES += \
    qnativeappkitplatformplugin.cpp

OTHER_FILES = \
        plugin.json

PLUGIN_TYPE = nativecontrols
PLUGIN_CLASS_NAME = QNativeAppKitPlatformPlugin
load(qt_plugin)

