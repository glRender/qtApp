#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <GL/glew.h>
#include <QGLWidget>
#include "glRender.h"

#include <QTimer>
#include <QMouseEvent>

using namespace glRender;

class MyModel : public Node
{
public:
  MyModel(Geometry* geometry, Textures* textures, ShaderProgram* shaderProgram)
  {
      m_model = new Model(geometry, textures, shaderProgram);
      m_model->setWireframeMode(false);
      m_model->setPosition(0.0, 0.0, 0.0);
  }

  ~MyModel()
  {

  }

  void update() override
  {
//      m_model->rotate(0.1, Vec3::AXE_Y());
  }

  void draw(Camera * camera) override
  {
      m_model->draw(camera);
  }

  Model * model()
  {
      return m_model;
  }

private:
  Model * m_model;

};

class MyModel0 : public Node
{
public:
  MyModel0(Geometry* geometry, Textures* textures, ShaderProgram* shaderProgram)
  {
      m_model = new Model(geometry, textures, shaderProgram);
      m_model->setWireframeMode(false);
      m_model->setPosition(0.0, 0.0, 0.0);
  }

  ~MyModel0()
  {

  }

  void update() override
  {
      m_model->rotate(-0.1, Vec3::AXE_Y());

      if (m_model->position().y < -25)
      {
          m_goBottom = false;

      } else
      if (m_model->position().y > 25)
      {
          m_goBottom = true;
      }

      if (m_goBottom)
      {
          m_model->translate(-0.1 * Vec3::AXE_Y());

      }
      else
      {
          m_model->translate(0.1 * Vec3::AXE_Y());

      }

  }

  void draw(Camera * camera) override
  {
      m_model->draw(camera);
  }

  Model * model()
  {
      return m_model;
  }

private:
  Model * m_model;

  bool m_goBottom = true;

};

class glRenderQtWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit glRenderQtWidget(QWidget *parent = 0);
    PerspectiveCamera * camera;

private:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mouseMoveEvent(QMouseEvent *event);

    QColor m_backgroundColor = QColor(1,0,0,1);

    Model *model0;
    Model *model1;

    MyModel *np;
    MyModel *fp;

    Vec3 cameraPos;

    Scene *scene;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

signals:
    void cameraPositionChanged(Vec3 position);
    void cameraTargetChanged(Vec3 target);
    void mousePositionChanged(Vec2 position);

public slots:

};

#endif // GLWINDOW_H
