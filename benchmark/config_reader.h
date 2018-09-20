#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <lower_bound_algorithm.h>
#include "euclidean_world_generator.h"
#include "constructive_algorithm.h"
#include "improvement_algorithm.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::shared_ptr;

namespace TSP::Benchmark {

class ConfigReader {
 public:

//  enum EndCriterion {
//    TIME,
//    ITERATIONS,
//    LOWER_BOUND,
//  };

enum Measure {
  CLASSIC,
  ALFA,
  ALFA_IMPROVED,
};

  void LoadConfig(string file_path);

  string file_path_;
  unordered_map<string, string> input_;
  vector<string> world_generators_strings_;
  vector<shared_ptr<EuclideanWorldGenerator>> world_generators_;
  vector<string> lower_bound_algorithms_strings_;
  vector<shared_ptr<LowerBoundAlgorithm>> lower_bound_algorithms_;
  vector<string> constructive_algorithms_strings_;
  vector<shared_ptr<ConstructiveAlgorithm>> constructive_algorithms_;
  vector<string> improvement_algorithms_strings_;
  vector<shared_ptr<ImprovementAlgorithm>> improvement_algorithms_;
  vector<string> input_files_;
  vector<Measure> measures_;
  vector<string> measure_strings_;
  vector<int> world_sizes_;
  int num_repeat_;
  int num_random_constructive_repeat_;
  // closeness in percetages
  double end_lower_bound_;
  // in seconds
  int end_time_;
  // in num
  int end_iterations_;

  bool file_world_generator_;

  int time_track_resolution_;

//  EndCriterion end_criterion_;

 private:

  void LoadFile();
  void ParseWorldGenerators();
  void ParseLowerBoundAlgorithms();
  void ParseConstructiveAlgorithms();
  void ParseImprovementAlgorithms();
  void ParseInputFiles();
  void ParseEndCriterion();
  void ParseNumRuns();
  void ParseWorldSizes();
  void ParseTimeTrackResolution();
  void ParseMeasures();

};

} // TSP::Benchmark