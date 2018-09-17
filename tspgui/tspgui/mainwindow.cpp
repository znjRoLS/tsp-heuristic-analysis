#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <memory>

#include "tsp_util.h"

using std::make_unique;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    solution_state_(SolutionState::START)
  //    world_generated_(false),
  //    constructive_algorithm_done_(false),
  //    improvement_algorithm_done_(false)
{
    ui->setupUi(this);
    tspview_ = ui->graphics_tsp;
    tspview_visualization_ = ui->graphics_tsp_visualization;

    for (auto &world_generator : TSP::world_generators) {
        ui->combo_world_generator->addItem(QString::fromStdString(world_generator.first));
    }
    for (auto &lower_bound_algorithm : TSP::lower_bound_algorithms) {
        ui->combo_lower_bound_algorithm->addItem(QString::fromStdString(lower_bound_algorithm.first));
    }
    for (auto &constructive_algorithm : TSP::constructive_algorithms) {
        ui->combo_constructive_algorithm->addItem(QString::fromStdString(constructive_algorithm.first));
    }
    for (auto &improvement_algorithm : TSP::improvement_algorithms) {
        ui->combo_improvement_algorithm->addItem(QString::fromStdString(improvement_algorithm.first));
    }

    connect(ui->combo_world_generator, SIGNAL(activated(const QString&)), this, SLOT(WorldGeneratorSelected(const QString&)));
    connect(ui->button_world_generator, SIGNAL(released()), this, SLOT(WorldGeneratorAction()));

    connect(ui->combo_lower_bound_algorithm, SIGNAL(activated(const QString&)), this, SLOT(LowerBoundAlgorithmSelected(const QString&)));
    connect(ui->button_iterate_lower_bound_algorithm, SIGNAL(released()), this, SLOT(LowerBoundAlgorithmIterateAction()));
    connect(ui->button_reset_lower_bound_algorithm, SIGNAL(released()), this, SLOT(LowerBoundAlgorithmResetAction()));

    connect(ui->combo_constructive_algorithm, SIGNAL(activated(const QString&)), this, SLOT(ConstructiveAlgorithmSelected(const QString&)));
    connect(ui->button_iterate_constructive_algorithm, SIGNAL(released()), this, SLOT(ConstructiveAlgorithmIterateAction()));
    connect(ui->button_reset_constructive_algorithm, SIGNAL(released()), this, SLOT(ConstructiveAlgorithmResetAction()));

    connect(ui->combo_improvement_algorithm, SIGNAL(activated(const QString&)), this, SLOT(ImprovementAlgorithmSelected(const QString&)));
    connect(ui->button_iterate_improvement_algorithm, SIGNAL(released()), this, SLOT(ImprovementAlgorithmIterateAction()));
    connect(ui->button_reset_improvement_algorithm, SIGNAL(released()), this, SLOT(ImprovementAlgorithmResetAction()));

    UpdateUserControls();

    WorldGeneratorSelected(ui->combo_world_generator->currentText());
    LowerBoundAlgorithmSelected(ui->combo_lower_bound_algorithm->currentText());
    ConstructiveAlgorithmSelected(ui->combo_constructive_algorithm->currentText());
    ImprovementAlgorithmSelected(ui->combo_improvement_algorithm->currentText());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetButtonStatus(QPushButton* widget, ButtonState status) {
    widget->setAutoFillBackground(true);
    QPalette pal = widget->palette();
    switch (status) {
    case (ButtonState::WAITING): {
        pal.setColor(widget->foregroundRole(), Qt::red);
        widget->setText("WAITING");
        break;
    }
    case (ButtonState::ITERATING): {
        pal.setColor(widget->foregroundRole(), Qt::blue);
        widget->setText("ITERATING");
        break;
    }
    case (ButtonState::DONE): {
        pal.setColor(widget->foregroundRole(), Qt::green);
        widget->setText("DONE");
        break;
    }
    }
    widget->setPalette(pal);
}

void MainWindow::UpdateUserControls() {

    switch(solution_state_) {
    case SolutionState::START: {
        ui->button_world_generator->setEnabled(true);

        ui->button_iterate_constructive_algorithm->setEnabled(false);
        ui->button_reset_constructive_algorithm->setEnabled(false);
        SetButtonStatus(ui->button_status_constructive_algorithm, ButtonState::WAITING);

        ui->button_iterate_improvement_algorithm->setEnabled(false);
        ui->button_reset_improvement_algorithm->setEnabled(false);
        SetButtonStatus(ui->button_status_improvement_algorithm, ButtonState::WAITING);
        break;
    }
    case SolutionState::WORLD_GENERATED: {
        ui->button_world_generator->setEnabled(true);

        ui->button_iterate_constructive_algorithm->setEnabled(true);
        ui->button_reset_constructive_algorithm->setEnabled(true);
        SetButtonStatus(ui->button_status_constructive_algorithm, ButtonState::ITERATING);

        ui->button_iterate_improvement_algorithm->setEnabled(false);
        ui->button_reset_improvement_algorithm->setEnabled(false);
        SetButtonStatus(ui->button_status_improvement_algorithm, ButtonState::WAITING);
        break;
    }
    case SolutionState::CONSTRUCTED_SOLUTION: {
        ui->button_world_generator->setEnabled(true);

        ui->button_iterate_constructive_algorithm->setEnabled(false);
        ui->button_reset_constructive_algorithm->setEnabled(true);
        SetButtonStatus(ui->button_status_constructive_algorithm, ButtonState::DONE);

        ui->button_iterate_improvement_algorithm->setEnabled(true);
        ui->button_reset_improvement_algorithm->setEnabled(true);
        SetButtonStatus(ui->button_status_improvement_algorithm, ButtonState::ITERATING);
        break;
    }
    case SolutionState::IMPROVED_SOLUTION: {
        ui->button_world_generator->setEnabled(true);

        ui->button_iterate_constructive_algorithm->setEnabled(false);
        ui->button_reset_constructive_algorithm->setEnabled(true);
        SetButtonStatus(ui->button_status_constructive_algorithm, ButtonState::DONE);

        ui->button_iterate_improvement_algorithm->setEnabled(false);
        ui->button_reset_improvement_algorithm->setEnabled(true);
        SetButtonStatus(ui->button_status_improvement_algorithm, ButtonState::DONE);
        break;
    }
    }
}

void MainWindow::WorldGeneratorSelected(const QString& text) {
    world_generator_ = TSP::world_generators[text.toStdString()];

    solution_state_ = SolutionState::START;

    UpdateUserControls();
}

void MainWindow::WorldGeneratorAction() {
    generated_world_size_ = ui->spin_size_world_generator->value();

    world_ = shared_ptr<TSP::World>(world_generator_->GenerateWorld(generated_world_size_));

    solution_state_ = SolutionState::WORLD_GENERATED;
    constructive_algorithm_->SetWorld(world_);
    constructive_algorithm_->Reset();
    UpdateUserControls();

    tspview_->UpdateContents(world_);
    tspview_visualization_->UpdateContents(world_);
}

void MainWindow::LowerBoundAlgorithmSelected(const QString& text) {
    lower_bound_algorithm_ = TSP::lower_bound_algorithms[text.toStdString()];

    if (solution_state_ == SolutionState::WORLD_GENERATED) {
        lower_bound_algorithm_->SetWorld(world_);
        lower_bound_algorithm_->Reset();
    }

    ui->spin_granularity_lower_bound_algorithm->setMaximum(lower_bound_algorithm_->GetMaxGranularity());

    UpdateUserControls();
}

void MainWindow::LowerBoundAlgorithmIterateAction() {
    int granularity = ui->spin_granularity_lower_bound_algorithm->value();

    if (!lower_bound_algorithm_->Iterate(granularity)) {
        double value_ = lower_bound_algorithm_->GetFinalValue();

        SetButtonStatus(ui->button_status_lower_bound_algorithm, ButtonState::DONE);
        ui->button_status_lower_bound_algorithm->setText(QString::number(value_));

        UpdateUserControls();

//        tspview_->UpdateContents(state_);
    }

    tspview_visualization_->UpdateContents(lower_bound_algorithm_->GetVisualization());

}

void MainWindow::LowerBoundAlgorithmResetAction() {
    lower_bound_algorithm_->Reset();
    UpdateUserControls();
}

void MainWindow::ConstructiveAlgorithmSelected(const QString& text) {
    constructive_algorithm_ = TSP::constructive_algorithms[text.toStdString()];

    if (solution_state_ == SolutionState::CONSTRUCTED_SOLUTION || solution_state_ == SolutionState::IMPROVED_SOLUTION) {
        solution_state_ = SolutionState::WORLD_GENERATED;
    }

    if (solution_state_ == SolutionState::WORLD_GENERATED) {
        constructive_algorithm_->SetWorld(world_);
        constructive_algorithm_->Reset();
    }

    ui->spin_granularity_constructive_algorithm->setMaximum(constructive_algorithm_->GetMaxGranularity());

    UpdateUserControls();
}

void MainWindow::ConstructiveAlgorithmIterateAction() {
    int granularity = ui->spin_granularity_constructive_algorithm->value();

    if (!constructive_algorithm_->Iterate(granularity)) {
        state_ = make_shared<TSP::State>(world_, constructive_algorithm_->GetFinalPath());
        solution_state_ = SolutionState::CONSTRUCTED_SOLUTION;
        improvement_algorithm_->SetState(state_);
        improvement_algorithm_->Reset();
        UpdateUserControls();

        tspview_->UpdateContents(state_);
    }

    tspview_visualization_->UpdateContents(constructive_algorithm_->GetVisualization());

}

void MainWindow::ConstructiveAlgorithmResetAction() {
    solution_state_ = SolutionState::WORLD_GENERATED;
    constructive_algorithm_->Reset();
    UpdateUserControls();

    tspview_->UpdateContents(world_);
}

void MainWindow::ImprovementAlgorithmSelected(const QString& text) {
    improvement_algorithm_ = TSP::improvement_algorithms[text.toStdString()];

    if (solution_state_ == SolutionState::IMPROVED_SOLUTION) {
        solution_state_ = SolutionState::CONSTRUCTED_SOLUTION;
    }

    if (solution_state_ == SolutionState::CONSTRUCTED_SOLUTION) {
        improvement_algorithm_->SetState(state_);
        improvement_algorithm_->Reset();
    }

    ui->spin_granularity_improvement_algorithm->setMaximum(improvement_algorithm_->GetMaxGranularity());

    UpdateUserControls();
}

void MainWindow::ImprovementAlgorithmIterateAction() {
    int granularity = ui->spin_granularity_improvement_algorithm->value();

    if (!improvement_algorithm_->Iterate(granularity)) {
        solution_state_ = SolutionState::IMPROVED_SOLUTION;
        UpdateUserControls();
    }

    tspview_->UpdateContents(state_);

    tspview_visualization_->UpdateContents(improvement_algorithm_->GetVisualization());
}

void MainWindow::ImprovementAlgorithmResetAction() {
    solution_state_ = SolutionState::CONSTRUCTED_SOLUTION;
    improvement_algorithm_->Reset();

    UpdateUserControls();
}
