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

    glClearColor ( 0.5, 0.5, 0.5, 1.0 );
    glEnable     ( GL_DEPTH_TEST );
    glDepthFunc  ( GL_LEQUAL );

    camera = new glRender::PerspectiveCamera( 90.0 / 180.0 * MATH_PI, 16.0f/9.0f, 1.0f, 200.0f );
    camera->lookAt(Vec3(0,0,0), Vec3(0,0,-10), Vec3::AXE_Y());
//    camera->lookAt(Vec3(-10,0,-10), Vec3(10,0,-10), Vec3::AXE_Y());

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

    Geometry * geometry0 = GeometryHelper::Cube(0.001);
    Geometry * geometry01 = GeometryHelper::Cube(0.11);

    ShaderProgram * shaderProgram0 = new ShaderProgram("data/shader0.vertex", "data/shader0.frag");
    shaderProgram0->setAttribute( "vertex", AttributeType::XYZ);
    shaderProgram0->setAttribute( "uv", AttributeType::UV);

    ShaderProgram * shaderProgram1 = new ShaderProgram("data/shader1.vertex", "data/shader1.frag");
    shaderProgram1->setAttribute( "vertex", AttributeType::XYZ);

    ShaderProgram * spRed = new ShaderProgram("data/red.vertex", "data/red.frag");
    spRed->setAttribute( "vertex", AttributeType::XYZ);

    Textures * textures0 = new Textures();
    textures0->setTexture( "texture0", new Texture("data/Plywood_1024x640.png") );
//    textures0->setTexture( "texture0", new Texture("data/cube.png") );

    Textures * textures1 = new Textures();
    textures1->setTexture( "texture0", new Texture("data/TexturesCom_BricksSmallOld0080_1_seamless_S_1024x1024.png") );

    Textures * textures2 = new Textures();
    textures2->setTexture( "texture0", new Texture("data/a.png") );

    MyModel * n0 = new MyModel(geometry1, textures0, shaderProgram0);
//    scene->addNode(n0);

    int halfSize = 500;
    int volume = 2;
    MyModel * n1 = new MyModel(
                GeometryHelper::Plane(
                    Vec3(-halfSize, -volume, -halfSize),
                    Vec3(halfSize, -volume, -halfSize),
                    Vec3(-halfSize, -volume, halfSize),
                    Vec3(halfSize, -volume, halfSize)), textures0, shaderProgram0);
//    scene->addNode(n1);

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

    np = new MyModel(GeometryHelper::Cube(0.05f), textures0, shaderProgram0);
    np->model()->setPosition( 0,0,0 );
    np->model()->setWireframeMode(true);
    scene->addNode(np);

    fp = new MyModel(GeometryHelper::Cube(1.0f), textures0, shaderProgram0);
    fp->model()->setPosition( 0,0,0 );
    fp->model()->setWireframeMode(false);
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

    float n = camera->nearPlane() /*1.0*/;
    float f = camera->farPlane() /*10.0*/;
    float angle = camera->fieldOfView() / 2.0;

    float widthFarPlane = atan(angle) * f * 2;
    float widthNearPlane = atan(angle) * n * 2;

    Vec3 p0(shiftedPosition.x * widthNearPlane * camera->aspectRatio(), -shiftedPosition.y * widthNearPlane, -n);
    Vec3 p1(shiftedPosition.x * widthFarPlane * camera->aspectRatio(), -shiftedPosition.y * widthFarPlane, -f);

    np->model()->setPosition(p0);
    fp->model()->setPosition(p1);

    qDebug() << p0.x << p0.y << p0.z << " " << p1.x << p1.y << p1.z;

}
