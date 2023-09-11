//
// Created by paul on 9/11/23.
//

#include "Point.h"


Point operator+(Point a, Point b){
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
Point operator-(Point a, Point b){
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
double operator*(Point a, Point b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Point operator/(Point a,double b){
    return {a.x/b, a.y/b, a.z/b};
}
std::ostream& operator<<(std::ostream &s, Point pt) {
    return s << "(x: " << pt.x << "\t y: " << pt.y << "\t z:" << pt.z<< ")";
}


simplePoint operator+(simplePoint a, simplePoint b){
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
simplePoint operator-(simplePoint a, simplePoint b){
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
double operator*(simplePoint a, simplePoint b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
simplePoint operator/(simplePoint a,double b){
    return {a.x/b, a.y/b, a.z/b};
}
std::ostream& operator<<(std::ostream &s, simplePoint pt) {
    return s << "(x: " << pt.x << "\t y: " << pt.y << "\t z:" << pt.z<< ")";
}


/*
 * [(p1.y * b3 – a3 * b2), (a3 * b1 – a1 * b3), (a1 * b2 – p1.y * b1)]
 */

Point cross(Point p1, Point p2){
    return (Point) {p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x};
}

simplePoint cross(simplePoint p1, simplePoint p2){
    return (simplePoint) {p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x};
}