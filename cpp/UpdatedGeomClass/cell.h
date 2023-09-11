/**
 * @author: Paul Rossouw
 * @brief: A simple class for storing subcell objects.
 *  Interact with class by adding points using the points push method (automaticall adds it to correct cell vector)
 *  Sorts subcells by the plane they belong to.
 */

#ifndef GLYPH3D_CELL_H
#define GLYPH3D_CELL_H
#include "subCell.h"
#include <vector>
#include <unordered_map>
#include <memory>


using namespace std;

class cell {
    public:
        cell();
        void pushPoints(Point p, Point norm, Point mid);
        void printPoints();
    private:
        unordered_map<Point, shared_ptr<subCell>, point_hash> ptMap;
};


#endif //GLYPH3D_CELL_H
