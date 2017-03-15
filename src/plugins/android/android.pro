TARGET = qtnativeandroidplugin

QT += unicontrols nativeandroid
QT_PRIVATE += core-private nativeandroid-private

SOURCES += \
    qtnativeandroidplatformplugin.cpp

OTHER_FILES = \
    plugin.json

PLUGIN_TYPE = unicontrols
PLUGIN_CLASS_NAME = QtUniAndroidPlatformPlugin
load(qt_plugin)
