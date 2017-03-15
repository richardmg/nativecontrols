TARGET = quniappkit

QT += unicontrols nativeappkitcontrols
QT_PRIVATE += core-private unicontrols-private nativeappkitcontrols-private

SOURCES += \
    quniappkitplatformplugin.cpp

OTHER_FILES = \
        plugin.json

PLUGIN_TYPE = unicontrols
PLUGIN_CLASS_NAME = QUniAppKitPlatformPlugin
load(qt_plugin)

