// asd
Mesh.MeshSizeFromPoints = 0;
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeFromCurvature = 0;
Mesh.MshFileVersion = 2.2;    //  Fix the mesh version to 2.2 - this works best for TTH
Mesh.Algorithm = 5;
Mesh.Algorithm3D = 1;
Mesh.OptimizeNetgen = 1;  
//Mesh.MeshSizeMin = 1e-6;
//Mesh.MeshSizeMax = 1e-6;

//+
SetFactory("OpenCASCADE");
//+
R = 100e-6;
W1 = 2e-6;
W2 = 0;
Z = 0.2e-6;

Rectangle(2) = {-R/2, -R/2, -Z, R, R, 0};


//+
Rectangle(3) = {-(R-W1-W2)/2,-(R-W1-W2)/2, -Z, (R-W1-W2), (R-W1-W2), 0};




//+
BooleanDifference(4) = { Surface{2}; Delete; }{ Surface{3}; Delete; };
//+
Extrude {0, 0, Z*2} {
  Surface{4}; 
}








//+
Physical Surface("FieldPlane0", 25) = {5, 9, 4, 13, 6, 12, 8, 11, 10, 7};


Coherence;
//Mesh 2;
//Save "loopFIELD.msh";

