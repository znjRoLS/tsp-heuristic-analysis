#include "config_reader.h"

#include <fstream>
#include <memory>
#include <greedy_constructive_algorithm.h>
#include "split_str.h"
#include "container_contains.h"
#include "random_euclidean_world_generator.h"
#include "file_euclidean_world_generator.h"
#include "held_karp_lower_bound_algorithm.h"
#include "random_constructive_algorithm.h"
#include "nearest_neighbour_constructive_algorithm.h"
#include "brute_force_constructive_algorithm.h"
#include "christofides_constructive_algorithm.h"
#include "kopt2_improvement_algorithm.h"
#include "kopt2_search_improvement_algorithm.h"
#include "ant_colony_improvement_algorithm.h"
#include "lin_kernighan_improvement_algorithm.h"
#include "min_1tree_lower_bound_algorithm.h"
#include "alfa_measure.h"
#include "kopt3_improvement_algorithm.h"
#include "kopt3_search_improvement_algorithm.h"

using std::ifstream;
using std::make_shared;
using std::stoi;

namespace TSP::Benchmark {

void ConfigReader::LoadConfig(string file_path) {
  file_world_generator_ = false;
  world_generators_.clear();
  world_generators_strings_.clear();
  improvement_algorithms_.clear();
  improvement_algorithms_strings_.clear();
  lower_bound_algorithms_.clear();
  lower_bound_algorithms_strings_.clear();
  constructive_algorithms_.clear();
  constructive_algorithms_strings_.clear();
  input_.clear();
  input_files_.clear();
  world_sizes_.clear();

  file_path_ = file_path;
  LoadFile();

  ParseWorldGenerators();
  ParseLowerBoundAlgorithms();
  ParseConstructiveAlgorithms();
  ParseImprovementAlgorithms();
  if (file_world_generator_) {
    ParseInputFiles();
  }

  ParseEndCriterion();
  ParseNumRuns();
  ParseWorldSizes();

  ParseTimeTrackResolution();
}


void ConfigReader::LoadFile() {
  input_.clear();

  ifstream file(file_path_);

  string line;
  while (getline(file, line)) {
    if (line[0] == '#') continue; // comment
    vector<string> tokens = split_str(line, '=');
    TSP_ASSERT_EQ(tokens.size(), 2);
      input_[tokens[0]] = tokens[1];
  }
}

void ConfigReader::ParseWorldGenerators() {
  TSP_ASSERT_CONTAINS(input_, "WORLD_GENERATORS");

  world_generators_.clear();
  file_world_generator_ = false;

  vector<string> items = split_str(input_["WORLD_GENERATORS"], ' ');
  world_generators_strings_ = items;
  for (string& item : items) {
    if (item == "random") {
      world_generators_.push_back(make_shared<RandomEuclideanWorldGenerator>());
    } else if (item == "file") {
      file_world_generator_ = true;
//      world_generators_.push_back(make_shared<FileEuclideanWorldGenerator>());
    } else {
      TSP_ILLEGAL;
    }
  }
}

void ConfigReader::ParseLowerBoundAlgorithms() {
  lower_bound_algorithms_.clear();

  if (!CONTAINS(input_, "LOWER_BOUND_ALGORITHMS")) return;

  vector<string> items = split_str(input_["LOWER_BOUND_ALGORITHMS"], ' ');
  lower_bound_algorithms_strings_ = items;
  for (string& item : items) {
    if (item == "held_karp_0") {
      lower_bound_algorithms_.push_back(make_shared<HeldKarpLowerBoundAlgorithm>(0));
    } else if (item == "held_karp_1") {
      lower_bound_algorithms_.push_back(make_shared<HeldKarpLowerBoundAlgorithm>(1));
    } else if (item == "held_karp_2") {
      lower_bound_algorithms_.push_back(make_shared<HeldKarpLowerBoundAlgorithm>(2));
    } else if (item == "held_karp_3") {
      lower_bound_algorithms_.push_back(make_shared<HeldKarpLowerBoundAlgorithm>(3));
    } else if (item == "min1tree") {
      lower_bound_algorithms_.push_back(make_shared<Min1treeLowerBoundAlgorithm>());
//    } else if (item == "christofides") {
//      constructive_algorithms_.push_back(make_shared<ChristofidesConstructiveAlgorithm>());
    } else {
      TSP_ILLEGAL;
    }
  }
}

void ConfigReader::ParseConstructiveAlgorithms() {

  constructive_algorithms_.clear();

  if (!CONTAINS(input_, "CONSTRUCTIVE_ALGORITHMS")) return;


  vector<string> items = split_str(input_["CONSTRUCTIVE_ALGORITHMS"], ' ');
  constructive_algorithms_strings_ = items;
  for (string& item : items) {
    if (item == "random") {
      constructive_algorithms_.push_back(make_shared<RandomConstructiveAlgorithm>());
    } else if (item == "nearest_neighbour") {
      constructive_algorithms_.push_back(make_shared<NearestNeighbourConstructiveAlgorithm>());
    } else if (item == "brute_force") {
      constructive_algorithms_.push_back(make_shared<BruteForceConstructiveAlgorithm>());
    } else if (item == "greedy") {
      constructive_algorithms_.push_back(make_shared<GreedyConstructiveAlgorithm>());
//    } else if (item == "christofides") {
//      constructive_algorithms_.push_back(make_shared<ChristofidesConstructiveAlgorithm>());
    } else {
      TSP_ILLEGAL;
    }
  }
}

void ConfigReader::ParseImprovementAlgorithms() {

  improvement_algorithms_.clear();

  if (!CONTAINS(input_, "IMPROVEMENT_ALGORITHMS")) return;


  vector<string> items = split_str(input_["IMPROVEMENT_ALGORITHMS"], ' ');
  improvement_algorithms_strings_ = items;
  for (string& item : items) {
    if (item == "kopt2") {
      improvement_algorithms_.push_back(make_shared<Kopt2ImprovementAlgorithm>());
    } else if (item == "kopt3") {
      improvement_algorithms_.push_back(make_shared<Kopt3ImprovementAlgorithm>());
    } else if (item == "kopt2_search") {
      improvement_algorithms_.push_back(make_shared<Kopt2SearchImprovementAlgorithm>());
    } else if (item == "kopt3_search") {
      improvement_algorithms_.push_back(make_shared<Kopt3SearchImprovementAlgorithm>());
    } else if (item == "ant_colony_0") {
      improvement_algorithms_.push_back(make_shared<AntColonyImprovementAlgorithm>(0, 10, 1, 3, 0.5, 10, 10));
    } else if (item == "ant_colony_1") {
      improvement_algorithms_.push_back(make_shared<AntColonyImprovementAlgorithm>(1, 10, 1, 3, 0.5, 10, 10));
    } else if (item == "ant_colony_2") {
      improvement_algorithms_.push_back(make_shared<AntColonyImprovementAlgorithm>(0, 1, 1, 3, 0.5, 10, 10));
    } else if (item == "lin_kernighan_0") {
      improvement_algorithms_.push_back(make_shared<LinKernighanImprovementAlgorithm>(0));
    } else if (item == "lin_kernighan_1") {
      improvement_algorithms_.push_back(make_shared<LinKernighanImprovementAlgorithm>(1));
    } else if (item == "lin_kernighan_2") {
      improvement_algorithms_.push_back(make_shared<LinKernighanImprovementAlgorithm>(2));
//    } else if (item == "lin_kernighan") {
//      improvement_algorithms_.push_back(make_shared<LinKernighanImprovementAlgorithm>());
    } else {
      TSP_ILLEGAL;
    }
  }
}

void ConfigReader::ParseInputFiles() {
  TSP_ASSERT_CONTAINS(input_, "INPUT_FILES");

  input_files_.clear();

  input_files_ = split_str(input_["INPUT_FILES"], ' ');

  if (input_.find("INPUT_FILES_PREFIX") != input_.end()) {
    for (unsigned i = 0 ; i < input_files_.size(); i ++ ) {
      input_files_[i] = input_["INPUT_FILES_PREFIX"] + input_files_[i];
    }
  }
}

void ConfigReader::ParseEndCriterion() {
//  TSP_ASSERT_CONTAINS(input_, "END_CRITERION");
//
//  string item = input_["END_CRITERION"];
//  if (item == "time") {
//    end_criterion_ = EndCriterion::TIME;
//    TSP_ASSERT_CONTAINS(input_, "END_TIME");
//    end_seconds_ = stoi(input_["END_TIME"]);
//  } else if (item == "iterations") {
//    end_criterion_ = EndCriterion::ITERATIONS;
//    TSP_ASSERT_CONTAINS(input_, "END_ITERATIONS");
//    end_seconds_ = stoi(input_["END_ITERATIONS"]);
//  } else if (item == "lower_bound_closeness") {
//    end_criterion_ = EndCriterion::LOWER_BOUND;
//    TSP_ASSERT_CONTAINS(input_, "END_LOWER_BOUND");
//    end_seconds_ = stoi(input_["END_LOWER_BOUND"]);
//  } else {
//    TSP_ILLEGAL;
//  }

  if (input_.find("END_TIME") != input_.end()) {
    end_time_ = stoi(input_["END_TIME"]);
  }
  if (input_.find("END_ITERATIONS") != input_.end()) {
    end_iterations_ = stoi(input_["END_ITERATIONS"]);
  }
  if (input_.find("END_LOWER_BOUND") != input_.end()) {
    end_lower_bound_ = stod(input_["END_LOWER_BOUND"]);
  }

  end_times_.clear();
  if (CONTAINS(input_, "END_TIMES")) {
    vector<string> items = split_str(input_["END_TIMES"], ' ');
    for (string &item : items) {
      end_times_.push_back(stoi(item));
    }
  }

}

void ConfigReader::ParseNumRuns() {
  TSP_ASSERT_CONTAINS(input_, "NUM_RUNS");

  num_repeat_ = stoi(input_["NUM_RUNS"]);

  TSP_ASSERT_CONTAINS(input_, "NUM_RANDOM_CONSTRUCTIVE_RUNS");

  num_random_constructive_repeat_ = stoi(input_["NUM_RANDOM_CONSTRUCTIVE_RUNS"]);
}

void ConfigReader::ParseWorldSizes() {
  TSP_ASSERT_CONTAINS(input_, "WORLD_SIZES");

  world_sizes_.clear();

  vector<string> items = split_str(input_["WORLD_SIZES"], ' ');
  for (string& item : items) {
    world_sizes_.push_back(stoi(item));
  }
}

void ConfigReader::ParseTimeTrackResolution() {
  time_track_resolution_ = 0;

  if (CONTAINS(input_, "TIME_TRACK_RESOLUTION")) {
    time_track_resolution_ = stoi(input_["TIME_TRACK_RESOLUTION"]);
  }
}

} // TSP::Benchmark