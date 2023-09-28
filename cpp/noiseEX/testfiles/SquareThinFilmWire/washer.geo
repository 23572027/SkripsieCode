//mesh params
Mesh.MeshSizeFromPoints = 0;
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeFromCurvature = 0;
Mesh.CharacteristicLengthMin = 1e-10;
Mesh.CharacteristicLengthMax = 1e-7;
Mesh.MshFileVersion = 2.2;    //  Fix the mesh version to 2.2 - this works best for TTH
Mesh.Algorithm = 5;
Mesh.Algorithm3D = 1;
Mesh.OptimizeNetgen = 1;  

//vars
zoff=0.2e-6; //thickness
R=15e-6; // loop radius
W=2e-6; // track width

//+
SetFactory("OpenCASCADE");
Circle(1) = {0, 0, -zoff/2, R, 0, 2*Pi};
//+
Circle(2) = {0, 0, -zoff/2, R-W, 0, 2*Pi};
//+
Curve Loop(1) = {1};
//+
Curve Loop(2) = {2};
//+
Plane Surface(1) = {1, 2};
//+
Extrude {0, 0, zoff} {
  Surface{1}; 
}

Point(17) = {0, 0, -1E-5, 1.5};
Point(18) = {0, 0, 1E-5, 1.5};
Line(25) = {17, 18};

Physical Volume("T0_ybco") = {1};
Physical Line("fone") = {25};

Coherence;
Mesh 3;
Save "washer.msh";

