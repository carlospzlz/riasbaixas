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

    m_screen = SDL_SetVideoMode(720, 720, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);

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

    //To draw vectors we create the needed primitives
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->createCylinder("vectorModulus",0.02,2,6,1);
    prim->createCone("vectorSense",0.05,0.2,6,1);

    //Other shader that I don't really know what it is for
    shader->createShaderProgram("Colour");

    shader->attachShader("ColourVertex",ngl::VERTEX);
    shader->attachShader("ColourFragment",ngl::FRAGMENT);
    shader->loadShaderSource("ColourVertex","shaders/Colour.vs");
    shader->loadShaderSource("ColourFragment","shaders/Colour.fs");

    shader->compileShader("ColourVertex");
    shader->compileShader("ColourFragment");
    shader->attachShaderToProgram("Colour","ColourVertex");
    shader->attachShaderToProgram("Colour","ColourFragment");

    shader->bindAttribute("Colour",0,"inVert");
    shader->linkProgramObject("Colour");
    shader->setShaderParam4f("Colour",1,1,1,1);

    //To draw Text (segmentation fault if uncomment this)
    //m_text = new ngl::Text(QFont("Arial",18));

    //For removal or hidden surfaces
    glEnable(GL_DEPTH_TEST);

    SDL_GL_SwapBuffers();

    return true;
}

/*
void Renderer::setWorld(Sea *_sea, std::vector<Object*> *_objects)
{
    m_sea = _sea;
    m_objects = _objects;
    std::cout << "The renderer was told the world" << std::endl;
}
*/

void Renderer::render(Sea *_sea, std::vector<Object*> _objects, ngl::Camera &_cam)
{
    render(_sea, _objects, _cam, 0);
}

void Renderer::render(Sea *_sea, std::vector<Object*> _objects, ngl::Camera &_cam, int _debugMode)
{
    std::cout << "RENDERING..." << std::endl;

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
    ngl::Material m(ngl::GOLD);
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
    m_transformStack.popTransform();*/


    //DRAWING
    ngl::Mat4 MVP;
    ngl::Obj *mesh;
    ngl::VAOPrimitives *primitivesInstance = ngl::VAOPrimitives::instance();

    //Drawing Sea
    shader->use("Phong");
    //MVP=(*currentObject)->getTransform().getMatrix()*_cam.getVPMatrix();

    //shader->setShaderParamFromMat4("MVP",MVP);
    m_transformStack.getCurrentTransform().reset();
    loadMatricesToShader(m_transformStack,_cam);
    mesh = _sea->getMesh();

    if (_debugMode != 0 || !mesh)
    {
        //m_transform.set
        primitivesInstance->draw(_sea->getPrimName());
    }
    else
        mesh->draw();

    //Drawing objects of the world
    std::vector<Object*>::iterator lastObject = _objects.end();
    for(std::vector<Object*>::iterator currentObject = _objects.begin(); currentObject!=lastObject; ++currentObject)
    {
        if ((*currentObject)->isActive())
        {
            shader->use("Phong");
            m_transformStack.pushTransform();
            {
            MVP=(*currentObject)->getTransform().getMatrix()*_cam.getVPMatrix();
            shader->setShaderParamFromMat4("MVP",MVP);
            //loadMatricesToShader(m_transformStack,_cam);
            mesh = (*currentObject)->getMesh();

            if (_debugMode == 1 || !mesh)
            {
                //m_transform.set
                primitivesInstance->draw((*currentObject)->getPrimName());
                drawVector((*currentObject)->getPosition(),(*currentObject)->getVelocity(),_cam);
            }
            else if (_debugMode == 2)
            {
                mesh->drawBBox();
            }
            else
                mesh->draw();
            }

            //(*currentObject)->info();

            m_transformStack.popTransform();


            //m_transformStack.pushTransform();
            //loadMatricesToShader(m_transformStack,_cam);
            //(*currentObject)->draw("Phong", _cam, debugMode);
            //m_transformStack.popTransform();

        }
    }

/*
    std::vector<DynamicSeaElement>::iterator lastDse = m_dynamicSeaElements->end();
    for(std::vector<DynamicSeaElement>::iterator currentDse = m_dynamicSeaElements->begin(); currentDse!=lastDse; ++currentDse)
    {
        m_transformStack.pushTransform();
        loadMatricesToShader(m_transformStack,_cam);
        currentDse->draw("Phong", _cam, debugMode);
        m_transformStack.popTransform();
    }
*/
    //ts.popTransform();

    //ts.pushTransform();
    //m_transformStack.setPosition(0,4,0);
    //loadMatricesToShader(m_transformStack,_cam);
    //m_sea->draw("Phong", _cam);
    //ts.popTransform();

    SDL_GL_SwapBuffers(); //DO NOOOTT COMMENT THIS FUCKING LINE!!!!!!

    //renderTextToSurface("Hello World!",300,300,m_screen);

    //SDL_Flip(m_screen);
}

