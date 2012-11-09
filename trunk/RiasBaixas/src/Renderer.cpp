#include "Renderer.h"
#include <ngl/NGLInit.h>


bool Renderer::initGLContext()
{
    // Black Background
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);

    //LOADING CONTEXT
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    SDL_SetVideoMode(720, 720, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);

    ngl::NGLInit *Init = ngl::NGLInit::instance();
    Init->initGlew();

    // now to load the shader and set the values
    // grab an instance of shader manager
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    // we are creating a shader called Phong
    shader->createShaderProgram("Phong");
    // now we are going to create empty shaders for Frag and Vert
    shader->attachShader("PhongVertex",ngl::VERTEX);
    shader->attachShader("PhongFragment",ngl::FRAGMENT);
    // attach the source
    shader->loadShaderSource("PhongVertex","shaders/Phong.vs");
    shader->loadShaderSource("PhongFragment","shaders/Phong.fs");
    // compile the shaders
    shader->compileShader("PhongVertex");
    shader->compileShader("PhongFragment");
    // add them to the program
    shader->attachShaderToProgram("Phong","PhongVertex");
    shader->attachShaderToProgram("Phong","PhongFragment");
    // now bind the shader attributes for most NGL primitives we use the following
    // layout attribute 0 is the vertex data (x,y,z)
    shader->bindAttribute("Phong",0,"inVert");
    // attribute 1 is the UV data u,v (if present)
    shader->bindAttribute("Phong",1,"inUV");
    // attribute 2 are the normals x,y,z
    shader->bindAttribute("Phong",2,"inNormal");

    // now we have associated this data we can link the shader
    shader->linkProgramObject("Phong");
    // and make it active ready to load values
    (*shader)["Phong"]->use();
    // the shader will use the currently active material and light0 so set them
    //ngl::Material m(ngl::GOLD);
    // load our material values to the shader into the structure material (see Vertex shader)
    //m.loadToShader("material");

    //For removal or hidden surfaces
    glEnable(GL_DEPTH_TEST);

    SDL_GL_SwapBuffers();

    return true;
}

void Renderer::setWorld(Sea *_sea, SpeedBoat *_sp)
{
    m_sea = _sea;
    m_speedBoat = _sp;
}

void Renderer::render(ngl::Camera &_cam)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    shader->setShaderParam3f("viewerPos",_cam.getEye().m_x,_cam.getEye().m_y,_cam.getEye().m_z);
    // now create our light this is done after the camera so we can pass the
    // transpose of the projection matrix to the light to do correct eye space
    // transformations
    ngl::Mat4 iv=_cam.getViewMatrix();
    iv.transpose();
    ngl::Light *m_light = new ngl::Light(ngl::Vec3(-2,5,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::POINTLIGHT );
    m_light->setTransform(iv);
    // load these values to the shader as well
    m_light->loadToShader("light");
    ngl::Material m(ngl::PEWTER);
    m.loadToShader("material");

    loadMatricesToShader(m_transformStack,_cam);


/*
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    m_transformStack.pushTransform();
    {
      m_transformStack.setPosition(1.0,0.35,1.0);
      m_transformStack.setScale(1.5,1.5,1.5);
      loadMatricesToShader(m_transformStack,_cam);
      prim->draw("troll");
    } // and before a pop
    m_transformStack.popTransform();
*/

    //DRAWING

    ngl::TransformStack ts;
    ts.pushTransform();

    ts.pushTransform();
    loadMatricesToShader(m_transformStack,_cam);
    m_sea->draw("Phong", &_cam);
    ts.popTransform();

    //ngl::Material m(ngl::GOLD);
    m.change(ngl::GOLD);
    m.loadToShader("material");

    loadMatricesToShader(m_transformStack,_cam);



    m_speedBoat->draw("Phong", &_cam);

    ts.popTransform();

    ts.pushTransform();
    m_transformStack.setPosition(0,4,0);
    loadMatricesToShader(m_transformStack,_cam);
    m_sea->draw("Phong", &_cam);
    ts.popTransform();


    //std::cout << "Rendering..." << std::endl;
    SDL_GL_SwapBuffers();
}

void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera m_cam)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=_tx.getCurrAndGlobal().getMatrix();
  MV=  _tx.getCurrAndGlobal().getMatrix()*m_cam.getViewMatrix();
  MVP= M*m_cam.getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);
}
