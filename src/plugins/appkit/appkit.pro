TARGET = quniappkit

QT += unicontrols uniappkitcontrols
QT_PRIVATE += core-private unicontrols-private uniappkitcontrols-private

SOURCES += \
    quniappkitplatformplugin.cpp

OTHER_FILES = \
        plugin.json

PLUGIN_TYPE = unicontrols
PLUGIN_CLASS_NAME = QUniAppKitPlatformPlugin
load(qt_plugin)

