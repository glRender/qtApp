#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <GL/glew.h>
#include <QGLWidget>
#include "glRender.h"

#include <QTimer>

using namespace glRender;

class MyModel : public NodeModel
{
public:
    MyModel(Model * model) :
        NodeModel(model)
    {

    }

    void update() override
    {
//        model()->translate(0.01, 0.0, 0.0);
    }

};

class MyCamera : public NodeCamera
{
public:
    MyCamera(Camera * camera) :
        NodeCamera(camera)
    {

    }

    void draw(Camera * camera) override
    {

    }

    void update() override
    {
        camera()->translate(0.0, 0.0, 0.5);

        Vec3 p = camera()->position();

        camera()->translate(-p);
        camera()->rotate( -7, Vec3::AXE_Y() );
        camera()->rotate( -7, Vec3::AXE_Z() );
        camera()->translate(p);
    }

};


class glRenderQtWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit glRenderQtWidget(QWidget *parent = 0);
    Camera * camera;

private:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    QColor m_backgroundColor = QColor(1,0,0,1);

    Model * model0;
    Model * model1;

    Vec3 cameraPos;

    Scene * scene;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

signals:

public slots:

};

#endif // GLWINDOW_H
