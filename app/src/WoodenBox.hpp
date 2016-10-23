#ifndef WOODENBOX_H
#define WOODENBOX_H

#include "glRender.h"

namespace glRender {

class WoodenBox : public Node
{
public:
  WoodenBox();

  ~WoodenBox();

  void update() override;

  void draw(Camera * camera) override;

  Model * model();

private:
  Model * m_model;

};

}

#endif // WOODENBOX_H
