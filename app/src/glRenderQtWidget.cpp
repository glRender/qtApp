#include "glRenderQtWidget.h"

#include <QDebug>

#include "Mark.hpp"
#include "WoodenBox.hpp"
#include "BrickBox.hpp"

glRenderQtWidget::glRenderQtWidget(QWidget *parent) :
    QGLWidget(parent)
{

}

void glRenderQtWidget::initializeGL()
{
    glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        printf("%s", glewGetErrorString(err));
    }

    if ( !GLEW_VERSION_3_3 )
    {
        printf ( "OpenGL 3.0 not supported.\n" );

        exit(-1);
    }

    // print context information
    printf ("**************************\n");
    printf ("Vendor: %s\n", glGetString (GL_VENDOR));
    printf ("Renderer: %s\n", glGetString (GL_RENDERER));
    printf ("Version: %s\n", glGetString (GL_VERSION));
    printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
    printf ("**************************\n");

    glClearColor ( 0.5, 0.5, 0.5, 1.0 );
    glEnable     ( GL_DEPTH_TEST );
    glDepthFunc  ( GL_LEQUAL );

    camera = new glRender::PerspectiveCamera( 90.0 / 180.0 * MATH_PI, 16.0f/9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());
//    camera->lookAt(Vec3(-10,0,-10), Vec3(10,0,-10), Vec3::AXE_Y());

    scene = new glRender::Scene();
    scene->setActiveCamera(camera);

    srand( time(0) );

    for (int i=0; i<1000; i++)
    {
        if ((int)(rand() % 3) == 0)
        {
            WoodenBox *n = new WoodenBox();
            n->model()->setPosition( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
            n->model()->setWireframeMode(false);
            scene->addNode(n);

        } else
        if ((int)(rand() % 3) == 1)
        {
            BrickBox *n = new BrickBox();
            n->model()->setPosition( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
            n->model()->setWireframeMode(false);
            scene->addNode(n);

        }
    }

    m_drawUpdater.setInterval(1);
    connect(&m_drawUpdater, &QTimer::timeout, this, [&]() {
        this->update();
    });
    m_drawUpdater.start();

    m_logicUpdater.setInterval(1);
    connect(&m_logicUpdater, &QTimer::timeout, this, [&]() {
        scene->update();
        emit updated();
    });
    m_logicUpdater.start();

    np = new Mark(1,0,0,1);
    np->model()->setPosition( 0,0,0 );
    scene->addNode(np);

    fp = new Mark(0,1,0,1);
    fp->model()->setPosition( 4,0,0 );
    scene->addNode(fp);

}

void glRenderQtWidget::resizeGL(int w, int h)
{
    glViewport ( 0, 0, (GLsizei)w, (GLsizei)h );

}

void glRenderQtWidget::paintGL()
{
    glClearColor ( 0.5, 0.5, 0.5, 1.0 );
    glEnable     ( GL_DEPTH_TEST );
    glDepthFunc  ( GL_LEQUAL );
    glClear      ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    scene->draw();
}

void glRenderQtWidget::mouseMoveEvent(QMouseEvent *event)
{
    Vec2 position((float)event->pos().x() / width(), (float)event->pos().y() / height());
    emit mousePositionChanged(position);

    Vec2 shiftedPosition = position - Vec2(0.5f, 0.5f);

    float n = /*camera->nearPlane()*/ 1.0;
    float f = /*camera->farPlane()*/ 10.0;
    float angle = camera->fieldOfView() / 2.0;

    float widthFarPlane = atan(angle) * f * 2;
    float widthNearPlane = atan(angle) * n * 2;

    Vec3 p0(shiftedPosition.x * widthNearPlane * camera->aspectRatio(), -shiftedPosition.y * widthNearPlane, -n);
    Vec3 p1(shiftedPosition.x * widthFarPlane * camera->aspectRatio(), -shiftedPosition.y * widthFarPlane, -f);

    Vec4 tmpP0(p0.x, p0.y, p0.z, 1.0);
    Vec4 tmpP1(p1.x, p1.y, p1.z, 1.0);

    Mat4 m = camera->transformationMatrix();
    m.invert();

    tmpP0 = m * tmpP0;
    tmpP1 = m * tmpP1;

    np->model()->setPosition(Vec3(tmpP0.x, tmpP0.y, tmpP0.z));
    fp->model()->setPosition(Vec3(tmpP1.x, tmpP1.y, tmpP1.z));

    qDebug() << p0.x << p0.y << p0.z << " " << p1.x << p1.y << p1.z;

}
