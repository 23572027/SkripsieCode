//
// Created by paul on 9/11/23.
//

//#define debug
#include "subCell.h"




subCell::subCell(vector<simplePoint> pts, simplePoint center, simplePoint norm): points(std::move(pts)), mid(center), normal(norm) {
    this->_translate();
    areaComputed = false;
    v = points[0];
    v = v / v.norm();
    u = cross(v,normal);
    u = u / u.norm();
#ifdef  debug
    for (auto pt : points){
        cout << 180/PI * this->_angleUV(pt) << "\t" << pt << endl;
    }
#endif
    this->_orderPts();
#ifdef debug
    for (auto pt : points){
        cout << 180/PI * this->_angleUV(pt) << "\t" << pt << endl;
    }
#endif
    cout << this->_computeArea();
}

void subCell::_translate() {
    for(auto pt: points){
        pt = pt - mid;
    }
}

void subCell::_orderPts() {
    int n = (int) points.size();
    for (int i = 1; i < n; i++) {
        simplePoint key = points[i];
        int j = i - 1;
        while (j >= 0 && this->comparePt(points[j],key)) {
            points[j + 1] = points[j];
            j--;
        }
        points[j + 1] = key;
    }
}

double subCell::_computeArea() {

    areaComputed = true;

    simplePoint pt0 = points[0];
    simplePoint pt_s = {0,0,0};
    for (int i = 0; i < points.size(); i++){
        pt_s = pt_s + (cross(points[i] - pt0, points[(i+1) % points.size()] - pt0));
    }
    area = pt_s.norm()/2;
    return area;
}

void subCell::_translateBack() {

}

double subCell::_angleUV(simplePoint p1) {
    double u_component = p1 * u;
    double v_component = p1 * v;
    double n = p1.norm();
    double angle = acos(v_component/n);

    if(!signbit(v_component)){
        // first or second quad (positive in the up direction)
        if (signbit(u_component)) {
            // second quadrant (negative in the right direction)
            angle = 2*PI - angle;
        }
    } else {
        // fourth or third quad
        if (signbit(u_component)){
            // negative in the right direction (third quadrant)
            angle = PI/2 + angle;
        } else {
            // fourth quadrant
            angle =  angle;
        }
    }
    return angle;
}


bool subCell::comparePt(simplePoint p1, simplePoint p2) {
    return this->_angleUV(p1) > this->_angleUV(p2);
}

double subCell::getArea() {
    if (areaComputed) {return area;};
    return this->_computeArea();
}
