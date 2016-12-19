TEMPLATE = subdirs
SUBDIRS += \
    qml \
    cpp

android: SUBDIRS += nativeandroid/catalog
