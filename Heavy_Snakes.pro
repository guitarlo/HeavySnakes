TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
SOURCES += \
        cbombs.cpp \
        cfnt.cpp \
        clevel.cpp \
        collision.cpp \
        crobby.cpp \
        ctimer.cpp \
        game.cpp \
        icelevel.cpp \
        main.cpp \
        menu.cpp \
        orb.cpp \
        sblogo.cpp \
        segment.cpp \
        snake.cpp \
        snowgame.cpp \
        sprite.cpp

HEADERS += \
    cbombs.h \
    cfnt.h \
    clevel.h \
    collision.h \
    crobby.h \
    ctimer.h \
    game.h \
    icelevel.h \
    menu.h \
    orb.h \
    sblogo.h \
    segment.h \
    snake.h \
    snowgame.h \
    sprite.h
