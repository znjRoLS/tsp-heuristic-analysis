#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void WorldGeneratorReset();
    void SetWorldGeneratorDone(bool done);

    void ConstructiveAlgorithmSelected(const QString& text);
    void ConstructiveAlgorithmIterateAction();
    void ConstructiveAlgorithmResetAction();
    void SetConstructiveAlgorithmDone(bool done);

    void ImprovementAlgorithmSelected(const QString& text);
    void ImprovementAlgorithmIterateAction();
    void ImprovementAlgorithmResetAction();
    void SetImprovementAlgorithmDone(bool done);

private:
    Ui::MainWindow *ui;
    TSPView* tspview_;

    shared_ptr<TSP::EuclideanWorldGenerator> world_generator_;
    shared_ptr<TSP::ConstructiveAlgorithm> constructive_algorithm_;
    shared_ptr<TSP::ImprovementAlgorithm> improvement_algorithm_;

    bool world_generated_;
    int generated_world_size_;
    shared_ptr<TSP::World> world_;

    bool constructive_algorithm_done_;
    shared_ptr<TSP::State> state_;

    bool improvement_algorithm_done_;

};

#endif // MAINWINDOW_H
