TARGET = QtNativeControls
CONFIG += internal_module

QT += qml
QT_PRIVATE += core-private gui-private qml-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

HEADERS += \
    $$PWD/qnativecontrolsglobal.h \
    $$PWD/qnativecontrol.h \
    $$PWD/qnativeapplicationwindow.h \
    $$PWD/qnativebutton.h

ios: include(ios/ios.pri)
android: include(android/android.pri)

load(qt_module)
