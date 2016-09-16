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

    connect(ui->actionMoveLeft, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        ui->glWidget->camera->translate( cameraMoveSpeed * -Vec3::AXE_X() );
        qDebug() << "a";
        ui->glWidget->update();
        qDebug() << "A clicked";
    });

    connect(ui->actionMoveRight, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        ui->glWidget->camera->translate( cameraMoveSpeed * Vec3::AXE_X() );
        qDebug() << "D clicked";
        ui->glWidget->update();
    });

    connect(ui->actionMoveForward, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        ui->glWidget->camera->translate( cameraMoveSpeed * Vec3::AXE_Z() );
        qDebug() << "W clicked";
        ui->glWidget->update();
    });

    connect(ui->actionMoveBack, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        ui->glWidget->camera->translate( cameraMoveSpeed * -Vec3::AXE_Z() );
        qDebug() << "S clicked";
        ui->glWidget->update();
    });

    connect(ui->actionRotate_left, &QAction::triggered, this, [this, cameraRotationSpeed ]() {
        ui->glWidget->camera->rotate( cameraRotationSpeed, Vec3::AXE_Y() );
        qDebug() << "Rotate left";
        ui->glWidget->update();
    });

    connect(ui->actionRotate_right, &QAction::triggered, this, [this, cameraRotationSpeed ]() {
        ui->glWidget->camera->rotate( -cameraRotationSpeed, Vec3::AXE_Y() );
        qDebug() << "Rotate right";
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

    connect(ui->qButton, &QPushButton::clicked, this, [=](){
        ui->actionRotate_left->trigger();
    });

    connect(ui->eButton, &QPushButton::clicked, this, [=](){
        ui->actionRotate_right->trigger();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
