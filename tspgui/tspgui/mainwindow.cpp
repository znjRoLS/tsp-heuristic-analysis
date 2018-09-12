#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <memory>

#include "tsp_util.h"

using std::make_unique;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    world_generated_(false),
    constructive_algorithm_done_(false),
    improvement_algorithm_done_(false)
{
    ui->setupUi(this);
    tspview_ = ui->graphics_tsp;

    for (auto &world_generator : TSP::world_generators) {
        ui->combo_world_generator->addItem(QString::fromStdString(world_generator.first));
    }
    for (auto &constructive_algorithm : TSP::constructive_algorithms) {
        ui->combo_constructive_algorithm->addItem(QString::fromStdString(constructive_algorithm.first));
    }
    for (auto &improvement_algorithm : TSP::improvement_algorithms) {
        ui->combo_improvement_algorithm->addItem(QString::fromStdString(improvement_algorithm.first));
    }

    connect(ui->combo_world_generator, SIGNAL(activated(const QString&)), this, SLOT(WorldGeneratorSelected(const QString&)));
    connect(ui->button_world_generator, SIGNAL(released()), this, SLOT(WorldGeneratorAction()));

    connect(ui->combo_constructive_algorithm, SIGNAL(activated(const QString&)), this, SLOT(ConstructiveAlgorithmSelected(const QString&)));
    connect(ui->button_iterate_constructive_algorithm, SIGNAL(released()), this, SLOT(ConstructiveAlgorithmIterateAction()));
    connect(ui->button_reset_constructive_algorithm, SIGNAL(released()), this, SLOT(ConstructiveAlgorithmResetAction()));

    connect(ui->combo_improvement_algorithm, SIGNAL(activated(const QString&)), this, SLOT(ImprovementAlgorithmSelected(const QString&)));
    connect(ui->button_iterate_improvement_algorithm, SIGNAL(released()), this, SLOT(ImprovementAlgorithmIterateAction()));
    connect(ui->button_reset_improvement_algorithm, SIGNAL(released()), this, SLOT(ImprovementAlgorithmResetAction()));

    WorldGeneratorSelected(ui->combo_world_generator->currentText());
    ConstructiveAlgorithmSelected(ui->combo_constructive_algorithm->currentText());
    ImprovementAlgorithmSelected(ui->combo_improvement_algorithm->currentText());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::WorldGeneratorSelected(const QString& text) {
    world_generator_ = TSP::world_generators[text.toStdString()];

    WorldGeneratorReset();
}

void MainWindow::WorldGeneratorAction() {
    generated_world_size_ = ui->spin_size_world_generator->value();

    world_ = shared_ptr<TSP::World>(world_generator_->GenerateWorld(generated_world_size_));
    SetWorldGeneratorDone(true);

    tspview_->UpdateContents(world_);
}

void MainWindow::WorldGeneratorReset() {
    SetWorldGeneratorDone(false);
}

void MainWindow::SetWorldGeneratorDone(bool done) {
    world_generated_ = done;

    ConstructiveAlgorithmResetAction();
}

void MainWindow::ConstructiveAlgorithmSelected(const QString& text) {
    constructive_algorithm_ = TSP::constructive_algorithms[text.toStdString()];
    ConstructiveAlgorithmResetAction();
}

void MainWindow::ConstructiveAlgorithmIterateAction() {
    int granularity = ui->spin_granularity_constructive_algorithm->value();

    if (!constructive_algorithm_->Iterate(granularity)) {
        state_ = make_shared<TSP::State>(world_, constructive_algorithm_->GetFinalPath());
        SetConstructiveAlgorithmDone(true);

//        tspview_->UpdateContents();
    }
}

void MainWindow::ConstructiveAlgorithmResetAction() {

    if (world_generated_) {
        constructive_algorithm_->SetWorld(world_);
        constructive_algorithm_->Reset();
    }

    SetConstructiveAlgorithmDone(false);
}

void MainWindow::SetConstructiveAlgorithmDone(bool done) {
    constructive_algorithm_done_ = done;
    QPalette pal = palette();

    ui->button_iterate_constructive_algorithm->setEnabled(world_generated_ && !constructive_algorithm_done_);

    if (done) {
        pal.setColor(QPalette::Background, Qt::green);
    } else {
        pal.setColor(QPalette::Background, Qt::red);
    }
    ui->button_done_constructive_algorithm->setPalette(pal);

    ImprovementAlgorithmResetAction();
}

#include <iostream>

void MainWindow::ImprovementAlgorithmSelected(const QString& text) {
    improvement_algorithm_ = TSP::improvement_algorithms[text.toStdString()];
    ImprovementAlgorithmResetAction();
}

void MainWindow::ImprovementAlgorithmIterateAction() {
    int granularity = ui->spin_granularity_improvement_algorithm->value();

    if (!improvement_algorithm_->Iterate(granularity)) {
        SetImprovementAlgorithmDone(true);

//        tspview_->UpdateContents();
    }
}

void MainWindow::ImprovementAlgorithmResetAction() {
    if (constructive_algorithm_done_) {
        improvement_algorithm_->SetState(state_);
        improvement_algorithm_->Reset();
    }

    SetImprovementAlgorithmDone(false);
}

void MainWindow::SetImprovementAlgorithmDone(bool done) {
    improvement_algorithm_done_ = done;
    QPalette pal = palette();

    ui->button_iterate_improvement_algorithm->setEnabled(constructive_algorithm_done_ && !improvement_algorithm_done_);

    if (done) {
        pal.setColor(QPalette::Background, Qt::green);
    } else {
        pal.setColor(QPalette::Background, Qt::red);
    }
    ui->button_done_improvement_algorithm->setPalette(pal);
}
