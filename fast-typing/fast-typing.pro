QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    def_sample_dialog.cpp \
    end_game.cpp \
    main.cpp \
    menu_actions.cpp \
    text_settings.cpp \
    win.cpp

HEADERS += \
    about.h \
    def_sample_dialog.h \
    end_game.h \
    text_settings.h \
    win.h

FORMS += \
    about.ui \
    def_sample_dialog.ui \
    end_game.ui \
    text_settings.ui \
    win.ui

TRANSLATIONS += \
    fast-typing_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    dark-theme.qss
