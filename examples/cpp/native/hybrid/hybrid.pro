TEMPLATE = app
TARGET = hybrid

QT += nativecontrols

macos {
    QT += nativeappkitcontrols
    LIBS += -framework AppKit
}

uikit:!watchos {
    QT += nativeuikitcontrols
    LIBS += -framework UIKit
}

SOURCES += \
    main.cpp

darwin: OBJECTIVE_SOURCES += \
    main_objc.mm

target.path = $$[QT_INSTALL_EXAMPLES]/cpp/native/$$TARGET
INSTALLS += target
