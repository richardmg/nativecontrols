TEMPLATE = subdirs
SUBDIRS += \
    controls \
    platforms \
    plugins \
    imports

platforms.depends = controls
plugins.depends = controls platforms
imports.depends = controls platforms
