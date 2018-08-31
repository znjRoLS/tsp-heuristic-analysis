//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_STATE_H
#define TSPHEURISTICANALYSIS_STATE_H

#include "Util.h"

namespace TSP{

  struct State {

  public:
    State(World world);

    World world;
    Path current_path;
    Path optimal_path;
    shared_ptr<vector<vector<double>>> current_path_ant_colony;

    string ToString();

    static Path Default(int size);
  };

  typedef shared_ptr<State> SharedState;
}

ostream& operator<<(ostream& out, const TSP::SharedState& state);

#endif //TSPHEURISTICANALYSIS_STATE_H
