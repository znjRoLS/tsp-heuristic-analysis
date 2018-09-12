#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "euclidean_world_generator.h"
#include "random_euclidean_world_generator.h"
#include "algorithm.h"
#include "constructive_algorithm.h"
#include "random_constructive_algorithm.h"
#include "improvement_algorithm.h"
#include "kopt2_improvement_algorithm.h"
#include "kopt2_search_improvement_algorithm.h"

using std::string;
using std::unordered_map;
using std::shared_ptr;
using std::make_shared;

namespace TSP {

extern unordered_map<string, shared_ptr<EuclideanWorldGenerator>> world_generators;

extern unordered_map<string, shared_ptr<ConstructiveAlgorithm>> constructive_algorithms;

extern unordered_map<string, shared_ptr<ImprovementAlgorithm>> improvement_algorithms;

} // namespace TSP
