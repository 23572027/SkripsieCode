//
// Created by paul on 9/11/23.
//

#include "cell.h"

cell::cell() {

}

// automatically organizes subcells by the plane they belong to.
void cell::pushPoints(Point p, Point norm) {
    bool found = false;
    for (const auto& ptPair : ptsMap){
        if(ptPair.first == norm){
            ptPair.second->pushPoint((simplePoint)p);
            found = true;
            break;
        }
    }
    if(!found){
     // Create new subCell
        ptsMap.emplace_back(norm, make_shared<subCell>((simplePoint) norm));
        ptsMap.back().second->pushPoint((simplePoint) p);
    }
}

void cell::printPoints() {
    for (const auto& entry: ptsMap){
        std::cout << "Key (" << entry.first.x << ", " << entry.first.y << ", " << entry.first.z << "): ";
        entry.second->printPoints();
        std::cout << std::endl;
    }
}

double cell::getArea() {
    double area = 0;
    for (const auto& entry: ptsMap){
        area += entry.second->getArea();
    }
    return area;
}

Point cell::isPlaneInMap(Point p1, Point p2) {
//    Point comp1 = cross(p1,p2);
//    comp1 = comp1/comp1.norm();
//    Point comp2 = cross(p2,p1);
//    comp2 = comp2/comp2.norm();
//
//    auto it = ptMap.find(comp1);
//    if (it != ptMap.end()){
//        return it->first;
//    }
//    it = ptMap.find(comp2);
//    if (it != ptMap.end()){
//        return it->first;
//    }

    // not implemented

    return {0,0,0};
}

int cell::getNumPoints() {
    int sum = 0;
    for(const auto& pt : ptsMap){
        sum += pt.second->getNumPoints();
    }
    return sum;
}


Point cell::getPoint(int index) {
    int sum = 0;
    Point p;
    for (auto pt : ptsMap) {
        sum += pt.second->getNumPoints();
        if (index < sum){
            p = pt.second->getPoint(index - sum - pt.second->getNumPoints());
        }
    }


    return p;
}

const vector<pair<Point, shared_ptr<subCell>>> &cell::getPtsMap() const {
    return ptsMap;
}

int cell::getNumSubCell() {
    int size = (int) ptsMap.size();
    return size;
}

