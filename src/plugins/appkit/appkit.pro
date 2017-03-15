TARGET = quniappkit

QT += nativecontrols nativeappkitcontrols
QT_PRIVATE += core-private nativecontrols-private nativeappkitcontrols-private

SOURCES += \
    quniappkitplatformplugin.cpp

OTHER_FILES = \
        plugin.json

PLUGIN_TYPE = nativecontrols
PLUGIN_CLASS_NAME = QNativeAppKitPlatformPlugin
load(qt_plugin)

