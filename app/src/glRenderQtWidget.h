#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <GL/glew.h>
#include <QGLWidget>
#include "glRender.h"

#include <QTimer>
#include <QMouseEvent>

using namespace glRender;

namespace glRender {
    class Mark;
    class WoodenBox;
    class BrickBox;
}

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

    Model * model0;
    Model * model1;

    Mark * np;
    Mark * fp;

    Vec3 cameraPos;

    Scene * scene;

    QTimer m_drawUpdater;
    QTimer m_logicUpdater;

signals:
    void mousePositionChanged(Vec2 position);
    void updated();

public slots:

};

#endif // GLWINDOW_H
