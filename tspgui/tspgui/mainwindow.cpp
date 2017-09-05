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
    button = new QPushButton("Hello world", this);
    result_label = new QLabel(this);

    connect(button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));
}

void MainWindow::slotButtonClicked(bool checked) {


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

      unique_ptr<TSP::Solver> solver (new TSP::Solver({5, 10000}, new WorldGeneratorRandom(), new AlgorithmBruteForce(), callbacks));

        solver->Solve();
}
