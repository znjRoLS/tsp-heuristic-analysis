#ifndef TSPHEURISTICANALYSIS_POINT2D_H
#define TSPHEURISTICANALYSIS_POINT2D_H

struct Point2 {
    double abs();

    Point2 operator-(Point2 other);

    double x_;
    double y_;
};


#endif //TSPHEURISTICANALYSIS_POINT2D_H
