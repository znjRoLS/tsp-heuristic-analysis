#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include "random_euclidean_world_generator.h"
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
    void WorldGeneratorAction();
private:
    Ui::MainWindow *ui;
    shared_ptr<TSP::World> world_;
    TSPView* tspview_;
};

#endif // MAINWINDOW_H
