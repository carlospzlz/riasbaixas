TARGET = RiasBaixas
QMAKE_CXX=clang++ -fdiagnostics-fixit-info

INCLUDEPATH += include
HEADERS += \
    include/Models.h \
    include/Renderer.h \
    include/SpeedBoat.h

SOURCES += \
    src/Models.cpp \
    src/SpeedBoat.cpp \
    src/Renderer.cpp \
    src/GameManager.cpp

OBJECTS_DIR = bin

#NGL library
INCLUDEPATH += $(HOME)/NGL/include
LIBS += -L$(HOME)/NGL/lib -l NGL

#OpenGL Extension Wrangler library (This library is used by NGL, not by you!!)
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

#SDL library
LIBS+=$$system(sdl-config  --libs)
message(output from sdl-config --libs added to LIBS =$$LIBS)

CXX_FLAGS+=$$system(sdl-config  --cflags)
message(output from sdl-config --cflags added to CXX_FLAGS= $$CXX_FLAGS)


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
