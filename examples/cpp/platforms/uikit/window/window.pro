TEMPLATE = app
TARGET = window

QT += uniuikitcontrols

LIBS += -framework UIKit

target.path = $$[QT_INSTALL_EXAMPLES]/cpp/platforms/uikit/$$TARGET
INSTALLS += target

OBJECTIVE_SOURCES += \
    main.mm
