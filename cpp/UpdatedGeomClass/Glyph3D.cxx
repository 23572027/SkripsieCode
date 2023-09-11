

//#include "Geommetry.h"
//#include "geom.hh"
#include "subCell.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<simplePoint> pts = {{0,2,0},
                               {2,2,0},
                               {-2,-2,0},
                               {2,-2,0},
                               {-2,2,0}};
    simplePoint mid = {0,0,0};
    simplePoint normal = {0, 0, 1};

    subCell sub(pts,mid,normal);

    return EXIT_SUCCESS;
}