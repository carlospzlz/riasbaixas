#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

class Window
{

private:
    SDL_Surface *m_screen;

public:
    bool initGLContext();
    void flip() { SDL_Flip(m_screen); }

};

#endif // WINDOW_H
