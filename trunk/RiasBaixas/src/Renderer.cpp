#include "Renderer.h"
#include <ngl/NGLInit.h>
#include <sstream>


void Renderer::initGLContext()
{

    //INITIALIZE VIDEO SUBSYSTEM, IF YOU WANT TO USE AUDIO, JOYSTICKS ETC.. INIT THEM!
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        SDLErrorExit("Unable to initialize Video Subsystem");

    //CREATING WINDOW
    SDL_Rect screen;
    SDL_GetDisplayBounds(0,&screen);
    m_window = SDL_CreateWindow("Rias Baixas",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                screen.w/2, screen.h*3.0/4.0, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!m_window)
        SDLErrorExit("unable to create window");

    m_fullScreen = false;
    SDL_GetWindowSize(m_window,&m_windowWidth,&m_windowHeight);

    //CREATING OPENGL CONTEXT
    /*
    #ifdef  DARWIN
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    #endif
    */
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    m_glContext = SDL_GL_CreateContext(m_window);

    if (!m_glContext)
        SDLErrorExit("Unable to create GL Context");

    SDL_GL_MakeCurrent(m_window, m_glContext);
    SDL_GL_SetSwapInterval(1);

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    SDL_GL_SwapWindow(m_window);

    //INITIALIZING NGL
    ngl::NGLInit *Init = ngl::NGLInit::instance();
    Init->initGlew();

    //LOAD AND CONFIGURE THE SHADERS
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    //Phong
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

    //Shader for plane colours
    //shader->createShaderProgram("Colour");

    //shader->attachShader("ColourVertex",ngl::VERTEX);
    //shader->attachShader("ColourFragment",ngl::FRAGMENT);
    //shader->loadShaderSource("ColourVertex","shaders/Colour.vs");
    //shader->loadShaderSource("ColourFragment","shaders/Colour.fs");

    //shader->compileShader("ColourVertex");
    //shader->compileShader("ColourFragment");
    //shader->attachShaderToProgram("Colour","ColourVertex");
    //shader->attachShaderToProgram("Colour","ColourFragment");

    //shader->bindAttribute("Colour",0,"inVert");
    //shader->linkProgramObject("Colour");

    //Shader for textures
    shader->createShaderProgram("TextureShader");

    shader->attachShader("TextureVertex",ngl::VERTEX);
    shader->attachShader("TextureFragment",ngl::FRAGMENT);
    shader->loadShaderSource("TextureVertex","shaders/Vertex.vs");
    shader->loadShaderSource("TextureFragment","shaders/Fragment.fs");

    shader->compileShader("TextureVertex");
    shader->compileShader("TextureFragment");
    shader->attachShaderToProgram("TextureShader","TextureVertex");
    shader->attachShaderToProgram("TextureShader","TextureFragment");
    // bind our attributes for the vertex shader
    shader->bindAttribute("TextureShader",0,"inVert");
    shader->bindAttribute("TextureShader",1,"inUV");

    // link the shader no attributes are bound
    shader->linkProgramObject("TextureShader");

    //LIGHTS
    m_light = new ngl::Light(ngl::Vec3(-2,5,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::POINTLIGHT );

    //PRIMITIVES TO DRAW VECTORS
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->createCylinder("vectorModulus",0.02,2,6,1);
    prim->createCone("vectorSense",0.05,0.2,6,1);

    //PRIMITIVE TO DRAW BOUNDING BOX
    prim->createSphere("bSphere",1.0,10);

    //LOADING FONT TO RENDER TEXT
    loadFont("fonts/arial.ttf",22);

    //LOAD TEST TEXTURES
    loadTexture("images/lena.bmp", m_lena);
    prim->createTrianglePlane("plane",1,1,1,1,ngl::Vec3(0,1,0));

}

void Renderer::resizeWindow()
{
    SDL_GetWindowSize(m_window,&m_windowWidth,&m_windowHeight);
    glViewport(0,0,m_windowWidth,m_windowHeight);
    //set the cameras!
}

void Renderer::fullScreen()
{
    SDL_SetWindowFullscreen(m_window,SDL_TRUE);
    m_fullScreen = true;
}

void Renderer::restoreWindow()
{
    SDL_SetWindowFullscreen(m_window,SDL_FALSE);
    m_fullScreen = false;
}

void Renderer::render(const Sea &_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam)
{
    render(_sea, _objects, _cam, 0);
}

void Renderer::render(const Sea &_sea, const std::vector<Object*> &_objects, ngl::Camera &_cam, int _debugMode)
{

    std::cout << "RENDERING..." << std::endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);

    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    ngl::VAOPrimitives *primitives=ngl::VAOPrimitives::instance();
    ngl::Mat4 iv;
    ngl::Material material(ngl::GOLD);

    ngl::Transformation transform;
    std::vector<Object*>::const_iterator endObject = _objects.end();
    float sphereRadius;

    if (!_debugMode)
    {
        (*shader)["TextureShader"]->use();

        shader->setShaderParam3f("viewerPos",_cam.getEye().m_x,_cam.getEye().m_y,_cam.getEye().m_z);
        iv=_cam.getViewMatrix();
        iv.transpose();
        m_light->setTransform(iv);
        m_light->loadToShader("light");
        material.loadToShader("material");

        loadMVPToShader(transform, _cam);
        primitives->draw(_sea.getPrimName());

        for(std::vector<Object*>::const_iterator currentObject = _objects.begin(); currentObject!=endObject; ++currentObject)
        {
            if ((*currentObject)->isActive())
            {
                transform = (*currentObject)->getTransform();
                loadMVPToShader(transform,_cam);
                if ((*currentObject)->hasMesh())
                    (*currentObject)->getMesh()->draw();
                else
                    primitives->draw((*currentObject)->getPrimName());
                //(*currentObject)->info();
            }
        }
    }
    else if (_debugMode==1)
    {
        (*shader)["Phong"]->use();

        shader->setShaderParam3f("viewerPos",_cam.getEye().m_x,_cam.getEye().m_y,_cam.getEye().m_z);
        iv=_cam.getViewMatrix();
        iv.transpose();
        m_light->setTransform(iv);
        m_light->loadToShader("light");
        material.loadToShader("material");

        loadMatricesToShader(transform,_cam);
        primitives->draw(_sea.getPrimName());

        for(std::vector<Object*>::const_iterator currentObject = _objects.begin(); currentObject!=endObject; ++currentObject)
        {
            if ((*currentObject)->isActive())
            {
                transform = (*currentObject)->getTransform();
                loadMatricesToShader(transform,_cam);
                primitives->draw((*currentObject)->getPrimName());
                //(*currentObject)->info();
            }
        }

        (*shader)["nglColourShader"]->use();

        for(std::vector<Object*>::const_iterator currentObject = _objects.begin(); currentObject!=endObject; ++currentObject)
        {
            if ((*currentObject)->isActive()) {}
                drawVector((*currentObject)->getPosition(),(*currentObject)->getVelocity(),_cam);
        }
    }
    else if (_debugMode==2)
    {
        (*shader)["nglColourShader"]->use();
        shader->setShaderParam4f("Colour",1,1,1,1);

        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        loadMVPToShader(transform,_cam);
        primitives->draw(_sea.getPrimName());

        for(std::vector<Object*>::const_iterator currentObject = _objects.begin(); currentObject!=endObject; ++currentObject)
        {
            if ((*currentObject)->isActive())
            {
                if ((*currentObject)->isCollided())
                        shader->setShaderParam4f("Colour",1,0,0,1);
                else
                        shader->setShaderParam4f("Colour",1,1,1,1);

                if ((*currentObject)->hasMesh())
                {
                    transform = (*currentObject)->getTransform();
                    sphereRadius = (*currentObject)->getBSRadius()*(*currentObject)->getScale().m_x;
                    transform.setScale(sphereRadius, sphereRadius, sphereRadius);
                    loadMVPToShader(transform,_cam);
                    primitives->draw("bSphere");
                    //(*currentObject)->info();
                }
                else
                {
                    transform = (*currentObject)->getTransform();
                    loadMVPToShader(transform,_cam);
                    primitives->draw("bSphere");
                }
            }
        }
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        for(std::vector<Object*>::const_iterator currentObject = _objects.begin(); currentObject!=endObject; ++currentObject)
        {
            if ((*currentObject)->isActive())
                drawVector((*currentObject)->getPosition(),(*currentObject)->getVelocity(),_cam);
        }
    }
    /* DEBUG MODE FOR SOME TESTS
    else if (_debugMode==3)
    {
        (*shader)["TextureShader"]->use();
        shader->setShaderParam3f("viewerPos",_cam.getEye().m_x,_cam.getEye().m_y,_cam.getEye().m_z);

        transform.setPosition(0,0,_cam.getEye().m_z-10);
        //transform.setRotation(90,0,0);
        transform.setScale(5,5,5);
        loadMatricesToColour(transform,_cam);
        //renderText("hello World",m_windowWidth/2,m_windowHeight/2);
        renderImage(30,30,m_lena);
        primitives->draw("plane");
    }*/

    SDL_GL_SwapWindow(m_window);

}

