#include "glRenderQtWidget.h"

#include <QDebug>

#include "Mark.hpp"
#include "WoodenBox.hpp"
#include "BrickBox.hpp"
#include "Line.hpp"

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

    nodePicker = new NodePicker(camera, scene);

    srand( time(0) );

    for (int i=0; i<512; i++)
    {
        if ((int)(rand() % 4) == 0)
        {
//            WoodenBox *n = new WoodenBox();
//            n->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
//            n->model()->setWireframeMode(false);
//            scene->addNode(n);

        } else
        if ((int)(rand() % 4) == 1)
        {
//            BrickBox *n = new BrickBox();
//            n->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
//            n->model()->setWireframeMode(false);
//            scene->addNode(n);

        } else
        if ((int)(rand() % 4) == 2)
        {
//            Mark * n = new Mark(0,1,0,1);
//            n->model()->setWireframeMode(false);
//            n->setOrigin(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25)));
//            scene->addNode(n);

        } else
        if ((int)(rand() % 4) == 3)
        {
            Vec3 p0 = Vec3(0,0,0);
            Vec3 p1 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
            Vec3 p2 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));

            Line * l = new Line(p0, p1, p2, 255);
//            n->setOrigin(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25)));
            scene->addNode(l);

        }
    }

    m_drawUpdater.setInterval(64);
    connect(&m_drawUpdater, &QTimer::timeout, this, [&]() {
        this->update();
    });
    m_drawUpdater.start();

    m_logicUpdater.setInterval(32);
    connect(&m_logicUpdater, &QTimer::timeout, this, [&]() {
        scene->update();
        emit updated();
    });
    m_logicUpdater.start();

//    np = new Mark(1,0,0,1);
//    np->model()->setWireframeMode(true);
//    np->setPos( Vec3(0,0,0) );
//    scene->addNode(np);

//    fp = new Mark(0,1,0,1);
//    fp->model()->setWireframeMode(true);
//    fp->setOrigin(Vec3(0,0,0));
//    scene->addNode(fp);

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
    Vec2 normDeviceCoords(
                2.0f * (float)event->pos().x() / width() - 1.0f,
                1.0f - 2.0f * (float)event->pos().y() / height() );

    std::vector<Mark *> selectedMarks = nodePicker->find<Mark>(normDeviceCoords);
    if (selectedMarks.size() > 0)
    {
        for (Mark * m : selectedMarks)
        {
            m->changeColor();
        }

        qDebug() << "Has intersection!";
    }

    std::vector<WoodenBox *> selectedWoodenBoxes = nodePicker->find<WoodenBox>(normDeviceCoords);
    if (selectedWoodenBoxes.size() > 0)
    {
        qDebug() << "Has intersection with " << selectedWoodenBoxes.size() << " woodenBxes";
    }


}
