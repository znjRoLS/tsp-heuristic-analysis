#pragma once

#include "config_reader.h"
#include <memory>
#include <string>
#include "results_writer.h"
#include <chrono>

using std::unique_ptr;
using std::string;

namespace TSP::Benchmark {

class Runner {
 public:
  Runner();
  void Run(string input_prefix, vector<string> input_configs, string output_prefix); // , RunParameters parameters?

 private:
  string LogInfo();
  void RunRuns();
  void RunSingleRun();
  void RunSingleWorldGenerator();
  void RunFileWorldGenerator();
  void RunSingleWorld();
  void RunSingleLowerBound();
  void RunSingleConstructive();
  void RunSingleStartingPathImprovement();
  void RunSingleImprovement();
  bool SingleImprovementEndCriteria();

  struct CurrentState {
    int iter;
    shared_ptr<EuclideanWorldGenerator> world_generator;
    string world_generator_string;
    int world_size;
    shared_ptr<World> world;
    int world_random_identifier;
    shared_ptr<LowerBoundAlgorithm> lower_bound_algorithm;
    string lower_bound_algorithm_string;
    bool lower_bound_calculated;
    double lower_bound_value;
    shared_ptr<ConstructiveAlgorithm> constructive_algorithm;
    string constructive_algorithm_string;
    Path path_random;
    shared_ptr<State> state_current;
    int path_random_identifier;
    shared_ptr<ImprovementAlgorithm> improvement_algorithm;
    string improvement_algorithm_string;
    std::chrono::time_point<std::chrono::high_resolution_clock> improvement_start;
    string input_file;
    bool inputs_from_file;
    int end_time;
  } current_state_;


  unique_ptr<ConfigReader> config_reader_;
  unique_ptr<ResultsWriter> results_writer_;
};

} // namespace TSP::Benchmark
