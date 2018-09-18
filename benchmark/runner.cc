#include "runner.h"

#define LOG (cout << LogInfo())
#define LOG1 LOG << "  "
#define LOG2 LOG1 << "  "
#define LOG3 LOG2 << "  "
#define LOG4 LOG3 << "  "
#define LOG5 LOG4 << "  "

#include <memory>
#include <iostream>
#include "controller.h"
#include "file_euclidean_world_generator.h"
#include <chrono>
#include "random.h"

using std::make_unique;
using std::cout;
using std::endl;
using std::make_shared;
using std::to_string;
using std::max;

namespace TSP::Benchmark {

Runner::Runner() :
    config_reader_(make_unique<ConfigReader>()) {

}

void Runner::Run(string input_prefix, vector<string> input_configs, string output_prefix) {
  for (string &input : input_configs) {

    LOG << "Reading file " << input_prefix + input << "" << endl;
    config_reader_->LoadConfig(input);

    LOG << "Successfully parsed!" << endl;

    LOG << "Repeating runs " << config_reader_->num_repeat_ << " times" << endl;

    for (int iter = 0; iter < config_reader_->num_repeat_; iter++) {

      LOG1 << "Running run: " << iter << endl;

      for (unsigned wg_iter = 0; wg_iter < config_reader_->world_generators_.size(); wg_iter++) {

        LOG2 << "Running world gen: " << config_reader_->world_generators_strings_[wg_iter] << endl;
        shared_ptr<EuclideanWorldGenerator> world_generator = config_reader_->world_generators_[wg_iter];

        for (unsigned ws_iter = 0; ws_iter < config_reader_->world_sizes_.size(); ws_iter++) {

          LOG3 << "Running size: " << config_reader_->world_sizes_[ws_iter] << endl;
          int world_size = config_reader_->world_sizes_[ws_iter];

          shared_ptr<World> world = world_generator->GenerateWorld(world_size);
          int world_random_identifier = Random::GetInt();

          bool lower_bound_calculated = false;
          double lower_bound_value = 0.0;

          //////////////////////// LOWER BOUND ALGORITHMS

          for (unsigned lb_iter = 0; lb_iter < config_reader_->lower_bound_algorithms_.size(); lb_iter ++) {

            LOG4 << "Running lower bound: " << config_reader_->lower_bound_algorithms_strings_[lb_iter] << endl;

            lower_bound_calculated = true;

            shared_ptr<LowerBoundAlgorithm> lower_bound_algorithm = config_reader_->lower_bound_algorithms_[lb_iter];

            lower_bound_algorithm->SetWorld(world);
            auto start = std::chrono::steady_clock::now();
            lower_bound_algorithm->Iterate(0);
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start).count();
            lower_bound_value = max(lower_bound_value, lower_bound_algorithm->GetFinalValue());

            unordered_map<string, string> output;
            output["dur"] = to_string(duration);
            output["lower_bound_name"] = config_reader_->lower_bound_algorithms_strings_[lb_iter];
            output["found_optimal"] = to_string(lower_bound_algorithm->FoundOptimalSolution());
            output["lower_bound_value"] = to_string(lower_bound_value);
            output["world_generator_name"] = config_reader_->world_generators_strings_[wg_iter];
            output["world_size"] = to_string(world_size);
            output["world_id"] = to_string(world_random_identifier);
            output["run_iteration"] = to_string(iter);

            results_writer_->AddItem(output);

          }

          //////////////////////// CONSTRUCTIVE ALGORITHMS

          if (!config_reader_->constructive_algorithms_.empty()) {

            for (unsigned ca_iter = 0; ca_iter < config_reader_->constructive_algorithms_.size(); ca_iter++) {

              LOG4 << "Running constructive: " << config_reader_->constructive_algorithms_strings_[ca_iter] << endl;

              controller.SetConstructiveAlgorithm(config_reader_->constructive_algorithms_[ca_iter]);

              auto start = std::chrono::steady_clock::now();
              controller.IterateConstructiveAlgorithm(0);
              auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::steady_clock::now() - start).count();

              unordered_map<string, string> output;

              output["dur"] = to_string(duration);
              output[""]

            }
          }
        }
      }
    }



      if (config_reader_->file_world_generator_) {
        for (unsigned if_iter = 0; if_iter < config_reader_->input_files_.size(); if_iter++) {
          Controller controller;

          shared_ptr<FileEuclideanWorldGenerator> world_generator_ = make_shared<FileEuclideanWorldGenerator>();
          world_generator_->SetFile(config_reader_->input_files_[if_iter]);
          controller.SetWorldGenerator(world_generator_);
          controller.GenerateNewWorld(0);
          for (unsigned ca_iter = 0; ca_iter < config_reader_->constructive_algorithms_.size(); ca_iter++) {
            for (unsigned ia_iter = 0; ia_iter < config_reader_->improvement_algorithms_.size(); ia_iter++) {

              LOG << "Running file world generator file: " << if_iter << ", constructive: " << ca_iter
                  << ", improvement: " << ia_iter << endl;

              controller.SetConstructiveAlgorithm(config_reader_->constructive_algorithms_[ca_iter]);
              controller.IterateConstructiveAlgorithm(0);

              controller.SetImprovementAlgorithm(config_reader_->improvement_algorithms_[ia_iter]);
              controller.IterateImprovementAlgorithm(0);

              LOG << "Final cost " << controller.GetCurrentState()->CurrentPathCost() << endl;
            }
          }
        }
      }
    }

    results_writer_->Output(output_prefix + input);

  }
}

string Runner::LogInfo() {
  return "";
}

} // namespace TSP::Benchmark
