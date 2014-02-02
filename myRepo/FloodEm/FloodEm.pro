QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FloodEm
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    board.cpp \
    colorsquare.cpp \
    colorbutton.cpp \
    sologame.cpp \
    mainmenu.cpp \
    endgamemessage.cpp \
    altturncompgame.cpp \
    compgameendmessage.cpp

HEADERS += \
    mainwindow.h \
    board.h \
    colorsquare.h \
    colorbutton.h \
    sologame.h \
    mainmenu.h \
    endgamemessage.h \
    altturncompgame.h \
    compgameendmessage.h
