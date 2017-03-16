TARGET = QtUniControls
MODULE = unicontrols
MODULE_PLUGIN_TYPES = unicontrols

QT += qml
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

UNI_CONTROLS = \
    base \
    window \
    view \
    control \
    button \
    textfield \
    searchfield \
    page \
    tabspage \
    tabspagetab

for(c,UNI_CONTROLS) {
    HEADERS += quni$${c}.h
    HEADERS += quni$${c}_p.h
    HEADERS += platform/quniplatform$${c}.h
    SOURCES += quni$${c}.cpp
}

HEADERS += \
    qunicontrolsglobal.h \
    quniplatformmanager_p.h \
    platform/qunicontrolsplatformplugin.h \
    quniqmlbase.h \
    quniqmlbase_p.h

SOURCES += \
    quniplatformmanager.cpp \
    quniqmlbase.cpp

load(qt_module)
