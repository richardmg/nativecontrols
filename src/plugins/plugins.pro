TEMPLATE = subdirs

android: SUBDIRS += android
macos: SUBDIRS += appkit
uikit:!watchos: SUBDIRS += uikit
