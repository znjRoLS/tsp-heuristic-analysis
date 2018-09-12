#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Solver.h"
#include "SolverCallback.h"
#include "WorldGenerators.h"
#include "Algorithms.h"

#include "node.h"
#include "edge.h"

#include <QSize>

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

    graphic_scene = new QGraphicsScene();
    ui->graphicsView->setScene(graphic_scene);

    QSize qsize = ui->graphicsView->size();
    world_scale_y = 0.8 * qsize.height();
    world_scale_x = 0.8 * qsize.width();

    //node_radius = min(world_scale_x, world_scale_y) / 20;
    node_radius = 5;

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_clicked()
{

    shared_ptr<SolverCallbacks> callbacks (new SolverCallbacks);

      callbacks->RegisterHandler(SolverCallbacks::ON_FINISH, [this] (SharedState state) {
        //ui->result_label->setText(QString::fromStdString("OPalaaa " + state->ToString()));

          graphic_scene->clear();

          vector<Node*> graph_nodes;


          Node* graph_node;
          for (pair<double, double>& world_node : (*state->world)) {
              graph_node = new Node(node_radius);
              graphic_scene->addItem(graph_node);
              graph_node->setPos(world_node.first*world_scale_x, world_node.second*world_scale_y);
              graph_node->setToolTip("(" + QString::number(world_node.first) + "," + QString::number(world_node.second) + ")");

              graph_nodes.push_back(graph_node);
          }

          graph_node = new Node(node_radius);
          graphic_scene->addItem(graph_node);
          graph_node->setPos(0,0);

          graph_node = new Node(node_radius);
          graphic_scene->addItem(graph_node);
          graph_node->setPos(world_scale_x, world_scale_y);

          graph_node = new Node(node_radius);
          graphic_scene->addItem(graph_node);
          graph_node->setPos(0, world_scale_y);

          graph_node = new Node(node_radius);
          graphic_scene->addItem(graph_node);
          graph_node->setPos(world_scale_x, 0);

          Edge* edge;
          for (int i = 1; i< state->current_path->size(); i++) {
              edge = new Edge(graph_nodes[state->current_path->at(i-1)], graph_nodes[state->current_path->at(i)]);
              graphic_scene->addItem(edge);
          }
          edge = new Edge(graph_nodes[state->current_path->at(state->current_path->size()-1)], graph_nodes[state->current_path->at(0)]);
          graphic_scene->addItem(edge);

      });

      WorldGenerator* world_generator = TSP::world_generator_container[ui->comboBoxWorldGenerator->currentText().toStdString()];
      Algorithm* algorithm = TSP::algorithm_container[ui->comboBoxAlgorithm->currentText().toStdString()];

      unique_ptr<TSP::Solver> solver (new TSP::Solver({10, 10000}, world_generator, algorithm, callbacks));

        solver->Solve();
}
