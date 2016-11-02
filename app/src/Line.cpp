#include "Line.hpp"

namespace glRender {

Line::Line(Vec3 p0, Vec3 p1, Vec3 p2, uint segmentsNumber)
    : m_aabb(new AABB(Vec3(0,0,0), 1.0))
{
    setSelectable(false);
    Geometry * geometry = GeometryHelper::QuadraticBezierCurve(p0, p1, p2, segmentsNumber);

    Textures * textures = new Textures();

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/colored.vertex", "data/colored.frag");
    if (shaderProgram->hasAttribute("vertex"))
    {
        shaderProgram->setAttributeType( "vertex", AttributeType::XYZ );
    }

    m_model = new Model(geometry, textures, shaderProgram);
    m_model->setWireframeMode(false);
    m_model->setDrawMode(Model::DrawMode::Lines);
    m_model->setOrigin(0.0, 0.0, 0.0);
}

Line::~Line()
{
    delete m_aabb;
}

void Line::update()
{
    m_model->rotate(0.1, Vec3::AXE_Y());
}

void Line::draw(Camera *camera)
{
    m_model->draw(camera);
}

Model * Line::model()
{
    return m_model;
}

IBoundingBox * Line::bb()
{
    return m_aabb;
}

}
