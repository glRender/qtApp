#ifndef MARK_H
#define MARK_H

#include "glRender.h"

namespace glRender {

class Mark : public Node
{
public:
  Mark(float r, float g, float b, float size);
  ~Mark();

  void update() override;
  void draw(Camera * camera) override;

  Model * model();
  const AABB * bb();

  void setPosition(Vec3 pos);
  void setPosition(float x, float y, float z);

  void changeColor();

private:
  Model * m_model;
  AABB * m_bb;

  float m_r;
  float m_g;
  float m_b;

};

}

#endif // MARK_H
