TEMPLATE = app
TARGET = window

QT += nativeuikitcontrols

SOURCES += main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/cpp/platforms/uikit/$$TARGET
INSTALLS += target
