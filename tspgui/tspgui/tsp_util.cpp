#include "tsp_util.h"

#include "random_euclidean_world_generator.h"
#include "random_constructive_algorithm.h"
#include "nearest_neighbour_constructive_algorithm.h"
#include "greedy_constructive_algorithm.h"
#include "brute_force_constructive_algorithm.h"
#include "kopt2_improvement_algorithm.h"
#include "kopt2_search_improvement_algorithm.h"
#include "ant_colony_improvement_algorithm.h"
#include "held_karp_lower_bound_algorithm.h"
#include "min_1tree_lower_bound_algorithm.h"

namespace TSP {

unordered_map<string, shared_ptr<EuclideanWorldGenerator>> world_generators = {
    {"Random Euclidean", make_shared<RandomEuclideanWorldGenerator>()},
};

unordered_map<string, shared_ptr<LowerBoundAlgorithm>> lower_bound_algorithms = {
    {"Min 1-tree", make_shared<Min1treeLowerBoundAlgorithm>()},
    {"Held Karp 0", make_shared<HeldKarpLowerBoundAlgorithm>(0)},
    {"Held Karp 1", make_shared<HeldKarpLowerBoundAlgorithm>(1)},
    {"Held Karp 2", make_shared<HeldKarpLowerBoundAlgorithm>(2)},
    {"Held Karp 3", make_shared<HeldKarpLowerBoundAlgorithm>(3)},
};

unordered_map<string, shared_ptr<ConstructiveAlgorithm>> constructive_algorithms = {
    {"Random", make_shared<RandomConstructiveAlgorithm>()},
    {"Nearest Neighbour", make_shared<NearestNeighbourConstructiveAlgorithm>()},
    {"Greedy", make_shared<GreedyConstructiveAlgorithm>()},
    {"Brute Force", make_shared<BruteForceConstructiveAlgorithm>()},
};

unordered_map<string, shared_ptr<ImprovementAlgorithm>> improvement_algorithms = {
    {"K-Opt 2", make_shared<Kopt2ImprovementAlgorithm>()},
    {"K-Opt 2 Search", make_shared<Kopt2SearchImprovementAlgorithm>()},
    {"Ant Colony Optimisation 0", make_shared<AntColonyImprovementAlgorithm>(0, 10, 1, 3, 0.5, 10, 10)},
    {"Ant Colony Optimisation 1", make_shared<AntColonyImprovementAlgorithm>(1, 10, 1, 3, 0.5, 10, 10)},
    {"Ant Colony Optimisation 2", make_shared<AntColonyImprovementAlgorithm>(0, 1, 1, 3, 0.5, 10, 10)},
};

} // namespace TSP
