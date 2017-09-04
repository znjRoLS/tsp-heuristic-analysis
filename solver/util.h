//
// Created by Bojan Roško on 9/2/17.
//

#ifndef TSPHEURISTICANALYSIS_UTIL_H
#define TSPHEURISTICANALYSIS_UTIL_H

#include <utility>
#include <vector>
#include <memory>
#include <iostream>


using namespace std;

typedef pair<double, double> Point2;
typedef shared_ptr<vector<Point2>> World;
typedef shared_ptr<vector<int>> Path;

double GetCost(const World& world, int i, int j);

double EuclidianDistance(Point2 x, Point2 y);

ostream& operator<<(ostream& out, const Point2& point);

double Random();

#endif //TSPHEURISTICANALYSIS_UTIL_H
