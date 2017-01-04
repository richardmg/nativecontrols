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

OBJECTIVE_SOURCES += \
    main.mm

target.path = $$[QT_INSTALL_EXAMPLES]/cpp/native/$$TARGET
INSTALLS += target
