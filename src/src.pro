TEMPLATE = subdirs
SUBDIRS += \
    nativecontrols \
    platforms \
    plugins \
    imports

platforms.depends = nativecontrols
plugins.depends = nativecontrols platforms
imports.depends = nativecontrols platforms
