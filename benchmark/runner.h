#pragma once

#include "config_reader.h"
#include <memory>
#include <string>

using std::unique_ptr;
using std::string;

namespace TSP::Benchmark {

class Runner {
 public:
  Runner();
  void Run(vector<string> input_configs ); // , RunParameters parameters?

 private:
  string LogInfo();

  unique_ptr<ConfigReader> config_reader_;
};

} // namespace TSP::Benchmark
