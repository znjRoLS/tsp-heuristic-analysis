#include "runner.h"

#define LOG (cout << LogInfo())
#define LOG1 LOG << "  "
#define LOG2 LOG1 << "  "
#define LOG3 LOG2 << "  "
#define LOG4 LOG3 << "  "
#define LOG5 LOG4 << "  "
#define LOG6 LOG5 << "  "

#include <memory>
#include <iostream>
#include "controller.h"
#include "file_euclidean_world_generator.h"
#include "random_constructive_algorithm.h"
#include "alfa_measure.h"
#include "random.h"
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string

using std::make_unique;
using std::cout;
using std::endl;
using std::make_shared;
using std::to_string;
using std::max;

namespace TSP::Benchmark {

Runner::Runner() :
    config_reader_(make_unique<ConfigReader>()),
    results_writer_(make_unique<ResultsWriter>()){

}

void Runner::Run(string input_prefix, vector<string> input_configs, string output_prefix) {
  for (string &input : input_configs) {

    LOG << "Reading file " << input_prefix + input << "" << endl;
    config_reader_->LoadConfig(input_prefix + input);

    LOG << "Successfully parsed!" << endl;

    RunRuns();

    LOG << "Writing file " << output_prefix + input + ".out" << "" << endl;

    results_writer_->Output(output_prefix + input + ".out");
  }
}

void Runner::RunRuns() {
  LOG << "Repeating runs " << config_reader_->num_repeat_ << " times" << endl;

  for (int iter = 0; iter < config_reader_->num_repeat_; iter++) {

    LOG1 << "Running run: " << iter << endl;

    current_state_.iter = iter;
    RunSingleRun();
  }

  if (config_reader_->file_world_generator_) {

    LOG << "Running file generator runs" << endl;

    RunFileWorldGenerator();
  }

}

void Runner::RunSingleRun() {
  current_state_.inputs_from_file = false;
  for (unsigned wg_iter = 0; wg_iter < config_reader_->world_generators_.size(); wg_iter++) {

    LOG2 << "Running world gen: " << config_reader_->world_generators_strings_[wg_iter] << endl;
    current_state_.world_generator = config_reader_->world_generators_[wg_iter];

    current_state_.world_generator_string = config_reader_->world_generators_strings_[wg_iter];

    RunSingleWorldGenerator();
  }
}

void Runner::RunSingleWorldGenerator() {
  for (unsigned ws_iter = 0; ws_iter < config_reader_->world_sizes_.size(); ws_iter++) {

    LOG3 << "Running size: " << config_reader_->world_sizes_[ws_iter] << endl;
    LOG3 << "Running with end time: " << config_reader_->end_times_[ws_iter] << endl;
    current_state_.world_size = config_reader_->world_sizes_[ws_iter];
    current_state_.end_time = config_reader_->end_times_[ws_iter];

    current_state_.world = current_state_.world_generator->GenerateWorld(current_state_.world_size);
    current_state_.world_random_identifier = Random::GetInt();

    RunSingleWorld();
  }
}

void Runner::RunFileWorldGenerator() {
  current_state_.inputs_from_file = true;

  for (unsigned if_iter = 0; if_iter < config_reader_->input_files_.size(); if_iter++) {

    LOG1 << "Running with input file: " << config_reader_->input_files_[if_iter] << endl;

    shared_ptr<FileEuclideanWorldGenerator> world_generator_ = make_shared<FileEuclideanWorldGenerator>();
    world_generator_->SetFile(config_reader_->input_files_[if_iter]);

    current_state_.world_generator = world_generator_;
    current_state_.input_file = config_reader_->input_files_[if_iter];

    current_state_.world = current_state_.world_generator->GenerateWorld(0);
    current_state_.world_size = current_state_.world->size;
    current_state_.world_random_identifier = Random::GetInt();

    RunSingleWorld();
  }

  current_state_.inputs_from_file = false;
}

void Runner::RunSingleWorld() {

  current_state_.lower_bound_calculated = false;
  current_state_.lower_bound_value = 0.0;

  //////////////////////// LOWER BOUND ALGORITHMS

  for (unsigned lb_iter = 0; lb_iter < config_reader_->lower_bound_algorithms_.size(); lb_iter++) {

    LOG4 << "Running lower bound: " << config_reader_->lower_bound_algorithms_strings_[lb_iter] << endl;

    current_state_.lower_bound_calculated = true;
    current_state_.lower_bound_algorithm = config_reader_->lower_bound_algorithms_[lb_iter];
    current_state_.lower_bound_algorithm_string = config_reader_->lower_bound_algorithms_strings_[lb_iter];

    RunSingleLowerBound();
  }

  //////////////////////// CONSTRUCTIVE ALGORITHMS

  for (unsigned ca_iter = 0; ca_iter < config_reader_->constructive_algorithms_.size(); ca_iter++) {

    LOG4 << "Running constructive: " << config_reader_->constructive_algorithms_strings_[ca_iter] << endl;

    current_state_.constructive_algorithm = config_reader_->constructive_algorithms_[ca_iter];
    current_state_.constructive_algorithm_string = config_reader_->constructive_algorithms_strings_[ca_iter];

    RunSingleConstructive();
  }

  //////////////////////// IMPROVEMENT ALGORITHMS

  for (int rca_iter = 0; rca_iter < config_reader_->num_random_constructive_repeat_; rca_iter++ ) {

    LOG4 << "Running random constructive for improvement, num: " << rca_iter << endl;

    shared_ptr<ConstructiveAlgorithm> random_constructive_algorithm = make_shared<RandomConstructiveAlgorithm>();

    random_constructive_algorithm->SetWorld(current_state_.world);
    random_constructive_algorithm->Reset();
    random_constructive_algorithm->Iterate(0);

    current_state_.path_random = random_constructive_algorithm->GetFinalPath();
    current_state_.path_random_identifier = Random::GetInt();

    RunSingleStartingPathImprovement();
  }
}


void Runner::RunSingleLowerBound() {
  current_state_.lower_bound_algorithm->SetWorld(current_state_.world);
  current_state_.lower_bound_algorithm->SetVisualsEnabled(false);
  current_state_.lower_bound_algorithm->Reset();

  auto start = std::chrono::high_resolution_clock::now();
  current_state_.lower_bound_algorithm->IterateOptimized();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start).count();
  current_state_.lower_bound_value = max(current_state_.lower_bound_value, current_state_.lower_bound_algorithm->GetFinalValue());

