TEMPLATE = subdirs

macos: SUBDIRS += appkit
uikit:!watchos: SUBDIRS += uikit
