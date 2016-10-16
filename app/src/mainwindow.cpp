#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    float cameraMoveSpeed = 0.3f;
    float cameraRotationSpeed = 5.0f;

    connect(ui->actionMoveForward, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "W clicked. To front";
        ui->glWidget->camera->shift(ui->glWidget->camera->front() * cameraMoveSpeed);
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMoveBack, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "S clicked. To back";
        ui->glWidget->camera->shift(-ui->glWidget->camera->front() * cameraMoveSpeed);
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMoveLeft, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "A clicked. To left";
        ui->glWidget->camera->shift(-ui->glWidget->camera->right() * cameraMoveSpeed);
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMoveRight, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "D clicked. To left";
        ui->glWidget->camera->shift(ui->glWidget->camera->right() * cameraMoveSpeed);
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMove_up, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "Z clicked. To up";
        ui->glWidget->camera->shift(ui->glWidget->camera->up() * cameraMoveSpeed);
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMove_bottom, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "X clicked. To bottom";
        ui->glWidget->camera->shift(-ui->glWidget->camera->up() * cameraMoveSpeed);
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMove_yawLeft, &QAction::triggered, this, [this, cameraRotationSpeed]() {
        qDebug() << "Q clicked. To up";

        Vec3 newPos = ui->glWidget->camera->position();

        Vec3 newTarget = ui->glWidget->camera->target() - ui->glWidget->camera->position();
        Vec4 tmp(newTarget.x, newTarget.y, newTarget.z, 1.0f);
        Mat4 rotationMatrix;
        rotationMatrix.rotate(cameraRotationSpeed, 0,1,0);
        tmp = rotationMatrix * tmp;
        newTarget.set(tmp.x, tmp.y, tmp.z);
        newTarget = newTarget + ui->glWidget->camera->position();

        Vec3 newUp = ui->glWidget->camera->up();

        ui->glWidget->camera->lookAt(
                    newPos,
                    newTarget,
                    newUp);

        ui->glWidget->update();
        qDebug() << "***************";

    });

    connect(ui->actionMove_yawRight, &QAction::triggered, this, [this, cameraRotationSpeed]() {
        qDebug() << "E clicked. To up";

        Vec3 newPos = ui->glWidget->camera->position();

        Vec3 newTarget = ui->glWidget->camera->target() - ui->glWidget->camera->position();
        Vec4 tmp(newTarget.x, newTarget.y, newTarget.z, 1.0f);
        Mat4 rotationMatrix;
        rotationMatrix.rotate(-cameraRotationSpeed, 0,1,0);
        tmp = rotationMatrix * tmp;
        newTarget.set(tmp.x, tmp.y, tmp.z);
        newTarget = newTarget + ui->glWidget->camera->position();

        Vec3 newUp = ui->glWidget->camera->up();

        ui->glWidget->camera->lookAt(
                    newPos,
                    newTarget,
                    newUp);

        ui->glWidget->update();
        qDebug() << "***************";

    });

    connect(ui->actionExit, &QAction::triggered, this, [this]() {
        this->close();
    });

    connect(ui->aButton, &QPushButton::clicked, this, [this](){
        ui->actionMoveLeft->trigger();
    });

    connect(ui->dButton, &QPushButton::clicked, this, [=](){
        ui->actionMoveRight->trigger();
    });

    connect(ui->wButton, &QPushButton::clicked, this, [=]() {
        ui->actionMoveForward->trigger();
    });

    connect(ui->sButton, &QPushButton::clicked, this, [=](){
        ui->actionMoveBack->trigger();
    });

    connect(ui->zButton, &QPushButton::clicked, this, [=]() {
        ui->actionMove_up->trigger();
    });

    connect(ui->xButton, &QPushButton::clicked, this, [=](){
        ui->actionMove_bottom->trigger();
    });

    connect(ui->glWidget, &glRenderQtWidget::updated, this, [this]() {
        ui->positionX->setText(QString::number(ui->glWidget->camera->position().x, 'f', 2));
        ui->positionY->setText(QString::number(ui->glWidget->camera->position().y, 'f', 2));
        ui->positionZ->setText(QString::number(ui->glWidget->camera->position().z, 'f', 2));

        ui->targetX->setText(QString::number(ui->glWidget->camera->target().x, 'f', 2));
        ui->targetY->setText(QString::number(ui->glWidget->camera->target().y, 'f', 2));
        ui->targetZ->setText(QString::number(ui->glWidget->camera->target().z, 'f', 2));

        ui->dirX->setText(QString::number(ui->glWidget->camera->normalizedDirection().x, 'f', 2));
        ui->dirY->setText(QString::number(ui->glWidget->camera->normalizedDirection().y, 'f', 2));
        ui->dirZ->setText(QString::number(ui->glWidget->camera->normalizedDirection().z, 'f', 2));

    });

    connect(ui->glWidget, &glRenderQtWidget::mousePositionChanged, this, [this](Vec2 position) {
//        qDebug() << position.toStdString();

    });

    addAction(ui->actionMoveBack);
    addAction(ui->actionMoveForward);
    addAction(ui->actionMoveLeft);
    addAction(ui->actionMoveRight);
    addAction(ui->actionMove_up);
    addAction(ui->actionMove_bottom);
    addAction(ui->actionMove_yawLeft);
    addAction(ui->actionMove_yawRight);

}

MainWindow::~MainWindow()
{
    delete ui;
}
