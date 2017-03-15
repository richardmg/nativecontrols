TEMPLATE = app
TARGET = window

QT += uniappkitcontrols

OBJECTIVE_SOURCES += main.mm

LIBS += -framework AppKit

target.path = $$[QT_INSTALL_EXAMPLES]/cpp/platforms/appkit/$$TARGET
INSTALLS += target
