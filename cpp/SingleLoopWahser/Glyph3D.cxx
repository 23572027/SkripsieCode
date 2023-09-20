/**
 * old geometry class
 */

#include "Geommetry.h"
#include "geom.hh"


using namespace std;

int main(int argc, char* argv[])
{

    Geommetry g("B_washer.vtk");
    g.debugDraw();
    cout << g.getArea();
//    Cell c(points,(Point) {0.5, 0.5 , 0},6,0,(Point){0,0,0});

//    std::vector<Point> cell1 = {{0,0,0} , {0,1,0}, {1,0,0}};
//    std::vector<Point> cell2 = {{1,0,0} , {0,1,0}, {1,0,0}};
//    std::vector<Point> cell3 = {{1, 1, 0}, {1,0,-1}, {1, 1, -1}};

//
//    double v_z = points[0].z;
//    double v_z_prev = v_z;
//
//    for (auto v : points){
//        if (v_z != v_z_prev){
//
//        }

//    }
  return EXIT_SUCCESS;
}