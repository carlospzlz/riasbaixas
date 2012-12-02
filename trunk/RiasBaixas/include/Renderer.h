#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/TransformStack.h>
#include <ngl/Text.h>
#include "Sea.h"
#include "Object.h"

struct fontChar
{
    int width;
    GLuint textureID;
    ngl::VertexArrayObject* billboard;
};

struct textVertData
   {
   ngl::Real x;
   ngl::Real y;
   ngl::Real u;
   ngl::Real v;
   };

class Renderer
{

private:
    SDL_GLContext m_glContext;
    SDL_Window *m_window;
    int m_windowWidth;
    int m_windowHeight;
    bool m_fullScreen;
    ngl::Light *m_light;
    std::map<char,fontChar> m_font;
    std::map<int, ngl::VertexArrayObject*> m_fontBillboards;
    int m_fontLineSkip;
    ngl::TransformStack m_transformStack;
    bool loadFont(std::string _fontFile, int _size);
    int nearestPowerOfTwo(int _number);
    void drawVector(ngl::Vec4 _position, ngl::Vec4 _vector, ngl::Camera _cam);
    inline void loadMatricesToPhong(ngl::Transformation &_t, ngl::Camera &_cam);
    inline void loadMatricesToColour(ngl::Transformation &_t, ngl::Camera &_cam);
    void renderText(std::string _text, float _x, float _y);
    void renderTextToSurface(std::string _line, int _x, int _y, SDL_Surface *_surface);
    void testTexturing();
    void SDLErrorExit(std::string msg);

public:
    Renderer() { };
    void initGLContext();
    void resizeWindow();
    void fullScreen();
    bool isFullScreen() { return m_fullScreen; }
    void restoreWindow();
    int getWindowWidth() const { return m_windowWidth; }
    int getWindowHeight() const { return m_windowWidth; }
    void render(const Sea &_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam);
    void render(const Sea &_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam, int _debugMode);
    //void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);

};

#endif // RENDERER_H
