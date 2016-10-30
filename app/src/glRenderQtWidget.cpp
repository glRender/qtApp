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

        } else
        if ((int)(rand() % 3) == 2)
        {
            Mark * n = new Mark(0,1,0,1);
            n->model()->setWireframeMode(false);
            n->setPosition(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25)));
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

//    np = new Mark(1,0,0,1);
//    np->model()->setWireframeMode(true);
//    np->setPos( Vec3(0,0,0) );
//    scene->addNode(np);

    fp = new Mark(0,1,0,1);
    fp->model()->setWireframeMode(true);
    fp->setPosition(Vec3(0,0,0));
//    fp->model()->setPosition( 0,0,-3 );
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

void glRenderQtWidget::mouseReleaseEvent(QMouseEvent *event)
{
    float n = camera->nearPlane();
    float f = camera->farPlane();

    Vec2 normDeviceCoords(
                2.0f * (float)event->pos().x() / width() - 1.0f,
                1.0f - 2.0f * (float)event->pos().y() / height() );

    Vec4 clipCoords(
                normDeviceCoords.x,
                normDeviceCoords.y,
                -1.0f,
                1.0f );

    Mat4 p = camera->projectionMatrix();
    p.invert();
    Vec4 eyeCoords = p * clipCoords;
    eyeCoords.z = -1.0f;
    eyeCoords.w = 0.0f;

    Mat4 t = camera->transformationMatrix();
    t.invert();
    Vec4 tmp = t * eyeCoords;
    Vec3 worldCoords(tmp.x, tmp.y, tmp.z);
    worldCoords.normalize();

    Vec3 origin = camera->position() + worldCoords * n;
    Vec3 target = camera->position() + worldCoords * f;

    Ray * ray = new Ray(origin, target);

    scene->traverse([ray](Node * node) {
        Mark * m = dynamic_cast<Mark*>(node);
        if (m != nullptr)
        {
            if (m->bb()->intersects(ray))
            {
                m->changeColor();
                qDebug() << "Has intersection!";
            }
        }

    });

    qDebug() << origin.x << origin.y << origin.z << " -> " << target.x << target.y << target.z;

}
