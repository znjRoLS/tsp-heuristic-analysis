#pragma once

#include "improvement_algorithm.h"

namespace TSP {

class LinKernighanImprovementAlgorithm : public ImprovementAlgorithm {
 public:
  LinKernighanImprovementAlgorithm(int variant);
  void Reset() override;
  bool Iterate(int granularity) override;
  int GetMaxGranularity() override;
 private:
  bool CheckValidTour();
  bool PositiveGain();
  bool CheckPositiveGain();
  void UpdateTour();
  bool AlreadyChosen(int t);

  shared_ptr<SquareMatrix<double>> optimization_metric_;
  vector<vector<int>> sorted_edges_;

  int variant_;
  bool metric_initialized_;
  vector<pair<int,int>> check_order_; // <node in path, direction>
  int current_check_edge;
  vector<int> current_t_;

  vector<double> g;
  vector<double> G;

  vector<pair<int, int>> current_tour_edges_;

  int curr_t3;
  int curr_t4;
  int curr_t5;

  vector<int> curr_t;

  const int try_nearest_ = 5;
};

} // namespace TSP
