//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_GENERATORRANDOM_H
#define TSPHEURISTICANALYSIS_GENERATORRANDOM_H

#include "TSPWorldGenerator.h"

class GeneratorRandom: public TSPWorldGenerator {
public:

  unique_ptr<vector<pair<double,double>>> GenerateWorld(int size) override;
};


#endif //TSPHEURISTICANALYSIS_GENERATORRANDOM_H
