TARGET = quniuikit

QT += nativecontrols nativeuikitcontrols
QT_PRIVATE += core-private nativecontrols-private nativeuikitcontrols-private

SOURCES += \
    quniuikitplatformplugin.cpp

OTHER_FILES = \
        plugin.json

PLUGIN_TYPE = nativecontrols
PLUGIN_CLASS_NAME = QUniUIKitPlatformPlugin
load(qt_plugin)                                                                                                                                             

