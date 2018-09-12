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

    tspview_ = ui->graphicsView;

    for (auto &world_generator : TSP::world_generators) {
        ui->combo_world_generator->addItem(QString::fromStdString(world_generator.first));
    }

    connect(ui->button_world_generator, SIGNAL(released()), this, SLOT(WorldGeneratorAction()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::WorldGeneratorAction() {
    string selected_world_generator = ui->combo_world_generator->currentText().toStdString();
    shared_ptr<TSP::EuclideanWorldGenerator> world_generator = TSP::world_generators[selected_world_generator];
    int world_size = ui->spin_size_world_generator->value();

    world_ = shared_ptr<TSP::World>(world_generator->GenerateWorld(world_size));

    tspview_->UpdateContents(world_);
}