  unordered_map<string, string> output;
  output["dur"] = to_string(duration);
  output["lower_bound_name"] = current_state_.lower_bound_algorithm_string;
  output["found_optimal"] = to_string(current_state_.lower_bound_algorithm->FoundOptimalSolution());
  output["lower_bound_value"] = to_string(current_state_.lower_bound_value);
  output["world_generator_name"] = current_state_.world_generator_string;
  output["world_size"] = to_string(current_state_.world_size);
  output["world_id"] = to_string(current_state_.world_random_identifier);
  output["run_iteration"] = to_string(current_state_.iter);
  if (current_state_.inputs_from_file) {
    output["input_file"] = current_state_.input_file;
  }

  results_writer_->AddItem(output);
}

void Runner::RunSingleConstructive() {

  current_state_.constructive_algorithm->SetWorld(current_state_.world);
  current_state_.constructive_algorithm->SetVisualsEnabled(false);
  current_state_.constructive_algorithm->Reset();

  auto start = std::chrono::high_resolution_clock::now();
  current_state_.constructive_algorithm->Iterate(0);
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start).count();

  double constructive_value = current_state_.constructive_algorithm->GetFinalPathCost();

  unordered_map<string, string> output;
  output["dur"] = to_string(duration);
  output["constructive_name"] = current_state_.constructive_algorithm_string;
  output["constructive_value"] = to_string(constructive_value);
  if (current_state_.lower_bound_calculated) {
    output["constructive_closeness"] =
        to_string((constructive_value - current_state_.lower_bound_value) / current_state_.lower_bound_value);
  }
  output["world_generator_name"] = current_state_.world_generator_string;
  output["world_size"] = to_string(current_state_.world_size);
  output["world_id"] = to_string(current_state_.world_random_identifier);
  output["run_iteration"] = to_string(current_state_.iter);
  if (current_state_.inputs_from_file) {
    output["input_file"] = current_state_.input_file;
  }

  results_writer_->AddItem(output);
}

