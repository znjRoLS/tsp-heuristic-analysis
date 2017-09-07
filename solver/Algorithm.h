//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_TSPALGORITHM_H
#define TSPHEURISTICANALYSIS_TSPALGORITHM_H

#include "State.h"

#include <memory>
#include <unordered_map>

namespace TSP {

  class Algorithm {
  public:

    virtual void Setup(SharedState state) = 0;
    virtual bool Iterate() = 0;

  protected:
    SharedState state;
  };

  extern unordered_map<string, Algorithm*> algorithm_container;

}

#endif //TSPHEURISTICANALYSIS_TSPALGORITHM_H
