// asd
Mesh.MeshSizeFromPoints = 0;
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeFromCurvature = 0;
Mesh.MshFileVersion = 2.2;    //  Fix the mesh version to 2.2 - this works best for TTH
Mesh.Algorithm = 5;
Mesh.Algorithm3D = 1;
Mesh.OptimizeNetgen = 1;  
//Mesh.MeshSizeMin = 10e-5;
//Mesh.MeshSizeMax = 10e-5;

//+
SetFactory("OpenCASCADE");
//+
R = 1e-3;
W1 = 300e-6;
W2 = 550e-6;
Z = 0.2e-6;

Rectangle(2) = {-R/2, -R/2, -Z, R, R, 0};


//+
Rectangle(3) = {-(R-W1-W2)/2,-(R-W1-W2)/2, -Z, (R-W1-W2), (R-W1-W2), 0};

slotW = W2*0.6;
slotH = 10e-6;

Rectangle(4) = {-(R-W1-W2)/2-slotW,-slotH/2, -Z, slotW, slotH, 0};
Rectangle(5) = {(R-W1-W2)/2,-slotH/2, -Z, slotW, slotH, 0};


//+
Delete {
  Surface{3}; 
}
//+
Delete {
  Curve{6}; 
}
//+
Delete {
  Curve{16}; 
}
//+
Delete {
  Surface{5}; 
}
//+
Delete {
  Curve{16}; 
}
//+
Delete {
  Surface{4}; 
}
//+
Delete {
  Curve{8}; 
}
//+
Delete {
  Curve{10}; 
}


//+
Line(16) = {8, 11};
//+
Line(17) = {10, 5};
//+
Line(18) = {6, 13};
//+
Line(19) = {16, 7};
//+


//+
Curve Loop(5) = {7, 16, 11, 12, 9, 17, 5, 18, 13, 14, 15, 19};
//+
Surface(3) = {5};

//+ 2 3
BooleanDifference(4) = {Surface{2}; Delete;}{Surface{3}; Delete;};

//+
Extrude {0, 0, Z*2} {
  Surface{4}; 
}
//+
Surface Loop(2) = {21, 5, 6, 8, 7, 4, 9, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10};


Point(100) = {0, 0, -1E-5, 1.5};
Point(400) = {0, 0, 1E-5, 1.5};
Line(300) = {100, 400};

Physical Volume("T0_ybco") = {1};
Physical Line("fone") = {300};

Coherence;
Mesh 3;
Save "loop.msh";
