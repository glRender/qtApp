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
        ui->glWidget->camera->setPosition( ui->glWidget->camera->position() + ui->glWidget->camera->front() * cameraMoveSpeed );
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMoveBack, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "S clicked. To back";
        ui->glWidget->camera->setPosition( ui->glWidget->camera->position() - ui->glWidget->camera->front() * cameraMoveSpeed );
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMoveLeft, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "A clicked. To left";
        ui->glWidget->camera->setPosition( ui->glWidget->camera->position() - ui->glWidget->camera->right() * cameraMoveSpeed );
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMoveRight, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "D clicked. To left";
        ui->glWidget->camera->setPosition( ui->glWidget->camera->position() + ui->glWidget->camera->right() * cameraMoveSpeed );
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMove_up, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "Z clicked. To up";
        ui->glWidget->camera->setPosition( ui->glWidget->camera->position() + ui->glWidget->camera->up() * cameraMoveSpeed );
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMove_bottom, &QAction::triggered, this, [this, cameraMoveSpeed]() {
        qDebug() << "X clicked. To bottom";
        ui->glWidget->camera->setPosition( ui->glWidget->camera->position() - ui->glWidget->camera->up() * cameraMoveSpeed );
        ui->glWidget->update();
        qDebug() << "***************";
    });

    connect(ui->actionMove_yawLeft, &QAction::triggered, this, [this, cameraRotationSpeed]() {
        qDebug() << "Q clicked. To up";

        ui->glWidget->camera->setEulerAngles( ui->glWidget->camera->pitch(), ui->glWidget->camera->yaw() - cameraRotationSpeed, ui->glWidget->camera->roll() );

        ui->glWidget->update();
        qDebug() << "***************";

    });

    connect(ui->actionMove_yawRight, &QAction::triggered, this, [this, cameraRotationSpeed]() {
        qDebug() << "E clicked. To up";

        ui->glWidget->camera->setEulerAngles( ui->glWidget->camera->pitch(), ui->glWidget->camera->yaw() + cameraRotationSpeed, ui->glWidget->camera->roll() );

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

        ui->frontX->setText(QString::number(ui->glWidget->camera->front().x, 'f', 2));
        ui->frontY->setText(QString::number(ui->glWidget->camera->front().y, 'f', 2));
        ui->frontZ->setText(QString::number(ui->glWidget->camera->front().z, 'f', 2));

        ui->rightX->setText(QString::number(ui->glWidget->camera->right().x, 'f', 2));
        ui->rightY->setText(QString::number(ui->glWidget->camera->right().y, 'f', 2));
        ui->rightZ->setText(QString::number(ui->glWidget->camera->right().z, 'f', 2));

        ui->upX->setText(QString::number(ui->glWidget->camera->up().x, 'f', 2));
        ui->upY->setText(QString::number(ui->glWidget->camera->up().y, 'f', 2));
        ui->upZ->setText(QString::number(ui->glWidget->camera->up().z, 'f', 2));

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
