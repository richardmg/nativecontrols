TEMPLATE = app
TARGET = tst_view

QT += gui qml testlib uniuikitcontrols
CONFIG += testcase qtquickcompiler

LIBS += -framework UIKit

SOURCES += \
    $$PWD/tst_view.mm

RESOURCES += \
    testdata.qrc

include (../../shared/util.pri)
