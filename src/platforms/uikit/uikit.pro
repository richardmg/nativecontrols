TARGET = QtUniUIKitControls
MODULE = uniuikitcontrols

QT += qml
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

LIBS += -framework CoreGraphics -framework Foundation -framework UIKit

IOS_CONTROLS = \
    qmlbase \
    base \
    responder \
    window \
    view \
    control \
    button \
    textfield \
    textfielddelegate \
    searchfield \
    label \
    slider \
    tableview \
    tableviewcell \
    tableviewdatasource \
    viewcontroller \
    tabbarcontroller \
    tabbaritem \
    indexpath \
    range

for(c,IOS_CONTROLS) {
    HEADERS += quniuikit$${c}.h
    HEADERS += quniuikit$${c}_p.h
    SOURCES += quniuikit$${c}.mm
}

HEADERS += \
    quniuikitcontrolsglobal.h \
    quniuikitpropertymacros_p.h

OTHER_FILES += \
    templates/quniuikittemplatecontrol.h.template \
    templates/quniuikittemplatecontrol_p.h.template \
    templates/quniuikittemplatecontrol.mm.template \
    templates/create

load(qt_module)
