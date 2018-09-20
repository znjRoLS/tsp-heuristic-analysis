#pragma once

#include "world.h"
#include "util.h"
#include <unordered_map>
#include <string>

using std::pair;
using std::vector;
using std::unordered_map;
using std::string;

namespace TSP {

class Algorithm {
 public:
  virtual ~Algorithm() = 0;
  virtual void Reset() = 0;
  virtual bool Iterate(int granularity) = 0;
  virtual int GetMaxGranularity() = 0;

  vector<VisualEdge> GetVisualization();
  unordered_map<string, string> GetVisualParams();

  void SetVisualsEnabled(bool enabled);

 protected:

  void PushVisualEdge(VisualEdge edge);

  vector<VisualEdge> visualization_;
  unordered_map<string, string> visual_params_;

  bool enable_visuals_ = true;

};

} // namespace TSP