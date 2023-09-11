//
// Created by paul on 9/11/23.
//

#include "cell.h"

cell::cell() {

}

void cell::pushPoints(Point p, Point norm, Point mid) {
    auto it = ptMap.find(norm);
    if (it != ptMap.end()){
        it->second->pushPoint((simplePoint) p);
    } else {
        //create new subcell
        ptMap[norm] = make_shared<subCell>((simplePoint) mid, (simplePoint) norm);
        ptMap[norm]->pushPoint((simplePoint) p);
    }
}

void cell::printPoints() {
    for (const auto& entry: ptMap){
        std::cout << "Key (" << entry.first.x << ", " << entry.first.y << ", " << entry.first.z << "): ";
        entry.second->printPoints();
        std::cout << std::endl;
    }
}

