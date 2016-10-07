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

    camera = new glRender::PerspectiveCamera( 50.0 / 180.0 * MATH_PI, 16.0f/9.0f, 0.1f, 200.0f );
    camera->lookAt(Vec3(0,0,10), Vec3(0,0,0), Vec3::AXE_Y());

//    qDebug() << "Front: " << QString(camera->front().toStdString());
//    qDebug() << "Right: " << QString(camera->right().toStdString());
//    qDebug() << "Up: " << QString(camera->m_up.toStdString());
//    qDebug() << "Position: " << QString(camera->position().toStdString());

    scene = new glRender::Scene();
    scene->setActiveCamera(camera);

//    MyCamera * nc = new MyCamera(camera);
//    scene->addNode(nc);

//    Geometry * geometry0 = GeometryHelper::Cube(1.0);
    float halfSideSize = 1.0;
    std::vector<Vec3> vertices;
    /////////////
    vertices.push_back( Vec3(-0.5, 0.0, -1.0) );
    vertices.push_back( Vec3(-0.5, 0.5, -1.0) );
    vertices.push_back( Vec3(0.5,  0.5, -1.0) );
    /////////////
    vertices.push_back( Vec3(-0.5, 0.0, -1.0) );
    vertices.push_back( Vec3(0.5,  0.5, -1.0) );
    vertices.push_back( Vec3(0.5,  0.0, -1.0) );
    /////////////
    vertices.push_back( Vec3(-0.5, -1.0, -2.0) );
    vertices.push_back( Vec3(-0.5, 0.0, -1.0) );
    vertices.push_back( Vec3(0.5,  0.0, -1.0) );
    /////////////
    vertices.push_back( Vec3(-0.5, -1.0, -2.0) );
    vertices.push_back( Vec3( 0.5, 0.0, -1.0) );
    vertices.push_back( Vec3( 0.5, -1.0, -2.0) );


    std::vector<Vec2> uvs;
    uvs.push_back( Vec2(0.0f, 1.0f) );
    uvs.push_back( Vec2(0.0f, 0.0f) );
    uvs.push_back( Vec2(1.0f, 0.0f) );

    uvs.push_back( Vec2(0.0f, 1.0f) );
    uvs.push_back( Vec2(1.0f, 0.0f) );
    uvs.push_back( Vec2(1.0f, 1.0f) );

    uvs.push_back( Vec2(0.0f, 1.0f) );
    uvs.push_back( Vec2(0.0f, 0.0f) );
    uvs.push_back( Vec2(1.0f, 0.0f) );

    uvs.push_back( Vec2(0.0f, 1.0f) );
    uvs.push_back( Vec2(1.0f, 0.0f) );
    uvs.push_back( Vec2(1.0f, 1.0f) );

    Geometry * geometry1 = new Geometry();
    geometry1->setGeometryBuffer( "vertex", new GeometryBufferVec3( vertices ) );
    geometry1->setGeometryBuffer( "uv", new GeometryBufferVec2( uvs ) );

    Geometry * geometry0 = GeometryHelper::Cube(1.0);

    ShaderProgram * shaderProgram0 = new ShaderProgram("data/shader0.vertex", "data/shader0.frag");
    shaderProgram0->setAttribute( "vertex", AttributeType::XYZ);
    shaderProgram0->setAttribute( "uv", AttributeType::UV);

    ShaderProgram * shaderProgram1 = new ShaderProgram("data/shader1.vertex", "data/shader1.frag");
    shaderProgram1->setAttribute( "vertex", AttributeType::XYZ);

    Textures * textures0 = new Textures();
    textures0->setTexture( "texture0", new Texture("data/Plywood_1024x640.png") );
//    textures0->setTexture( "texture0", new Texture("data/cube.png") );

    Textures * textures1 = new Textures();
    textures1->setTexture( "texture0", new Texture("data/TexturesCom_BricksSmallOld0080_1_seamless_S_1024x1024.png") );

    Textures * textures2 = new Textures();
    textures2->setTexture( "texture0", new Texture("data/a.png") );

    MyModel * n0 = new MyModel(geometry1, textures0, shaderProgram0);
    scene->addNode(n0);

    int halfSize = 500;
    int volume = 2;
    MyModel * n1 = new MyModel(
                GeometryHelper::Plane(
                    Vec3(-halfSize, -volume, -halfSize),
                    Vec3(halfSize, -volume, -halfSize),
                    Vec3(-halfSize, -volume, halfSize),
                    Vec3(halfSize, -volume, halfSize)), textures0, shaderProgram0);
    scene->addNode(n1);

    srand( time(0) );

    for (int i=0; i<1000; i++)
    {
        if ((int)(rand() % 3) == 0)
        {
            MyModel *n;
            n = new MyModel(geometry0, textures0, shaderProgram0);
            n->model()->setPosition( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
            n->model()->setWireframeMode(false);

//            scene->addNode(n);

        } else
        if ((int)(rand() % 3) == 1)
        {
            MyModel0 *n;
            n = new MyModel0(geometry0, textures1, shaderProgram0);
            n->model()->setPosition( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
            n->model()->setWireframeMode(false);

//            scene->addNode(n);

        } else
        if ((int)(rand() % 3) == 2)
        {
            MyModel *n;
            n = new MyModel(geometry0, textures2, shaderProgram0);
            n->model()->setPosition( ((rand() % 50)) - 25, ((rand() % 50)) - 25, ((rand() % 50) - 25) );
            n->model()->setWireframeMode(false);

//            scene->addNode(n);

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
        emit cameraPositionChanged( camera->position() );
        emit cameraTargetChanged( camera->target() );

    });
    m_logicUpdater.start();

}

void glRenderQtWidget::resizeGL(int w, int h)
{
//    int minSide = qMin(w, h);
//    int x;
//    int y;

//    if (w > h)
//    {
//        x = minSide;//w / 2 - minSide / 2;
//        y = 0;
//    } else
//    if (w < h)
//    {
//        x = 0;
//        y = minSide;//h / 2 - minSide / 2;

//    }
//    if (w == h)
//    {
//        x = 0;
//        y = 0;
//    }

//    glViewport ( x, y, (GLsizei)minSide, (GLsizei)minSide );
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
}
