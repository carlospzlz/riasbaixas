#include <Sea.h>
#include <ngl/VAOPrimitives.h>

Sea::Sea(float _depth)
{
    m_depth = _depth;
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->createLineGrid("sea",SEA_DEPTH,SEA_DEPTH,SEA_DEPTH);
}

void Sea::draw(const std::string &_shader, ngl::Camera &_cam)
{
    //ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    //(*shader)[_shader]->use();

    //ngl::Mat4 MVP=m_transform.getMatrix()*_cam->getVPMatrix();

    //shader->setShaderParamFromMat4("MVP",MVP);
    //m_model->draw();
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->draw("sea");
}
