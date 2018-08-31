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

double GetCost(const World& world, unsigned i, unsigned j);
double GetCost(const World& world, const Path& path);
void SetMin(const World& world, Path& path1, Path& path2);
bool Less(const World& world, Path& path1, Path& path2);

double EuclidianDistance(Point2 x, Point2 y);

ostream& operator<<(ostream& out, const Point2& point);

double Random();

bool Equal(double x, double y);
bool Less(double x, double y);
bool Greater(double x, double y);
bool LessOrEqual(double x, double y);
bool GreaterOrEqual(double x, double y);

double WeightedRandom(const vector<double>& weights, const vector<double>& values);
int WeightedRandom(const vector<double>& weights, const vector<int>& values);

#endif //TSPHEURISTICANALYSIS_UTIL_H
