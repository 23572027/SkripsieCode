// asd
Mesh.MeshSizeFromPoints = 0;
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeFromCurvature = 0;
Mesh.MshFileVersion = 2.2;    //  Fix the mesh version to 2.2 - this works best for TTH
Mesh.Algorithm = 5;
Mesh.Algorithm3D = 1;
Mesh.OptimizeNetgen = 1;  
//Mesh.MeshSizeMin = 1e-5;
//Mesh.MeshSizeMax = 1e-5;

R = 200E-6;
W = 50E-6;
Z = 0.2E-6;
C = (R - 2*W)/2;
X = R/2;
SH = 0.1E-6;
SW = 5E-6;


Point(1) = {-C,C,-Z};
Point(2) =  {C,C,-Z};
Point(3) = {C,-C,-Z};
Point(4) = {SW/2,-C,-Z};
Point(5) = {SW/2,-(C+SH),-Z};
Point(6) = {-SW/2,-(C+SH),-Z};
Point(7) = {-SW/2,-C,-Z};
Point(8) = {-C,-C,-Z};

Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,5};
Line(5) = {5,6};
Line(6) = {6,7};
Line(7) = {7,8};
Line(8) = {8,1};




Point(9) = {-X,X,-Z};
Point(10) =  {X,X,-Z};
Point(11) = {X,-X,-Z};
Point(12) = {SW/2,-X,-Z};
Point(13) = {SW/2,-(X-SH),-Z};
Point(14) = {-SW/2,-(X-SH),-Z};
Point(15) = {-SW/2,-X,-Z};
Point(16) = {-X,-X,-Z};

Line(9) = {9,10};
Line(10) = {10,11};
Line(11) = {11,12};
Line(12) = {12,13};
Line(13) = {13,14};
Line(14) = {14,15};
Line(15) = {15,16};
Line(16) = {16,9};


Point(100) = {0, 0, -1E-5, 1.5};
Point(400) = {0, 0, 1E-5, 1.5};
Line(300) = {100, 400};


Curve Loop(1) = {16, 9, 10, 11, 12, 13, 14, 15};
Curve Loop(2) = {8, 1, 2, 3, 4, 5, 6, 7};
Plane Surface(1) = {1, 2};
//+
Extrude {0, 0, Z*2} {
  Surface{1}; 
}

Physical Line("fone") = {300};
Physical Volume("T0_ybco") = {1};


Coherence;
Mesh 3;
Coherence;
Save "loop.msh";

