TARGET = qtqmlandroidappplugin
TARGETPATH = android/app
IMPORT_VERSION = 0.21

QT += uniandroid-private

SOURCES += \
    $$PWD/qtqmlandroidappplugin.cpp

CONFIG += no_cxx_module
load(qml_plugin)
