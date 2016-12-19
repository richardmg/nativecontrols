TARGET = qtnativeandroidplugin

QT += nativecontrols nativeandroid
QT_PRIVATE += core-private nativeandroid-private

SOURCES += \
    qtnativeandroidplatformplugin.cpp

OTHER_FILES = \
    plugin.json

PLUGIN_TYPE = nativecontrols
PLUGIN_CLASS_NAME = QtNativeAndroidPlatformPlugin
load(qt_plugin)
