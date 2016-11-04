#include "Mark.hpp"

namespace glRender {

Mark::Mark(float r, float g, float b, float size)
    : m_aabb(new AABB(Vec3(0,0,0), size))
    , m_r(r)
    , m_g(g)
    , m_b(b)
{
    setSelectable(true);
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

    shaderProgram->addUniform("r");
    shaderProgram->addUniform("g");
    shaderProgram->addUniform("b");

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setOrigin(0.0, 0.0, 0.0);
}

Mark::~Mark()
{
    delete m_aabb;
}

void Mark::update()
{
    m_model->rotate(0.1, Vec3::AXE_Y());
}

void Mark::draw(Camera *camera)
{
    m_model->shaderProgram()->setUniform1f("r", m_r);
    m_model->shaderProgram()->setUniform1f("g", m_g);
    m_model->shaderProgram()->setUniform1f("b", m_b);

    m_model->draw(camera);
}

Model * Mark::model()
{
    return m_model;
}

IBoundingBox * Mark::bb()
{
    return m_aabb;
}

void Mark::changeColor()
{
    if (m_r == 1 && m_g == 0 && m_b == 0)
    {
        m_r = 0;
        m_g = 1;
        m_b = 0;
    }
    else if (m_r == 0 && m_g == 1 && m_b == 0)
    {
        m_r = 1;
        m_g = 0;
        m_b = 0;
    }
}

}


