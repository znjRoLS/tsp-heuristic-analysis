//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_ALGORITHMS_H
#define TSPHEURISTICANALYSIS_ALGORITHMS_H

#include "Algorithm.h"

#include <unordered_map>
#include <unordered_set>


#define REGISTER_ALGORITHM(x) \
struct x##_static_constructor { \
  public: x##_static_constructor() { \
    TSP::algorithm_container.insert({#x, new x()}); \
  } \
}; \
x##_static_constructor x##_hidden;


namespace TSP{

  class AlgorithmBruteForce: public Algorithm {

  public:
    void Setup(SharedState state) override;
    bool Iterate() override;

  };

  class AlgorithmNearestNeighbour: public Algorithm {
  public:
    void Setup(SharedState state) override;
    bool Iterate() override;

  private:
    unordered_set<int> unvisited;

  };

  class AlgorithmAntColonyOptimization: public Algorithm {
  public:
    AlgorithmAntColonyOptimization();
    struct Settings {
      double alpha; // exponent for pheromone trail parameter
      double eta; // exponent for nearness parameter
      double ro; // pheromone evaporation parameter
      int num_ants;
      double Q; // increase pheromone paramter
    };
    void SetSettings(Settings settings);
    void Setup(SharedState state) override;
    bool Iterate() override;
  private:

    struct Ant{
      Path path;
      unordered_set<int> unvisited;
    };

    void SubIterate();
    void AntIterate(Ant& ant);
    void UpdateTrails();

    vector<Ant> ants;
    shared_ptr<vector<vector<double>>> matrix;
    Settings settings;
  };

}



#endif //TSPHEURISTICANALYSIS_ALGORITHMS_H
