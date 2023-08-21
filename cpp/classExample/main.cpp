#include <iostream>
#include <iomanip>
#include "geom.hh"



int main(){
    
    std::vector<Point> pts = {{-2, 2, 0},{0, 1, 0},{-1, 0, 0},{-1.5, 0, 0}};
    // pts.push_back({0, 1, 0});
    // pts.push_back({1, 1, 0});
    // pts.push_back({1, 0, 0});
    // pts.push_back({0, 0, 0});
    Point charPt = {0.5, 0.5, 0};
    int numpts = 4;
    Cell *nCell = new Cell(pts,charPt,numpts);
    std::cout << nCell->getArea() << std::endl;  
    delete nCell;
    return 1;
}

