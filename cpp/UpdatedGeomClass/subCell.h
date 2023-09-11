/**
 * @author Paul Rossouw
 * @brief A very simple class that abstracts the area calculation of cells. The input is unordered points
 * of a polygon. The points are ALWAYS coplanar. The cell class abstracts this. Makes use of the shoelace algorithm
 * to calculate areas. This class has nothing to do with msfn and only stores geometry data. the cell class stores the
 * field data.
 */

#ifndef GLYPH3D_SUBCELL_H
#define GLYPH3D_SUBCELL_H
#include "Point.h"
#include <vector>

#define PI 3.141592653589793238463

using namespace std;

class subCell {
    public:
        subCell(vector<simplePoint> pts, simplePoint center, simplePoint norm);
        double getArea();
    private:
        simplePoint mid;
        vector<simplePoint> points;
        simplePoint normal;
        simplePoint u; //Line to first point
        simplePoint v; // perpendicular to first point and plane normal
        double area;
        bool areaComputed;

        void _orderPts();
        void _translate();
        void _translateBack();
        double _computeArea();
        double _angleUV(simplePoint p1);
        bool comparePt(simplePoint p1, simplePoint p2);
};


#endif //GLYPH3D_SUBCELL_H
