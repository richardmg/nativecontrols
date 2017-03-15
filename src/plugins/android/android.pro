TARGET = qtuniandroidplugin

QT += unicontrols uniandroid
QT_PRIVATE += core-private uniandroid-private

SOURCES += \
    qtuniandroidplatformplugin.cpp

OTHER_FILES = \
    plugin.json

PLUGIN_TYPE = unicontrols
PLUGIN_CLASS_NAME = QtUniAndroidPlatformPlugin
load(qt_plugin)
