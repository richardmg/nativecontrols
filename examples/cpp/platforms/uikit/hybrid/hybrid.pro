TEMPLATE = app
TARGET = hybrid

QT += nativecontrols nativeuikitcontrols
LIBS += -framework UIKit

OBJECTIVE_SOURCES += \
    main.mm

target.path = $$[QT_INSTALL_EXAMPLES]/cpp/platforms/uikit/$$TARGET
INSTALLS += target
