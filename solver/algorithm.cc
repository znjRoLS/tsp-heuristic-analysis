#include "algorithm.h"

namespace TSP {

Algorithm::~Algorithm() {}

vector<VisualEdge> Algorithm::GetVisualization() {
  return visualization_;
}

unordered_map<string, string> Algorithm::GetVisualParams() {
  return visual_params_;
}

} //namespace TSP
