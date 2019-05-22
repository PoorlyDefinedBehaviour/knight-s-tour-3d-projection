TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board/board.cpp \
    matrix/matrix.cpp \
    sdlcontroller/sdlcontroller.cpp \
    vector/vector.cpp \
    button/button.cpp


win32: LIBS += -L$$PWD/../../Desktop/SDL2-devel-2.0.9-mingw/SDL2-2.0.9/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../Desktop/SDL2-devel-2.0.9-mingw/SDL2-2.0.9/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../../Desktop/SDL2-devel-2.0.9-mingw/SDL2-2.0.9/i686-w64-mingw32/include

HEADERS += \
    board/board.h \
    matrix/matrix.h \
    sdlcontroller/sdlcontroller.h \
    vector/vector.h \
    button/button.h