inline void Renderer::loadMatricesToShader(ngl::Transformation &_transform, ngl::Camera &_cam)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=_transform.getMatrix();
  MV=  _transform.getMatrix()*_cam.getViewMatrix();
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
    ngl::Transformation transform;
    ngl::Mat4 MVP;
    const int scaleFactor = 5;

    //COMPONENT X
    shader->setShaderParam4f("Colour",1,0,0,1);
    transform.setScale(2,2,_vector.m_x*scaleFactor);
    transform.setPosition(_position);
    transform.setRotation(0,-90,0);
    loadMVPToShader(transform,_cam);
    primitivesInstance->draw("vectorModulus");

    transform.setScale(2,2,2);
    transform.setPosition(_position.m_x+2*_vector.m_x*scaleFactor,_position.m_y,_position.m_z);
    if (_vector.m_x>=0)
        transform.setRotation(0,90,0);
    loadMVPToShader(transform,_cam);
    primitivesInstance->draw("vectorSense");

    //COMPONENT Y
    shader->setShaderParam4f("Colour",0,0,1,1);
    transform.setScale(2,2,_vector.m_y*scaleFactor);
    transform.setPosition(_position);
    transform.setRotation(90,0,0);
    loadMVPToShader(transform,_cam);
    primitivesInstance->draw("vectorModulus");

    transform.setScale(2,2,2);
    transform.setPosition(_position.m_x,_position.m_y+2*_vector.m_y*scaleFactor,_position.m_z);
    if (_vector.m_y>=0)
        transform.setRotation(-90,0,0);
    loadMVPToShader(transform,_cam);
    primitivesInstance->draw("vectorSense");

    //COMPONENT Z
    shader->setShaderParam4f("Colour",0,1,0,1);
    transform.setScale(2,2,_vector.m_z*scaleFactor);
    transform.setPosition(_position);
    transform.setRotation(0,180,0);
    loadMVPToShader(transform,_cam);
    primitivesInstance->draw("vectorModulus");

    transform.setScale(2,2,2);
    transform.setPosition(_position.m_x,_position.m_y,_position.m_z+2*_vector.m_z*scaleFactor);
    if (_vector.m_z>0)
        transform.setRotation(0,0,0);
    loadMVPToShader(transform,_cam);
    primitivesInstance->draw("vectorSense");

}

