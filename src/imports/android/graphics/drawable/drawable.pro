TARGET = qtqmlandroiddrawableplugin
TARGETPATH = android/graphics/drawable
IMPORT_VERSION = 0.21

QT += uniandroid-private

SOURCES += \
    $$PWD/qtqmlandroiddrawableplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
