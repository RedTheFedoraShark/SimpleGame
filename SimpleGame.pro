QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Game.cpp \
    actor.cpp \
    enums.cpp \
    gametextitem.cpp \
    main.cpp \
    tile.cpp \
    window.cpp

HEADERS += \
    Game.h \
    actor.h \
    enums.h \
    gametextitem.h \
    tile.h \
    window.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    config.json \
    psudocode.txt \
    todo.txt

RC_ICONS = game.ico