inline void Renderer::loadMVPToShader(ngl::Transformation &_transform, ngl::Camera &_cam)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    ngl::Mat4 MVP;

    MVP = _transform.getMatrix()*_cam.getVPMatrix();
    shader->setShaderParamFromMat4("MVP",MVP);
}

bool Renderer::loadFont(std::string _fontFile, int _size)
{

    TTF_Init();

    //Font
    TTF_Font *font = TTF_OpenFont(_fontFile.c_str(),_size);
    TTF_SetFontStyle(font,TTF_STYLE_NORMAL);

    std::cout << "FONT: "<< font << std::endl;

    if (!font)
        SDLErrorExit("Error when loading font "+_fontFile);

    m_fontLineSkip = TTF_FontLineSkip(font);
    SDL_Color fontColour = {0xFF, 0xFF, 0xFF};
    SDL_Color fontBackground = {0,0xFF,0xFF};

    int fontHeight = TTF_FontHeight(font);
    int fontHeightPow2 = nearestPowerOfTwo(fontHeight);
    int fontWidth;
    int fontWidthPow2;

    //Surface
    SDL_Surface *billboardSurface;
    SDL_Surface *glyph;
    SDL_Rect area;

    //Texture
    GLint nOfColours;
    GLenum textureFormat;

    //Billboard
    ngl::Real s0;
    ngl::Real t0;
    ngl::Real s1;
    ngl::Real t1;
    textVertData billboardData[6];

    const char startChar = ' ';
    const char endChar = '~';

    std::cout << "Loading font " << _fontFile << std::endl;
    std::stringstream ss;
    std::string s;

    for (char c = startChar; c<=endChar; ++c)
    {

        std::cout << c << ": " ;

        //CREATING SDL_Surface FOR THE GLYPH IMAGE
        //charRenderedSurface = TTF_RenderText_Solid(font,&c,fontColour);
        //billboardSurface = TTF_RenderUTF8_Blended(font,&c,fontColour);
        glyph = TTF_RenderGlyph_Shaded(font,(int)c,fontColour,fontBackground);

        ss << "glyphs/" << c << ".bmp";
        s = ss.str();
        SDL_SaveBMP(glyph,s.c_str());
        ss.str("");

        std::cout << "saving in " << s << std::endl;

        //std::cout << "FORMAT:   " << (int)billboardSurface->format->BytesPerPixel << std::endl;
        //it has alpha channel

        fontWidth = glyph->w;
        fontWidthPow2 = nearestPowerOfTwo(fontWidth);

        //billboardSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,fontWidth,fontHeight,32,0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
        billboardSurface = glyph;
        nOfColours = billboardSurface->format->BytesPerPixel;

        if (nOfColours == 4)     // contains an alpha channel
        {
            if (billboardSurface->format->Rmask == 0x000000ff)
                textureFormat = GL_RGBA;
            else
                textureFormat = GL_BGRA;
         }
        else if (nOfColours == 3)     // no alpha channel
        {
            if (billboardSurface->format->Rmask == 0x000000ff)
                textureFormat = GL_RGB;
            else
                textureFormat = GL_BGR;
        }
        else
            std::cout << "Renderer: WARNING: the image is not truecolor..  this will probably break" << std::endl;

        //adding the width to the map of font characters
        m_font[c].width = fontWidth;

        std::cout << "Surface (" << fontWidth << "," << fontHeight << "): ";

        //LOADING TEXTURE
        // Have OpenGL generate a texture object handle for us
        glGenTextures(1, &(m_font[c].textureID));

        // Bind the texture object
        glBindTexture( GL_TEXTURE_2D, m_font[c].textureID);

        // Set the texture's stretching properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Edit the texture object's image data using the information SDL_Surface gives us
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColours, fontWidthPow2, fontHeightPow2,
                      0, textureFormat, GL_UNSIGNED_BYTE, billboardSurface->pixels );

        std::cout << "texture (" << fontWidthPow2 << "," << fontHeightPow2 << "): ";

        //GENERATING BILLBOARD

        s0 = 0.0;
        t0 = 0.0;

        if (m_fontBillboards.find(fontWidth) == m_fontBillboards.end())
        {
            s1 = fontWidth * 1.0/fontWidthPow2;
            t1 = fontHeight * 1.0/fontHeightPow2;

            //first triangle
            billboardData[0].x=0;
            billboardData[0].y=0;
            billboardData[0].u=s0;
            billboardData[0].v=t0;

            billboardData[1].x=fontWidth;
            billboardData[1].y=0;
            billboardData[1].u=s1;
            billboardData[1].v=t0;

            billboardData[2].x=0;
            billboardData[2].y=fontHeight;
            billboardData[2].u=s0;
            billboardData[2].v=t1;

            //second triangle
            billboardData[3].x=0;
            billboardData[3].y=fontHeight;
            billboardData[3].u=s0;
            billboardData[3].v=t1;

            billboardData[4].x=fontWidth;
            billboardData[4].y=0;
            billboardData[4].u=s1;
            billboardData[4].v=t0;

            billboardData[5].x=fontWidth;
            billboardData[5].y=fontHeight;
            billboardData[5].u=s1;
            billboardData[5].v=t1;

            //CREATING THE VAO
            ngl::VertexArrayObject *vao = ngl::VertexArrayObject::createVOA(GL_TRIANGLES);
            vao->bind();
            vao->setData(6*sizeof(textVertData),billboardData[0].x);
            vao->setVertexAttributePointer(0,2,GL_FLOAT,sizeof(textVertData),2);
            vao->setNumIndices(6);
            vao->unbind();

            m_fontBillboards[fontWidth] = vao;


            std::cout << "Billboard created: ";
        }
        else
            std::cout << "Billboard reused: ";

        //AND FINALLY...
        m_font[c].billboard = m_fontBillboards[fontWidth];

        std::cout << "character loaded" << std::endl;


        //TTF_GlyphMetrics(font,c,&minX,&maxX,NULL,NULL,NULL);
        //fc.width = nearestPowerOfTwo(maxX-minX);

        //billBoardSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,fontWidth,fontHeight,32,0,0,0,0);
        //SDL_FillRect(billBoardSurface,&billBoardSurface->clip_rect,SDL_MapRGBA(billBoardSurface->format,0,0,0,0));
    }

    SDL_FreeSurface(billboardSurface);

    TTF_CloseFont(font);
    //TTF_Quit();

    return true;
}

