TARGET = qnativeuikit

QT += nativecontrols nativeuikitcontrols
QT_PRIVATE += core-private nativecontrols-private nativeuikitcontrols-private

SOURCES += \
    qnativeuikitplatformplugin.cpp

OTHER_FILES = \
        plugin.json

PLUGIN_TYPE = nativecontrols
PLUGIN_CLASS_NAME = QNativeUIKitPlatformPlugin
load(qt_plugin)                                                                                                                                             

