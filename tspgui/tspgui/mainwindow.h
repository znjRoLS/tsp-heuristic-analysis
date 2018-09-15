#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <memory>
#include "random_euclidean_world_generator.h"
#include "constructive_algorithm.h"
#include "improvement_algorithm.h"
#include "tspview.h"

using std::unique_ptr;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void WorldGeneratorSelected(const QString& text);
    void WorldGeneratorAction();

    void ConstructiveAlgorithmSelected(const QString& text);
    void ConstructiveAlgorithmIterateAction();
    void ConstructiveAlgorithmResetAction();

    void ImprovementAlgorithmSelected(const QString& text);
    void ImprovementAlgorithmIterateAction();
    void ImprovementAlgorithmResetAction();

private:

    enum ButtonState {
        WAITING,
        ITERATING,
        DONE,
    };

    enum SolutionState {
        START,
        WORLD_GENERATED,
        CONSTRUCTED_SOLUTION,
        IMPROVED_SOLUTION,
    };

    void UpdateUserControls();
    void SetButtonStatus(QPushButton* widget, ButtonState state);

    Ui::MainWindow *ui;
    TSPView* tspview_;
    TSPView* tspview_visualization_;

    shared_ptr<TSP::EuclideanWorldGenerator> world_generator_;
    shared_ptr<TSP::ConstructiveAlgorithm> constructive_algorithm_;
    shared_ptr<TSP::ImprovementAlgorithm> improvement_algorithm_;

    int generated_world_size_;
    shared_ptr<TSP::World> world_;

    shared_ptr<TSP::State> state_;

    SolutionState solution_state_;



};

#endif // MAINWINDOW_H
