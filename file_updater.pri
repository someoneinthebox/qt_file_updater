FILE_UPDATER_VERSION = 1.0.0

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/controller_fu.h \
    $$PWD/protocol_fu.h \
    $$PWD/gui_fu.h \
    $$PWD/downloader_fu.h

SOURCES += \
    $$PWD/controller_fu.cpp \
    $$PWD/protocol_fu.cpp \
    $$PWD/gui_fu.cpp \
    $$PWD/downloader_fu.cpp

FORMS += \
    $$PWD/gui_fu.ui
