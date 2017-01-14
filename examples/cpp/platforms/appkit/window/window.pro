TEMPLATE = app
TARGET = window

QT += nativeappkitcontrols

SOURCES += main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/cpp/platforms/appkit/$$TARGET
INSTALLS += target
