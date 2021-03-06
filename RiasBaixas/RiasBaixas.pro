####################################
# 3D GAME PROJECT CONFIGURATION FILE
####################################

TARGET = RiasBaixas


##############
# SOURCE FILES
##############

HEADERS += \
    include/Renderer.h \
    include/SpeedBoat.h \
    include/Sea.h \
    include/Floating.h \
    include/PlayerControls.h \
    include/Object.h \
    include/Parser.h \
    include/Diagonal.h \
    include/PoliceBoat.h \
    include/Horizontal.h \
    include/Vertical.h \
    include/TXTParser.h \
    include/PhysicsEngine.h \
    include/BSpherePE.h \
    include/Utilities.h \
    include/CameraSet.h \
    include/Behaviour.h \
    include/SourceStore.h \
    include/GameState.h \
    include/Game.h \
    include/GamePlay.h \
    include/GameMenu.h \
    include/GameStory.h \
    include/Predator.h

SOURCES += \
    src/SpeedBoat.cpp \
    src/Renderer.cpp \
    src/Sea.cpp \
    src/Floating.cpp \
    src/PlayerControls.cpp \
    src/Object.cpp \
    src/Diagonal.cpp \
    src/Horizontal.cpp \
    src/Vertical.cpp \
    src/TXTParser.cpp \
    src/BSpherePE.cpp \
    src/Utilities.cpp \
    src/CameraSet.cpp \
    src/Behaviour.cpp \
    src/SourceStore.cpp \
    src/GamePlay.cpp \
    src/Game.cpp \
    src/GameMenu.cpp \
    src/GameStory.cpp \
    src/Parser.cpp \
    src/PoliceBoat.cpp \
    src/Predator.cpp


###################
# NEEDED LIBRARIES:
#
# NGL, opengl, glew
# boost
# SDL2, SDL2_ttf
###################


#######################
# GENERAL CONFIGURATION
#######################

QMAKE_CXX=clang++ -fdiagnostics-fixit-info -g

OBJECTS_DIR = obj

INCLUDEPATH += include

#OpenGL QT
QT += opengl

#include boost for tokenizer and reading from configFiles
INCLUDEPATH += /usr/local/boost

#SDL2
#QMAKE_CXXFLAGS+=$$system($$(HOME)/SDL2.0/bin/sdl2-config  --cflags)
#LIBS+=$$system($$(HOME)/SDL2.0/bin/sdl2-config  --libs)


##################################
# CONFIGURATION FOR DEXTER (MY PC)
##################################

#NGL library at dexter
INCLUDEPATH += $(HOME)/NGL/include
LIBS += -L$(HOME)/NGL/lib -l NGL

#OpenGL Extension Wrangler library at dexter
#INCLUDEPATH += $(HOME)/glew-1.9.0/includeGL
LIBS += -L$(HOME)/glew-1.9.0/lib

#SDL2 at dexter
LIBS+=$$system(sdl2-config --libs)


##################################
# CONFIGURATION FOR THE UNIVERSITY
##################################

#SDL2 library at the University
INCLUDEPATH += $(HOME)/SDL-2.0/include
#INCLUDEPATH += $(HOME)/SDL2_ttf-2.0/include

#SDL2_ttf library at the University
LIBS += -L$(HOME)/SDL-2.0/lib -lSDL2
LIBS += -L$(HOME)/SDL-2.0/lib -lSDL2_ttf
LIBS += -L$(HOME)/SDL-2.0/lib -lSDL2_image
DEFINES += LINUX
LIBS+= -lGLEW


########################################
# For the rubbish of WINDOWS, no offense
########################################

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


###############
# PRINTING INFO
###############

message(INCLUDEPATH: $$INCLUDEPATH)
message(LIBS: $$LIBS)
