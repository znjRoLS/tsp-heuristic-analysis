#include "results_writer.h"

#include <fstream>
#include <unordered_set>
#include "container_contains.h"
#include "util.h"

using std::unordered_set;
using std::ofstream;

namespace TSP::Benchmark {

void ResultsWriter::Output(string file_path) {
  ofstream file_(file_path);

  TSP_ASSERT(file_.is_open());

  unordered_set<string> header;
  for (auto& mapa : data_) {
    for (auto& kp : mapa) {
      header.insert(kp.first);
    }
  }

  for (auto& column : header) {
    file_.write(column.c_str(), column.size());
    file_.write(", ", 2);
  }

  file_.write("\n", 1);

  for (auto& mapa : data_) {

    for (auto& column : header) {
      if (CONTAINS(mapa, column)) {
        file_.write(mapa[column].c_str(), mapa[column].size());
      }
      file_.write(", ", 2);
    }
    file_.write("\n", 1);
  }

  file_.close();

  data_.clear();
}

void ResultsWriter::AddItem(unordered_map<string, string> item) {
  data_.push_back(item);
}

}