int Renderer::nearestPowerOfTwo(int _number)
{
    int pow2 = _number>0 ? _number-1 : 0;

    _number |= _number >> 1;
    _number |= _number >> 2;
    _number |= _number >> 4;
    _number |= _number >> 8;
    _number |= _number >> 16;
    ++_number;

    return _number;
}


void Renderer::renderText(std::string _text, float _x, float _y)
{
    std::cout << "rendering " << _text << std::endl;

    glActiveTexture(0);
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    //(*shader)["TextureShader"]->use();
    //shader->setRegisteredUniform3f("Colour",1,1,1);
    //shader->setRegisteredUniform1f("ScaleX",2.0/720);
    //shader->setRegisteredUniform1f("ScaleY",-2.0/720);
    //shader->setShaderParam1f("ypos",_y);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);

    fontChar fc;
    int nChar = _text.length();
    for(int i = 0; i<nChar; ++i)
    {
        //shader->setShaderParam1f("xpos",_x);
        fc = m_font[_text[i]];
        std::cout << _text[i] << " " << fc.textureID << " IN RENDERING TEXT LOOP" << std::endl;
        glBindTexture(GL_TEXTURE_2D, fc.textureID);
        fc.billboard->bind();
        fc.billboard->draw();
        fc.billboard->unbind();
        _x += fc.width;

        //std::cin.ignore();

    }
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::loadTexture(std::string _path, GLuint &_texture)
{
    SDL_Surface *surface = SDL_LoadBMP(_path.c_str());

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D,_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, nearestPowerOfTwo(surface->w), nearestPowerOfTwo(surface->h),
                 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);

    //std::cout << "number of colours: " << (int) lena->format->BytesPerPixel << std::endl;

    SDL_FreeSurface(surface);

}

