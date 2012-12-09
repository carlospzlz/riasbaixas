#include <Sea.h>
#include <ngl/VAOPrimitives.h>

Sea::Sea()
{
    m_depth = SEA_DEPTH;
    m_primName = "bunny";
}

void Sea::setDepth(float _depth)
{
    m_depth = _depth;
    m_primName = "sea";
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->createLineGrid("sea",2*m_depth, 2*m_depth, 2*m_depth);
}
