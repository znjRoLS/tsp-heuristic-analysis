#include "runner.h"

#define LOG (cout << LogInfo())

#include <memory>
#include <iostream>
#include "controller.h"
#include "file_euclidean_world_generator.h"

using std::make_unique;
using std::cout;
using std::endl;
using std::make_shared;

namespace TSP::Benchmark {

Runner::Runner() :
    config_reader_(make_unique<ConfigReader>()) {

}

void Runner::Run(vector<string> input_configs) {
  for (string &input : input_configs) {

    LOG << "Reading file " << input << "" << endl;
    config_reader_->LoadConfig(input);

    LOG << "Successfully parsed!" << endl;

    LOG << "Repeating runs " << config_reader_->num_repeat_ << " times" << endl;

    for (int iter = 0; iter < config_reader_->num_repeat_; iter++) {

      for (unsigned wg_iter = 0; wg_iter < config_reader_->world_generators_.size(); wg_iter++) {
        for (unsigned ws_iter = 0; ws_iter < config_reader_->world_sizes_.size(); ws_iter++) {

          Controller controller;

          controller.SetWorldGenerator(config_reader_->world_generators_[wg_iter]);
          controller.GenerateNewWorld(config_reader_->world_sizes_[ws_iter]);

          for (unsigned ca_iter = 0; ca_iter < config_reader_->constructive_algorithms_.size(); ca_iter++) {
            for (unsigned ia_iter = 0; ia_iter < config_reader_->improvement_algorithms_.size(); ia_iter++) {
              LOG << "Running world generator: " << wg_iter << ", constructive: " << ca_iter << ", improvement: "
                  << ia_iter << endl;

              controller.SetConstructiveAlgorithm(config_reader_->constructive_algorithms_[ca_iter]);
              controller.IterateConstructiveAlgorithm(0);

              controller.SetImprovementAlgorithm(config_reader_->improvement_algorithms_[ia_iter]);
              controller.IterateImprovementAlgorithm(0);

              LOG << "Final cost " << controller.GetCurrentState()->CurrentPathCost() << endl;
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

  }
}

string Runner::LogInfo() {
  return "";
}

} // namespace TSP::Benchmark
