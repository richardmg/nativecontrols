TARGET = qtqmlandroidanimationplugin
TARGETPATH = android/view/animation
IMPORT_VERSION = 0.21

QT += uniandroid-private

SOURCES += \
    $$PWD/qtqmlandroidanimationplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
