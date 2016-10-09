#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    float cameraMoveSpeed = 0.7f;
    float cameraRotationSpeed = 10.0f;

    connect(ui->actionMoveForward, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "W clicked. To front";
        ui->glWidget->camera->lookAt(
                    ui->glWidget->camera->position() - Vec3::AXE_Z(),
                    Vec3(0,0,-100),
                    Vec3::AXE_Y());
//        qDebug() << "Position: " << QString(ui->glWidget->camera->position().toStdString());
        qDebug() << "***************";
        ui->glWidget->update();

    });

    connect(ui->actionMoveBack, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "S clicked. To back";
        ui->glWidget->camera->lookAt(ui->glWidget->camera->position() + Vec3::AXE_Z(), Vec3(0,0,-100), Vec3::AXE_Y());
//        qDebug() << "Position: " << QString(ui->glWidget->camera->position().toStdString());
        qDebug() << "***************";
        ui->glWidget->update();

    });

    connect(ui->actionMoveLeft, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "A clicked. To left";
        ui->glWidget->camera->lookAt(ui->glWidget->camera->position() - Vec3::AXE_X(), Vec3(0,0,0), Vec3::AXE_Y());
//        qDebug() << "Position: " << QString(ui->glWidget->camera->position().toStdString());
        qDebug() << "***************";
        ui->glWidget->update();

    });

    connect(ui->actionMoveRight, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "D clicked. To left";
        ui->glWidget->camera->lookAt(ui->glWidget->camera->position() + Vec3::AXE_X(), Vec3(0,0,0), Vec3::AXE_Y());
//        qDebug() << "Position: " << QString(ui->glWidget->camera->position().toStdString());
        qDebug() << "***************";
        ui->glWidget->update();

    });

    connect(ui->actionMove_up, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "Z clicked. To up";
        ui->glWidget->camera->lookAt(ui->glWidget->camera->position() + Vec3::AXE_Y(), Vec3(0,0,0), Vec3::AXE_Y());
//        qDebug() << "Position: " << QString(ui->glWidget->camera->position().toStdString());
        qDebug() << "***************";
        ui->glWidget->update();

    });

    connect(ui->actionMove_bottom, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "X clicked. To bottom";
        ui->glWidget->camera->lookAt(ui->glWidget->camera->position() - Vec3::AXE_Y(), Vec3(0,0,0), Vec3::AXE_Y());
//        qDebug() << "Position: " << QString(ui->glWidget->camera->position().toStdString());
        qDebug() << "***************";
        ui->glWidget->update();

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

    connect(ui->qButton, &QPushButton::clicked, this, [=](){
        ui->actionRotate_left->trigger();
    });

    connect(ui->eButton, &QPushButton::clicked, this, [=](){
        ui->actionRotate_right->trigger();
    });

    connect(ui->glWidget, &glRenderQtWidget::cameraPositionChanged, this, [this](Vec3 position) {
        ui->positionX->setText(QString::number(ui->glWidget->camera->position().x));
        ui->positionY->setText(QString::number(ui->glWidget->camera->position().y));
        ui->positionZ->setText(QString::number(ui->glWidget->camera->position().z));
    });

    connect(ui->glWidget, &glRenderQtWidget::cameraTargetChanged, this, [this](Vec3 target) {
        ui->targetX->setText(QString::number(ui->glWidget->camera->target().x));
        ui->targetY->setText(QString::number(ui->glWidget->camera->target().y));
        ui->targetZ->setText(QString::number(ui->glWidget->camera->target().z));
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
    addAction(ui->actionRotate_left);
    addAction(ui->actionRotate_right);

}

MainWindow::~MainWindow()
{
    delete ui;
}
