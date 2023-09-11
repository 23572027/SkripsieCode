

//#include "Geommetry.h"
//#include "geom.hh"
#include "subCell.h"
#include "cell.h"

using namespace std;

int main(int argc, char* argv[])
{
//
//    vector<simplePoint> pts = {{0,2,0},
//                               {2,2,0},
//                               {-2,-2,0},
//                               {2,-2,0},
//                               {-2,2,0}};
//    simplePoint mid = {0,0,0};
//    simplePoint normal = {0, 0, 1};
//
//    subCell sub(pts,mid,normal);

    // Example usage
    Point p1 = {1.0, 2.0, 3.0};
    Point p2 = {4.0, 5.0, 6.0};
    Point p3 = {1.0, 2.0, 3.0};

    cell c;
    c.pushPoints(p2,p1);
    c.pushPoints(p3,p3);
    c.pushPoints(p2,p2);
//    c.pushPoints(p2);
    c.printPoints();
    return EXIT_SUCCESS;
}