#include "tsplib_parser.h"

#include <vector>

#include "split_str.h"
#include <cassert>

using std::vector;
using std::stod;

TSPLIBParser::TSPLIBParser(string file_path) :
    input_file_(file_path) {

  assert(input_file_.is_open());
}

TSPLIBParser::~TSPLIBParser() {
  input_file_.close();
}

Point2 TSPLIBParser::GetNextPoint() {

  return point_;
}

bool TSPLIBParser::IterateNextPoint() {
  string line;

  // Usually only one iteration, but easier to program this way
  while (getline(input_file_, line)) {
    // Assumption is that all the lines not starting with a number are info.

    unsigned curr_i=0;
    while(curr_i < line.size() && isspace(line[curr_i]) ) curr_i++;

    if (curr_i >= line.size()) continue;

    if (!isdigit(line[curr_i])) {
      info_ += "\n" + line;
      continue;
    }
    info_processed_ = true;

    vector<string> tokens = split_str(line.substr(curr_i), ' ');

    vector<string> non_empty_tokens;

    for (auto& item : tokens) {
      if (!item.empty()) non_empty_tokens.push_back(item);
    }

    if (non_empty_tokens.size() != 3) break;

//    double first = stod(tokens[0]);
    double second = stod(non_empty_tokens[1]);
    double third = stod(non_empty_tokens[2]);

    point_ = {second, third};
    return true;

  }

  point_ = {0, 0};
  return false;
}

string TSPLIBParser::GetInfo() {
  if (!info_processed_) {

  }
  return info_;
}
