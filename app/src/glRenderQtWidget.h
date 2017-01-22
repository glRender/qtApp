#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <GL/glew.h>
#include <QOpenGLWidget>
#include "glRender.h"

#include <QTimer>
#include <QMouseEvent>

using namespace glRender;

namespace glRender {
    class Mark;
    class WoodenBox;
    class BrickBox;
    class Line;
}

class glRenderQtWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit glRenderQtWidget(QWidget *parent = 0);
    PerspectiveCamera * camera;

private:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void mouseReleaseEvent(QMouseEvent *event);

    QColor m_backgroundColor = QColor(1,0,0,1);

    Mark * np;
    Mark * fp;
    Line * l;

    Scene * scene;

    Render * render;

    NodePicker * nodePicker;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

    QString defaultResourcesPath = "./data";
    QString bashVarWithResourcesPath = "GL_RENDER_QT_APP_RESOURCES_PATH";

signals:
    void mousePositionChanged(Vec2 position);
    void updated();

public slots:

};

#endif // GLWINDOW_H
