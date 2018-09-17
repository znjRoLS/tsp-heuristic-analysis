#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "euclidean_world_generator.h"
#include "algorithm.h"
#include "constructive_algorithm.h"
#include "improvement_algorithm.h"
#include "lower_bound_algorithm.h"

using std::string;
using std::unordered_map;
using std::shared_ptr;
using std::make_shared;

namespace TSP {

extern unordered_map<string, shared_ptr<EuclideanWorldGenerator>> world_generators;

extern unordered_map<string, shared_ptr<LowerBoundAlgorithm>> lower_bound_algorithms;

extern unordered_map<string, shared_ptr<ConstructiveAlgorithm>> constructive_algorithms;

extern unordered_map<string, shared_ptr<ImprovementAlgorithm>> improvement_algorithms;

} // namespace TSP
