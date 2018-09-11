#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->combo_world_generator->addItem("Random Euclidean World Generator");

    ui->

    connect(ui->button_world_generator, SIGNAL(released()), this, SLOT(world_generator_action()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::world_generator_action() {

}
