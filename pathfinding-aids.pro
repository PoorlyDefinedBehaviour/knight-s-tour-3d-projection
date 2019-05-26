TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        board/board.cpp \
        button/button.cpp \
        sdlcontroller/sdlcontroller.cpp \
        vector/vector.cpp \

HEADERS += \
        board/board.h \
        button/button.h \
        matrix/matrix.h \
        sdlcontroller/sdlcontroller.h \
        vector/vector.h

win32: LIBS += -L$$PWD/SDL2-2.0.9/x86_64-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/SDL2-2.0.9/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/SDL2-2.0.9/x86_64-w64-mingw32/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/SDL2-2.0.9/x86_64-w64-mingw32/lib/SDL2.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/SDL2-2.0.9/x86_64-w64-mingw32/lib/libSDL2.a
