/*
Author: Paul Rossouw
Description: 
Class that calculates the area of an n-gon given that it is parralell with the xy plane.
Used in msfn calculation to calculate node areas.
Usage: 
Pass it points of type Point all except the point at which the area is being calculated. That point is passed to charpt
numPoints is the number of points in the polygon (excluding the characteristic point)

*/

#ifndef GEOM_
#define GEOM_

#define PT(pt) pt.x , pt.y, pt.z

#include <vtkGenericDataObjectReader.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>

#include <vector>
#include <math.h>


typedef struct Point { 
    double x, y, z;
    int pid = 0;
    double norm() { return std::sqrt(x*x + y*y + z*z); }
} Point;


Point operator+(Point a, Point b);
Point operator-(Point a, Point b);
double operator*(Point a, Point b);
Point operator/(Point a, double b);

class Cell {
    private:
        double area;
        bool areaComputed;
        std::vector<Point> pts;
        Point charPt;
        int numPts;
        int charId;

        void _orderPts();
        void _translate();
        void _translateBack();
        double _computeArea();


    public:
        Cell(std::vector<Point> p_pts, Point p_charPt, int p_numPts, int CharId);
        ~Cell();
        double getArea();
        double getNumPts();
        Point getCharPt();
        Point GetPoint(int index);
        int getCharPtId();
        std::string toString();
        static void test();
        static Point MeanPoints(std::vector<Point> points);
        static Point MeanPoints(Point pt1, Point pt2);
        static Point vtkPtsToPoint(vtkPoints *PointArray, int pid);
    
};

#endif