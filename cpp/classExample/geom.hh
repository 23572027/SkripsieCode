/*
Author: Paul Rossouw
Description: 
Class that calculates the area of an n-gon given that it is parralell with the xy plane.
Used in msfn calculation to calculate node areas.
Usage: 
Pass it points of type Point all except the point at which the area is being calculated. That point is passed to charpt
numPoints is the number of points in the polygon (excluding the characteristic point)

*/


#include <vector>
#include <math.h>

typedef struct Point { 
    double x, y, z;
    double norm() { return std::sqrt(x*x + y*y + z*z); } 
} Point;



class Cell {
    private:
        double area;
        bool areaComputed;
        std::vector<Point> pts;
        Point charPt;
        int numPts;

        void _orderPts();
        void _translate();
        double _computeArea();


    public:
        Cell(std::vector<Point> p_pts, Point &p_charPt, int p_numPts);
        ~Cell();
        double getArea();
    
};