void Runner::RunSingleStartingPathImprovement() {
  for (unsigned ia_iter = 0; ia_iter < config_reader_->improvement_algorithms_.size(); ia_iter++) {

    LOG5 << "Running improvement: " << config_reader_->improvement_algorithms_strings_[ia_iter] << endl;

    current_state_.improvement_algorithm = config_reader_->improvement_algorithms_[ia_iter];
    current_state_.improvement_algorithm_string = config_reader_->improvement_algorithms_strings_[ia_iter];
    current_state_.state_current = make_shared<State>(current_state_.world, current_state_.path_random);

    RunSingleImprovement();
  }
}

void Runner::RunSingleImprovement() {
  current_state_.improvement_algorithm->SetState(current_state_.state_current);
  current_state_.improvement_algorithm->Reset();
  current_state_.improvement_algorithm->SetVisualsEnabled(false);

  if (config_reader_->time_track_points_.empty()) {

    current_state_.improvement_start = std::chrono::high_resolution_clock::now();

    auto last_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - current_state_.improvement_start).count();

    int nums_written = 0;
    int one_resolution_width =  current_state_.end_time / config_reader_->time_track_resolution_;

    while (nums_written < config_reader_->time_track_resolution_) {
      current_state_.improvement_algorithm->Iterate(current_state_.improvement_algorithm->GetMaxGranularity());

      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() - current_state_.improvement_start).count();

      double improvement_value = current_state_.improvement_algorithm->GetCurrentPathCost();

      if (duration - last_duration > one_resolution_width) {
        last_duration = duration;
        nums_written ++;

        unordered_map<string, string> output;
        output["dur"] = to_string(duration);
        output["improvement_name"] = current_state_.improvement_algorithm_string;
        output["improvement_value"] = to_string(improvement_value);
        if (current_state_.lower_bound_calculated) {
          output["improvement_closeness"] =
              to_string((improvement_value - current_state_.lower_bound_value) / current_state_.lower_bound_value);
        }
        output["world_generator_name"] = current_state_.world_generator_string;
        output["world_size"] = to_string(current_state_.world_size);
        output["world_id"] = to_string(current_state_.world_random_identifier);
        output["random_path_id"] = to_string(current_state_.path_random_identifier);
        output["run_iteration"] = to_string(current_state_.iter);
        if (current_state_.inputs_from_file) {
          output["input_file"] = current_state_.input_file;
        }

        results_writer_->AddItem(output);
      }
    }
  } else {
    auto last_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - current_state_.improvement_start).count();

    unsigned time_point_ind = 0;

    while (time_point_ind < config_reader_->time_track_points_.size()) {
      current_state_.improvement_algorithm->Iterate(current_state_.improvement_algorithm->GetMaxGranularity());

      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::high_resolution_clock::now() - current_state_.improvement_start).count();

      double improvement_value = current_state_.improvement_algorithm->GetCurrentPathCost();

      if (duration - last_duration > config_reader_->time_track_points_[time_point_ind]) {
        //last_duration = duration;
        time_point_ind ++;

        unordered_map<string, string> output;
        output["dur"] = to_string(duration);
        output["improvement_name"] = current_state_.improvement_algorithm_string;
        output["improvement_value"] = to_string(improvement_value);
        if (current_state_.lower_bound_calculated) {
          output["improvement_closeness"] =
              to_string((improvement_value - current_state_.lower_bound_value) / current_state_.lower_bound_value);
        }
        output["world_generator_name"] = current_state_.world_generator_string;
        output["world_size"] = to_string(current_state_.world_size);
        output["world_id"] = to_string(current_state_.world_random_identifier);
        output["random_path_id"] = to_string(current_state_.path_random_identifier);
        output["run_iteration"] = to_string(current_state_.iter);
        output["time_point"] = to_string(config_reader_->time_track_points_[time_point_ind-1]);
        if (current_state_.inputs_from_file) {
          output["input_file"] = current_state_.input_file;
        }

        results_writer_->AddItem(output);
      }
    }
  }

}

bool Runner::SingleImprovementEndCriteria() {
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - current_state_.improvement_start).count();

  return duration > current_state_.end_time;
}

string Runner::LogInfo() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << "| ";
  return ss.str();
}

} // namespace TSP::Benchmark
