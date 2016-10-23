#include "Mark.hpp"

namespace glRender {

Mark::Mark(float r, float g, float b, float size)
    : m_r(r)
    , m_g(g)
    , m_b(b)
{
    Geometry * geometry = GeometryHelper::Cube(size);

    Textures * textures = new Textures();

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/colored.vertex", "data/colored.frag");
    if (shaderProgram->hasAttribute("vertex"))
    {
        shaderProgram->setAttributeType( "vertex", AttributeType::XYZ );
    }

    if (shaderProgram->hasAttribute("uv"))
    {
        shaderProgram->setAttributeType( "uv", AttributeType::UV );
    }

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setPosition(0.0, 0.0, 0.0);
}

Mark::~Mark()
{

}

void Mark::update()
{
    //      m_model->rotate(0.1, Vec3::AXE_Y());
}

void Mark::draw(Camera *camera)
{
    m_model->shaderProgram()->setUniform("r", m_r);
    m_model->shaderProgram()->setUniform("g", m_g);
    m_model->shaderProgram()->setUniform("b", m_b);

    m_model->draw(camera);
}

Model *Mark::model()
{
    return m_model;
}

}


