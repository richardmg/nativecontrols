INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/quniandroidr_p.h \
    $$PWD/qtuniandroidglobal_p.h

SOURCES += \
    $$PWD/quniandroidr.cpp

include(app/app.pri)
include(core/core.pri)
include(content/content.pri)
include(graphics/graphics.pri)
include(support/support.pri)
include(view/view.pri)
include(widget/widget.pri)
