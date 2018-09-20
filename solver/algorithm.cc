#include "algorithm.h"

namespace TSP {

Algorithm::~Algorithm() {}

vector<VisualEdge> Algorithm::GetVisualization() {
  return visualization_;
}

unordered_map<string, string> Algorithm::GetVisualParams() {
  return visual_params_;
}

void Algorithm::SetVisualsEnabled(bool enabled) {
  enable_visuals_ = enabled;
}

void Algorithm::PushVisualEdge(VisualEdge edge) {
  if (enable_visuals_) {
    visualization_.push_back(edge);
  }
}

} //namespace TSP
