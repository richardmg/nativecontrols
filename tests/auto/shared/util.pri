QT += core-private gui-private qml-private

HEADERS += $$PWD/util.h
SOURCES += $$PWD/util.cpp

DEFINES += QT_QMLTEST_DATADIR=\\\"$${_PRO_FILE_PWD_}/data\\\"
