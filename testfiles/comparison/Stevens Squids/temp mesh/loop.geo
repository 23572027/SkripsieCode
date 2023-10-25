// asd
Mesh.MeshSizeFromPoints = 0;
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeFromCurvature = 0;
Mesh.MshFileVersion = 2.2;    //  Fix the mesh version to 2.2 - this works best for TTH
Mesh.Algorithm = 5;
Mesh.Algorithm3D = 1;
Mesh.OptimizeNetgen = 1;  
Mesh.MeshSizeMin = 40e-6;
Mesh.MeshSizeMax = 40e-6;

R = 100E-6;
W = 50E-6;
Z = 100E-9;
C = R - W;


Point(1) = {-C,C,-Z};
Point(2) =  {C,C,-Z};
Point(3) = {C,-C,-Z};
Point(4) = {-C,-C,-Z};

Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,1};




Point(9) = {-R,R,-Z};
Point(10) =  {R,R,-Z};
Point(11) = {R,-R,-Z};
Point(12) = {-R,-R,-Z};

Line(9) = {9,10};
Line(10) = {10,11};
Line(11) = {11,12};
Line(12) = {12,9};

Point(100) = {0, 0, -1E-5, 1.5};
Point(400) = {0, 0, 1E-5, 1.5};
Line(300) = {100, 400};


Curve Loop(1) = {12, 9, 10, 11};
Curve Loop(2) = {4, 1, 2, 3};
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

