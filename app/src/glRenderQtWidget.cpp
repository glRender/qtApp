#include "glRenderQtWidget.h"

#include <QDebug>

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

    glClearColor ( 0.5, 0.5, 0.5, 1.0111 );
    glEnable     ( GL_DEPTH_TEST );
    glDepthFunc  ( GL_LEQUAL );

    camera = new glRender::PerspectiveCamera( 50.0 / 180.0 * MATH_PI, 1.0, 0.1f, 200.0f );
//    camera->rotate(180, Vec3::AXE_Y());
//    camera->translate(50*Vec3::AXE_Z());

    scene = new glRender::Scene();
    scene->setActiveCamera(camera);

    MyCamera * nc = new MyCamera(camera);
    scene->addNode(nc);

    Geometry * geometry0 = GeometryHelper::Cube(1.0);

    ShaderProgram * shaderProgram0 = new ShaderProgram("data/shader0.vertex", "data/shader0.frag");
    shaderProgram0->setAttribute( "vertex", AttributeType::XYZ);
    shaderProgram0->setAttribute( "uv", AttributeType::UV);

    Textures * textures0 = new Textures();
    textures0->setTexture( "texture0", new Texture("data/a.png") );
    textures0->setTexture( "texture1", new Texture("data/a.png") );

    model0 = new Model(geometry0, textures0, shaderProgram0);
    model0->setWireframeMode(false);
    model0->setPosition(0.0, 0.0, 0.0);

    MyModel * n0 = new MyModel(model0);
    scene->addNode(n0);

    srand( time(0) );

    for (int i=0; i<10; i++)
    {
        for (int j=0; j<10; j++)
        {
            for (int k=0; k<10; k++)
            {
                model1 = new Model(GeometryHelper::Cube(1.0), textures0, shaderProgram0);
                model1->setWireframeMode(false);
                model1->setPosition( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );

                MyModel *n = new MyModel(model1);
                scene->addNode(n);
            }
        }
    }

//    m_drawUpdater.setInterval(16);
//    connect(&m_drawUpdater, &QTimer::timeout, this, [&]() {
//        this->update();
//    });
//    m_drawUpdater.start();

    m_logicUpdater.setInterval(16);
    connect(&m_logicUpdater, &QTimer::timeout, this, [&]() {
        scene->update();
        this->update();
    });
    m_logicUpdater.start();

}

void glRenderQtWidget::resizeGL(int w, int h)
{
    int minSide = qMin(w, h);
    int x;
    int y;

    if (w > h)
    {
        x = w / 2 - minSide / 2;
        y = 0;
    } else
    if (w < h)
    {
        x = 0;
        y = h / 2 - minSide / 2;

    }
    if (w == h)
    {
        x = 0;
        y = 0;
    }

        glViewport ( x, y, (GLsizei)minSide, (GLsizei)minSide );
}

void glRenderQtWidget::paintGL()
{
    glClearColor ( 0.5, 0.5, 0.5, 1.0 );
    glEnable     ( GL_DEPTH_TEST );
    glDepthFunc  ( GL_LEQUAL );
    glClear      ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    scene->draw();
}
