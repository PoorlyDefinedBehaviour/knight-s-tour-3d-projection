TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    board/board.cpp \
    sdlcontroller/sdlcontroller.cpp \
    vector/vector.cpp \
    button/button.cpp

HEADERS += \
    board/board.h \
    matrix/matrix.h \
    sdlcontroller/sdlcontroller.h \
    vector/vector.h \
    button/button.h

win32: LIBS += -L$$PWD/../../Desktop/SDL2-2.0.9/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../Desktop/SDL2-2.0.9/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../../Desktop/SDL2-2.0.9/i686-w64-mingw32/include

win32: LIBS += -L$$PWD/SDL2-2.0.9/x86_64-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/SDL2-2.0.9/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/SDL2-2.0.9/x86_64-w64-mingw32/include