void Renderer::loadMatricesToShader(ngl::TransformStack &_tx, ngl::Camera _cam)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=_tx.getCurrAndGlobal().getMatrix();
  MV=  _tx.getCurrAndGlobal().getMatrix()*_cam.getViewMatrix();
  MVP= M*_cam.getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);
}

void Renderer::drawVector(ngl::Vec4 _position, ngl::Vec4 _vector, ngl::Camera _cam)
{
    ngl::VAOPrimitives *primitivesInstance = ngl::VAOPrimitives::instance();
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    ngl::TransformStack tx;
    const int scaleFactor = 5;

    shader->use("Colour");

    tx.pushTransform();
    {

    //COMPONENT X
    shader->setShaderParam4f("Colour",1,0,0,1);
    tx.setScale(2,2,_vector.m_x*scaleFactor);
    tx.setPosition(_position);
    tx.setRotation(0,-90,0);
    loadMatricesToShader(tx, _cam);
    primitivesInstance->draw("vectorModulus");
    tx.setScale(2,2,2);
    tx.setPosition(_position.m_x+2*_vector.m_x*scaleFactor,_position.m_y,_position.m_z);
    if (_vector.m_x>=0)
        tx.setRotation(0,90,0);
    loadMatricesToShader(tx, _cam);
    primitivesInstance->draw("vectorSense");

    //COMPONENT Y
    shader->setShaderParam4f("Colour",0,0,1,1);
    tx.setScale(2,2,_vector.m_y*scaleFactor);
    tx.setPosition(_position);
    tx.setRotation(90,0,0);
    loadMatricesToShader(tx, _cam);
    primitivesInstance->draw("vectorModulus");
    tx.setScale(2,2,2);
    tx.setPosition(_position.m_x,_position.m_y+2*_vector.m_y*scaleFactor,_position.m_z);
    if (_vector.m_y>=0)
        tx.setRotation(-90,0,0);
    loadMatricesToShader(tx, _cam);
    primitivesInstance->draw("vectorSense");

    //COMPONENT Z
    shader->setShaderParam4f("Colour",0,1,0,1);
    tx.setScale(2,2,_vector.m_z*scaleFactor);
    tx.setPosition(_position);
    tx.setRotation(0,180,0);
    loadMatricesToShader(tx, _cam);
    primitivesInstance->draw("vectorModulus");
    tx.setScale(2,2,2);
    tx.setPosition(_position.m_x,_position.m_y,_position.m_z+2*_vector.m_z*scaleFactor);
    if (_vector.m_z>0)
        tx.setRotation(0,0,0);
    loadMatricesToShader(tx, _cam);
    primitivesInstance->draw("vectorSense");

    }
    tx.popTransform();
}

void Renderer::renderTextToSurface(std::string _line, int _x, int _y, SDL_Surface *_surface)
{
    SDL_Color txtColour;
    txtColour.r = 0xFF;
    txtColour.r = 0xFF;
    txtColour.r = 0xFF;

    SDL_Surface *textSurface;
    SDL_Rect textRect;
    TTF_Font *font = TTF_OpenFont("font.tff",24);

    if (!(textSurface = TTF_RenderText_Solid(font,_line.c_str(), txtColour)))
    {
        SDL_FreeSurface(textSurface);
        std::cerr << "Renderer: ERROR when rendering text" << std::endl;
    }

    textRect.x = _x;
    textRect.y = _y;
    SDL_BlitSurface(textSurface,NULL,_surface,&textRect);

    //sdl flip??

    SDL_FreeSurface(textSurface);

    TTF_CloseFont(font);
}
