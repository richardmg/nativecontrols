TEMPLATE = subdirs
SUBDIRS += \
    imports \
    platforms

imports.depends = platforms
