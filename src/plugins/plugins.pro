TEMPLATE = subdirs

android: SUBDIRS += android
uikit:!watchos: SUBDIRS += uikit
