#ifndef RENDERER_H
#define RENDERER_H

/**
 * @file Renderer.h
 * @brief this is the one in charge of setting and mantain the graphic context
 * and drawing the objects on the screen
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/TransformStack.h>
#include <ngl/Text.h>
#include "Sea.h"
#include "Object.h"

/**
 * @struct fontChar
 * @brief struct that stores the information of a character of one specific font
 */
struct fontChar
{
    int width;
    GLuint textureID;
    ngl::VertexArrayObject* billboard;
};

/**
 * @struct textVertData
 * @brief struct to map u v texture coordinates to vertices
 */
struct textVertData
   {
   ngl::Real x;
   ngl::Real y;
   ngl::Real u;
   ngl::Real v;
   };

/**
 * @class Renderer
 * @brief this is the one in charge of setting and mantaining the graphic context
 * and drawing the world on the screen (class in construction)
 */
class Renderer
{

private:
    /**
     * @brief the graphic library context
     */
    SDL_GLContext m_glContext;
    /**
     * @brief window of the graphic context where draw
     */
    SDL_Window *m_window;
    /**
     * @brief window width
     */
    int m_windowWidth;
    /**
     * @brief window height
     */
    int m_windowHeight;
    /**
     * @brief bool to specify if the window is in full screen mode
     */
    bool m_fullScreen;
    /**
     * @brief light of the world
     */
    ngl::Light *m_light;
    /**
     * @brief camera used for the rendering of still images
     */
    ngl::Camera m_stillImagesCamera;
    /**
     * @brief texture for used for tests
     */
    GLuint m_lena;
    /**
     * @brief draws the components of a vector on the screen
     */
    void drawVector(ngl::Vec4 _position, ngl::Vec4 _vector, ngl::Camera _cam);
    /**
     * @brief load all the matrices to the current active shader
     */
    inline void loadMatricesToShader(ngl::Transformation &_t, ngl::Camera &_cam);
    /**
     * @brief load just the Model View Projection matrix to the current active shader
     */
    inline void loadMVPToShader(ngl::Transformation &_t, ngl::Camera &_cam);
    /**
     * @brief render a plane image 2D on the screen (in construction)
     */
    void renderImage(float _width, float _height, GLuint _texture);
    /**
     * @brief to leave the application in a smart way
     */
    void SDLErrorExit(std::string msg);

public:
    Renderer() { }
    /**
     * @brief initilize the graphic context, create the shaders and everything needed for the rendering
     */
    void initGLContext();
    /**
     * @brief adjust the viewport when the window is resized
     */
    void resizeWindow();
    /**
     * @brief change to mode full screen
     */
    void fullScreen();
    bool isFullScreen() { return m_fullScreen; }
    /**
     * @brief leave full screen mode
     */
    void restoreWindow();
    int getWindowWidth() const { return m_windowWidth; }
    int getWindowHeight() const { return m_windowWidth; }
    /**
     * @brief normal render of the current scene with the background sea and the objects
     */
    void render(const Sea &_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam);
    /**
     * @brief render of the current scene with the background sea and the objects with
     * the option of any debug mode (1 for primitive mode and 2 for collision mode)
     */
    void render(const Sea &_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam, int _debugMode);
    /**
     * @brief load texture to memory
     */
    void loadTexture(std::string _path, GLuint &_texture);
    /**
     * @brief render a texture on a patch as a still image
     */
    void renderFrame(GLuint _texture);
    /**
     * @brief ganerated effect of fade out
     */
    void fadeOut();

};

#endif // RENDERER_H
