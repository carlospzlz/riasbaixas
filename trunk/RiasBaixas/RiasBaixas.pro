TARGET = RiasBaixas
QMAKE_CXX=clang++ -fdiagnostics-fixit-info

INCLUDEPATH += include
HEADERS += \
    include/Renderer.h \
    include/SpeedBoat.h \
    include/Sea.h \
    include/Controller.h \
    include/Floating.h \
    include/Stream.h \
    include/Ramp.h \
    include/PlayerControls.h \
    include/CameraManager.h \
    include/Object.h \
    include/SourceManager.h \
    include/ObjectManager.h \
    include/Parser.h \
    include/Diagonal.h \
    include/PoliceBoat.h \
    include/Horizontal.h \
    include/Vertical.h \
    include/ControllerManager.h \
    include/TXTParser.h \
    include/PhysicsEngine.h \
    include/BSpherePE.h

SOURCES += \
    src/SpeedBoat.cpp \
    src/Renderer.cpp \
    src/GameManager.cpp \
    src/Sea.cpp \
    src/Controller.cpp \
    src/Floating.cpp \
    src/PlayerControls.cpp \
    src/CameraManager.cpp \
    src/Object.cpp \
    src/SourceManager.cpp \
    src/ObjectManager.cpp \
    src/Diagonal.cpp \
    src/Horizontal.cpp \
    src/Vertical.cpp \
    src/ControllerManager.cpp \
    src/TXTParser.cpp \
    src/BSpherePE.cpp

OBJECTS_DIR = bin

#NGL library
INCLUDEPATH += $(HOME)/NGL/include
LIBS += -L$(HOME)/NGL/lib -l NGL

#OpenGL Extension Wrangler library (This library is used by NGL, not by you!!) at Dexter
#INCLUDEPATH += $(HOME)/glew-1.9.0/includeGL
LIBS += -L$(HOME)/glew-1.9.0/lib

#OpenGL QT
#INCLUDEPATH += $(HOME)/glew-1.9.0/include
QT += opengl

#now if we are under unix and not on a Mac (i.e. linux) define GLEW
#linux-clang {
#    DEFINES += LINUX
#    LIBS+= -lGLEW
#}
#linux-g++-64 {
#    DEFINES += LINUX
#    LIBS+= -lGLEW
#}

#SDL-2.0 library at dexter
#include at /usr/local/include
#libs at /usr/local/libs
LIBS+=$$system(sdl2-config  --libs)
#message(output from sdl-config --libs added to LIBS =$$LIBS)

#SDL_ttf libray for the lab workstation
INCLUDEPATH += $(HOME)/SDL_ttf-2.0/include
LIBS += -L$(HOME)/SDL_ttf-2.0/lib -lSDL_ttf

#include boost for tokenizer and reading from configFiles
INCLUDEPATH +=/usr/local/boost

CXX_FLAGS+=$$system(sdl-config  --cflags)
#message(output from sdl-config --cflags added to CXX_FLAGS= $$CXX_FLAGS)


# For the rubbish of WINDOWS
win32: {
        DEFINES+=USING_GLEW
        INCLUDEPATH+=-I c:/boost_1_44_0
        INCLUDEPATH+=-I c:/boost

        INCLUDEPATH+= -I C:/NGL/Support/glew
        LIBS+= -L C:/NGL/lib
        LIBS+= -lmingw32
        DEFINES += WIN32
        DEFINES += USING_GLEW
        DEFINES +=GLEW_STATIC
        DEFINES+=_WIN32
        SOURCES+=C:/NGL/Support/glew/glew.c
        INCLUDEPATH+=C:/NGL/Support/glew/
}

message(INCLUDEPATH: $$INCLUDEPATH)
message(LIBS: $$LIBS)