void Renderer::renderImage(float _width, float _height, GLuint _texture)
{

    // billboard
    ngl::Real s0 = 0.0;
    ngl::Real t0 = 0.0;
    ngl::Real s1 = _width * 1.0 / nearestPowerOfTwo(_width);
    ngl::Real t1 = _height * 1.0 / nearestPowerOfTwo(_height);

    textVertData billboardData[6];

    //first triangle
    billboardData[0].x=0;
    billboardData[0].y=0;
    billboardData[0].u=0;
    billboardData[0].v=0;

    billboardData[1].x=_width;
    billboardData[1].y=0;
    billboardData[1].u=s1;
    billboardData[1].v=0;

    billboardData[2].x=0;
    billboardData[2].y=_height;
    billboardData[2].u=0;
    billboardData[2].v=t1;

    //second triangle
    billboardData[3].x=0;
    billboardData[3].y=_height;
    billboardData[3].u=0;
    billboardData[3].v=t1;

    billboardData[4].x=_width;
    billboardData[4].y=0;
    billboardData[4].u=s1;
    billboardData[4].v=0;

    billboardData[5].x=_width;
    billboardData[5].y=_height;
    billboardData[5].u=s1;
    billboardData[5].v=t1;

    //CREATING THE VAO
    ngl::VertexArrayObject *vao = ngl::VertexArrayObject::createVOA(GL_TRIANGLES);
    vao->bind();
    vao->setData(6*sizeof(textVertData),billboardData[0].x);
    vao->setVertexAttributePointer(0,2,GL_FLOAT,sizeof(textVertData),2);
    vao->setNumIndices(6);
    vao->unbind();

    //DRAWING VAO
    //glActiveTexture(0);
    //ngl::ShaderLib *shader= ngl::ShaderLib::instance();
    //(*shader)["TextureShader"]->use();
    //shader->setShaderParam1f("xpos",0);
    //shader->setShaderParam1f("ypos",0);
    //glEnable(GL_BLEND);
    //glDisable(GL_DEPTH_TEST);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBindTexture(GL_TEXTURE_2D, _texture);
    //vao->bind();;
    vao->draw();
    //vao->unbind();
    //glDisable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);

    std::cout << "Image rendered" <<std::endl;

    //std::cin.ignore();

}

void Renderer::SDLErrorExit(std::string msg)
{
    std::cerr << "Renderer: ERROR: ";
    std::cerr << msg << ": ";
    std::cerr << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(EXIT_FAILURE);
}
