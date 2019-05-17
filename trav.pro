TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sdlcontroller/sdlcontroller.cpp \
    board/board.cpp

HEADERS += \
    sdlcontroller/sdlcontroller.h \
    cell/cell.h \
    board/board.h

win32: LIBS += -L$$PWD/../../Desktop/SDL2-2.0.9/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../Desktop/SDL2-2.0.9/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../../Desktop/SDL2-2.0.9/i686-w64-mingw32/include
