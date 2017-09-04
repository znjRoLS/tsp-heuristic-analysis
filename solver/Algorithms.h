//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_ALGORITHMS_H
#define TSPHEURISTICANALYSIS_ALGORITHMS_H

#include "Algorithm.h"

namespace TSP{

  class AlgorithmBruteForce: public Algorithm {
  public:

    void Setup(SharedState state) override;

    bool Iterate() override;

  };

}



#endif //TSPHEURISTICANALYSIS_ALGORITHMS_H
