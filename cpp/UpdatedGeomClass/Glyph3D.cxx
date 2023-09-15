

//#include "Geommetry.h"
//#include "geom.hh"
//#include "subCell.h"
#include "cell.h"
#include "noiseEx.h"





using namespace std;

int main(int argc, char* argv[])
{
    noiseEx g("B_washer2.vtk");

    cout << g.getArea();

    g.debugDraw();

//    Point p1 = {-1, 0, 0};
//    Point p2 = {0, 2, 0};
//    Point p3 = {1, 0, 0};
//
//    Point bottom = cross(p1-p2,p2-p3);
//    double bot = (bottom*bottom)*2;
//    double alpha = ((p2 - p3)*(p2 - p3))*((p1-p2)*(p1-p3))/bot;
//    double beta = ((p1 - p3)*(p1 - p3))*((p2-p1)*(p2-p3))/bot;
//    double gamma = ((p1 - p2)*(p1 - p2))*((p3-p1)*(p3-p2))/bot;
//    Point pc = alpha *p1 + beta*p2 + gamma*p3;
//
//    cout << pc;


    return EXIT_SUCCESS;
}