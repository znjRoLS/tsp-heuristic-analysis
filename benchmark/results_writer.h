#pragma once

#include <unordered_map>
#include <vector>
#include <string>

using std::unordered_map;
using std::vector;
using std::string;

namespace TSP::Benchmark {

class ResultsWriter {
 public:
  void Output(string file_path);

  void AddItem(unordered_map<string,string> item);

 private:
  vector<unordered_map<string,string>> data_;
};


} // namespace TSP::Benchmark
