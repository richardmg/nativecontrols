INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/quniandroidgravity_p.h \
    $$PWD/quniandroidlayoutparams_p.h \
    $$PWD/quniandroidlayoutparams_p_p.h \
    $$PWD/quniandroidmenu_p.h \
    $$PWD/quniandroidmenu_p_p.h \
    $$PWD/quniandroidmenuitem_p.h \
    $$PWD/quniandroidview_p.h \
    $$PWD/quniandroidview_p_p.h \
    $$PWD/quniandroidviewgroup_p.h \
    $$PWD/quniandroidviewgroup_p_p.h \
    $$PWD/quniandroidwindow_p.h

SOURCES += \
    $$PWD/quniandroidlayoutparams.cpp \
    $$PWD/quniandroidmenu.cpp \
    $$PWD/quniandroidmenuitem.cpp \
    $$PWD/quniandroidview.cpp \
    $$PWD/quniandroidviewgroup.cpp \
    $$PWD/quniandroidwindow.cpp

include(animation/animation.pri)
