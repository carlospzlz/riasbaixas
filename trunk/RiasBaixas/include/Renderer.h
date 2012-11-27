#ifndef RENDERER_H
#define RENDERER_H

#include <SDL/SDL.h>
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
    SDL_Surface *m_screen;
    ngl::Light *m_light;
    std::map<char,fontChar> m_font;
    std::map<int, ngl::VertexArrayObject> m_fontBillboards;
    int m_fontLineSkip;
    ngl::TransformStack m_transformStack;
    void loadFont(std::string _fontFile, int _size);
    int nearestPowerOfTwo(int _number);
    void drawVector(ngl::Vec4 _position, ngl::Vec4 _vector, ngl::Camera _cam);
    void loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera _cam);
    void Renderer::renderText(std::string _text, float _x, float _y);
    void renderTextToSurface(std::string _line, int _x, int _y, SDL_Surface *_surface);

public:
    Renderer() { };
    bool initGLContext();
    void render(const Sea *_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam);
    void render(const Sea *_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam, int _debugMode);
    //void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam);

};

#endif // RENDERER_H
