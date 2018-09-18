#pragma once

#include "config_reader.h"
#include <memory>
#include <string>
#include "results_writer.h"

using std::unique_ptr;
using std::string;

namespace TSP::Benchmark {

class Runner {
 public:
  Runner();
  void Run(string input_prefix, vector<string> input_configs, string output_prefix); // , RunParameters parameters?

 private:
  string LogInfo();

  unique_ptr<ConfigReader> config_reader_;
  unique_ptr<ResultsWriter> results_writer_;
};

} // namespace TSP::Benchmark
