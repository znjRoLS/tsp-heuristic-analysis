#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include "random_euclidean_world_generator.h"

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
    void world_generator_action();
private:
    Ui::MainWindow *ui;
    shared_ptr<TSP::World> world_;
};

#endif // MAINWINDOW_H
