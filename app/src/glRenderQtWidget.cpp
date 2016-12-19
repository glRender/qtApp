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

//void APIENTRY glDebugOutput(GLenum source,
//                            GLenum type,
//                            GLuint id,
//                            GLenum severity,
//                            GLsizei length,
//                            const GLchar *message,
//                            void *userParam)
//{
//    // ignore non-significant error/warning codes
//    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

//    std::cout << "---------------" << std::endl;
//    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

//    switch (source)
//    {
//        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
//        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
//        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
//        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
//        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
//        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
//    } std::cout << std::endl;

//    switch (type)
//    {
//        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
//        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
//        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
//        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
//        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
//        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
//        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
//        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
//        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
//    } std::cout << std::endl;

//    switch (severity)
//    {
//        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
//        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
//        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
//        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
//    } std::cout << std::endl;
//    std::cout << std::endl;
//}

void glRenderQtWidget::initializeGL()
{
//    if (GL_CONTEXT_FLAG_DEBUG_BIT)
//    {
//        glEnable(GL_DEBUG_OUTPUT);
//        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//        glDebugMessageCallback(glDebugOutput, nullptr);
//        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//    }

    if (!Render::glLoad())
    {
        exit(3);
    }

    printf("%s\n\n", Render::contextInformation());

    camera = new glRender::PerspectiveCamera( 90.0 / 180.0 * MATH_PI, 16.0f/9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());
//    camera->lookAt(Vec3(-10,0,-10), Vec3(10,0,-10), Vec3::AXE_Y());

    scene = new glRender::Scene();
    scene->setActiveCamera(camera);

    nodePicker = new NodePicker(camera, scene);

    srand( time(0) );

    for (int i=0; i<3000; i++)
    {
        if ((int)(rand() % 4) == 0)
        {
            WoodenBox *n = new WoodenBox();
            n->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
            n->model()->setWireframeMode(false);
            scene->addNode(n);

        } else
        if ((int)(rand() % 4) == 1)
        {
            BrickBox *n = new BrickBox();
            n->model()->setOrigin( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
            n->model()->setWireframeMode(false);
            scene->addNode(n);

        } else
        if ((int)(rand() % 4) == 2)
        {
            Mark * n = new Mark(0,1,0,1);
            n->model()->setWireframeMode(false);
            n->setOrigin(Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25)));
            scene->addNode(n);

        } else
        if ((int)(rand() % 4) == 3)
        {
            Vec3 p0 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
            Vec3 p1 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));
            Vec3 p2 = Vec3(((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25));

            float r = (rand() % 255) / 255.0;
            float g = (rand() % 255) / 255.0;
            float b = (rand() % 255) / 255.0;

            Line * l = new Line(p0, p1, p2, 512, r, g, b);
            scene->addNode(l);

        }
    }

    m_drawUpdater.setInterval(32);
    connect(&m_drawUpdater, &QTimer::timeout, this, [&]() {
        this->update();
    });
    m_drawUpdater.start();

    m_logicUpdater.setInterval(64);
    connect(&m_logicUpdater, &QTimer::timeout, this, [&]() {
        scene->update();
        emit updated();
    });
    m_logicUpdater.start();
}

void glRenderQtWidget::resizeGL(int w, int h)
{
    Render::setViewPortSize(w, h);
}

void glRenderQtWidget::paintGL()
{
    Render::draw(scene);
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
