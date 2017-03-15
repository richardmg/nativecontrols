TARGET = quniuikit

QT += unicontrols nativeuikitcontrols
QT_PRIVATE += core-private unicontrols-private nativeuikitcontrols-private

SOURCES += \
    quniuikitplatformplugin.cpp

OTHER_FILES = \
        plugin.json

PLUGIN_TYPE = unicontrols
PLUGIN_CLASS_NAME = QUniUIKitPlatformPlugin
load(qt_plugin)                                                                                                                                             

