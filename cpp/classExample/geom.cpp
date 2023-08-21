#define PI 3.141592653589793238463

#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>


#include "geom.hh"
using namespace std;

Point operator+(Point a, Point b){
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
Point operator-(Point a, Point b){
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
double operator*(Point a, Point b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// helper methods -> TODO: move to static methods in class
// angle of points used in sorting
double angleXY(Point p){
    double angle = atan(p.y/p.x);
    double add = 0;
        // second quadrant
    if (p.y > 0 && p.x < 0){
        add = PI;
    } else if (p.y < 0 && p.x < 0){
        // third quadrant
        add = PI;
    } else if (p.y < 0 && p.x > 0){
        //thirds quadrant
        add = 2 * PI;
    }
    return angle + add;
}
// for sorting the points
bool comparePoint(Point p1, Point p2){
    return angleXY(p1) > angleXY(p2);
}


// class methods
Cell :: Cell(vector<Point> p_pts, Point &p_charPt, int p_numPts) : 
      pts(p_pts),
      charPt(p_charPt),
      numPts(p_numPts) 
    {
        getArea();
    }

Cell :: ~Cell(){

}


void Cell :: _translate() {
    // implement and test
    for(Point &pt : this->pts){
        pt = pt - this->charPt;
    }
}

void Cell :: _orderPts(){
    //implement and test
    #ifdef debug
    cout << "Before sort" << endl;
    for (Point pt : pts){
        cout << pt.x << " " << pt.y << " " << angleXY(pt) << endl;
    }
    cout << "After sort" << endl;
    #endif
    
    sort(pts.begin(),pts.end(), comparePoint);
}

double Cell :: _computeArea(){
    //implement and test
    double sum1, sum2 = 0;
    // calculate area given ordered points
    for (int i = 0; i < numPts; i++){
        int sindex = (i+1) % numPts;
        sum1 += pts.at(i).x*pts.at(sindex).y;
        sum2 += pts.at(sindex).x*pts.at(i).y;
    }
    
    double tot = 1/2.0 * abs(sum1 - sum2);
    return tot;
}


double Cell :: getArea() {
    if (areaComputed == true) return area;

    this->_translate();
    this->_orderPts();
    double area = this->_computeArea();
    this->area = area;
    areaComputed = true;
    return area;
}

