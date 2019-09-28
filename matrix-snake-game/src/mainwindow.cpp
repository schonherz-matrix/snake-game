#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(this) {

    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->scale(10, 10);
    scene.setSlider(ui->slider);
    scene.setGrowthSwitch(ui->growthButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}
