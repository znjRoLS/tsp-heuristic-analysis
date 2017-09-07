#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Solver.h"
#include "SolverCallback.h"
#include "WorldGenerators.h"
#include "Algorithms.h"

using namespace TSP;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (auto &key_pair : TSP::algorithm_container) {
        ui->comboBoxAlgorithm->addItem(QString::fromStdString(key_pair.first));
    }
    for (auto &key_pair : TSP::world_generator_container) {
        ui->comboBoxWorldGenerator->addItem(QString::fromStdString(key_pair.first));
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_clicked()
{

    shared_ptr<SolverCallbacks> callbacks (new SolverCallbacks);

      callbacks->RegisterHandler(SolverCallbacks::ON_FINISH, [this] (SharedState state) {
        ui->result_label->setText(QString::fromStdString("OPalaaa " + state->ToString()));
      });

      WorldGenerator* world_generator = TSP::world_generator_container[ui->comboBoxWorldGenerator->currentText().toStdString()];
      Algorithm* algorithm = TSP::algorithm_container[ui->comboBoxAlgorithm->currentText().toStdString()];

      unique_ptr<TSP::Solver> solver (new TSP::Solver({5, 10000}, world_generator, algorithm, callbacks));

        solver->Solve();
}
