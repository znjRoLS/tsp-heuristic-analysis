#include "config_reader.h"

#include <fstream>
#include <memory>
#include "split_str.h"
#include "random_euclidean_world_generator.h"
#include "file_euclidean_world_generator.h"
#include "held_karp_lower_bound.h"
#include "random_constructive_algorithm.h"
#include "nearest_neighbour_constructive_algorithm.h"
#include "brute_force_constructive_algorithm.h"
#include "christofides_constructive_algorithm.h"
#include "kopt2_improvement_algorithm.h"
#include "kopt2_search_improvement_algorithm.h"
#include "ant_colony_improvement_algorithm.h"
#include "lin_kernighan_improvement_algorithm.h"

using std::ifstream;
using std::make_shared;
using std::stoi;

namespace TSP::Benchmark {

void ConfigReader::LoadConfig(string file_path) {
  file_path_ = file_path;
  LoadFile();

  ParseWorldGenerators();
  ParseLowerBoundAlgorithms();
  ParseConstructiveAlgorithms();
  ParseImprovementAlgorithms();
  ParseInputFiles();
  ParseEndCriterion();
  ParseNumRuns();
  ParseWorldSizes();
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
  TSP_ASSERT_CONTAINS(input_, "LOWER_BOUND_ALGORITHM");

  string item = input_["LOWER_BOUND_ALGORITHM"];
//  if (item == "held_karp") {
//    lower_bound_algorithm_ = make_shared<HeldKarpLowerBound>();
//  } else {
//    TSP_ILLEGAL;
//  }
}

void ConfigReader::ParseConstructiveAlgorithms() {
  TSP_ASSERT_CONTAINS(input_, "CONSTRUCTIVE_ALGORITHMS");

  constructive_algorithms_.clear();

  vector<string> items = split_str(input_["CONSTRUCTIVE_ALGORITHMS"], ' ');
  for (string& item : items) {
    if (item == "random") {
      constructive_algorithms_.push_back(make_shared<RandomConstructiveAlgorithm>());
//    } else if (item == "nearest_neighbour") {
//      constructive_algorithms_.push_back(make_shared<NearestNeighbourConstructiveAlgorithm>());
//    } else if (item == "brute_force") {
//      constructive_algorithms_.push_back(make_shared<NearestNeighbourConstructiveAlgorithm>());
//    } else if (item == "christofides") {
//      constructive_algorithms_.push_back(make_shared<ChristofidesConstructiveAlgorithm>());
    } else {
      TSP_ILLEGAL;
    }
  }
}

void ConfigReader::ParseImprovementAlgorithms() {
  TSP_ASSERT_CONTAINS(input_, "IMPROVEMENT_ALGORITHMS");

  improvement_algorithms_.clear();

  vector<string> items = split_str(input_["IMPROVEMENT_ALGORITHMS"], ' ');
  for (string& item : items) {
    if (item == "kopt2") {
      improvement_algorithms_.push_back(make_shared<Kopt2ImprovementAlgorithm>());
    } else if (item == "kopt2_search") {
      improvement_algorithms_.push_back(make_shared<Kopt2SearchImprovementAlgorithm>());
//    } else if (item == "ant_colony") {
//      improvement_algorithms_.push_back(make_shared<AntColonyImprovementAlgorithm>());
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

}

void ConfigReader::ParseNumRuns() {
  TSP_ASSERT_CONTAINS(input_, "NUM_RUNS");

  num_repeat_ = stoi(input_["NUM_RUNS"]);
}

void ConfigReader::ParseWorldSizes() {
  TSP_ASSERT_CONTAINS(input_, "WORLD_SIZES");

  world_sizes_.clear();

  vector<string> items = split_str(input_["WORLD_SIZES"], ' ');
  for (string& item : items) {
    world_sizes_.push_back(stoi(item));
  }
}

} // TSP::Benchmark