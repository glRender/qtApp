#include "BrickBox.hpp"

namespace glRender {

BrickBox::BrickBox()
{
    Geometry * geometry = GeometryHelper::Cube(1.0);

    Textures * textures = new Textures();
    textures->setTexture( "texture0", ResourceManager::getInstance().getTexture("data/TexturesCom_BricksSmallOld0080_1_seamless_S_1024x1024.png") );

    ShaderProgram * shaderProgram = ResourceManager::getInstance().getShaderProgram("data/shader0.vertex", "data/shader0.frag");
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
    m_model->setOrigin(0.0, 0.0, 0.0);
}

BrickBox::~BrickBox()
{
    delete m_model;
    delete m_aabb;
}

void BrickBox::update()
{
//    m_model->rotate(0.1, Vec3::AXE_Y());
}

void BrickBox::draw(Camera *camera)
{
    m_model->draw(camera);
}

Model * BrickBox::model()
{
    return m_model;
}

AABB *BrickBox::bb()
{
    return m_aabb;
}

}
