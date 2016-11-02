#ifndef LINE_H
#define LINE_H

#include "glRender.h"

namespace glRender {

class Line : public Node
{
public:
  Line(Vec3 p0, Vec3 p1, Vec3 p2, uint segmentsNumber);
  ~Line();

  void update() override;
  void draw(Camera * camera) override;

  Model * model() override;
  IBoundingBox * bb() override;

private:
  Model * m_model;
  AABB * m_aabb;

};

}

#endif // LINE_H
