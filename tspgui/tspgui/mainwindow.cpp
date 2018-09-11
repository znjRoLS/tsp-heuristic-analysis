#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <memory>

#include "tsp_util.h"

using std::make_unique;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (auto &world_generator : TSP::world_generators) {
        ui->combo_world_generator->addItem(QString::fromStdString(world_generator.first));
    }

    connect(ui->button_world_generator, SIGNAL(released()), this, SLOT(world_generator_action()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::world_generator_action() {
    string selected_world_generator = ui->combo_world_generator->currentText().toStdString();
    shared_ptr<TSP::WorldGenerator> world_generator = TSP::world_generators[selected_world_generator];
    int world_size = ui->spin_size_world_generator->value();

    world_ = shared_ptr<TSP::World>(world_generator->GenerateWorld(world_size));
}
