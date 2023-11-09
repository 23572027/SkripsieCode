//+

Mesh.MshFileVersion = 2.2;

//+

R = 40e-6;
Z = 20e-6;
lc = 5e-6;
//+
Point(1) = {R, R, -Z, lc};
//+
Point(2) = {-R, R, -Z, lc};
//+
Point(3) = {-R, -R, -Z, lc};
//+
Point(4) = {R, -R, -Z, lc};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 1};
//+
Curve Loop(1) = {1, 2, 3, 4};
//+
Plane Surface(1) = {1};
//+
Extrude {0, 0, 2*Z} {
  Surface{1}; 
}
Physical Volume("FieldPlane0") = {1};

Mesh 3;
Save "loopFIELD.msh";
