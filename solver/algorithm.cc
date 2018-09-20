#include "algorithm.h"

namespace TSP {

Algorithm::~Algorithm() {}

vector<VisualEdge> Algorithm::GetVisualization() {
  return visualization_;
}

unordered_map<string, string> Algorithm::GetVisualParams() {
  return visual_params_;
}

void Algorithm::SetMeasureForOptimizing(shared_ptr<SquareMatrix<double>> measure) {
  optimizing_measure_ = measure;
}

} //namespace TSP
