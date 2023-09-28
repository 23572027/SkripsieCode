// vars
r1 = %r1; //15e-6
r2 = %r2; //0.2e-6


Mesh.MeshSizeFromPoints = 0;
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeFromCurvature = 10;

Mesh.CharacteristicLengthMin = 1e-10;
Mesh.CharacteristicLengthMax = 1e-6;

SetFactory("OpenCASCADE");
Mesh.MshFileVersion = 2.2;    //  Fix the mesh version to 2.2 - this works best for TTH
Mesh.Algorithm = 5;
Mesh.Algorithm3D = 1;
Mesh.OptimizeNetgen = 1;  

Point(17) = {0, 0, -1E-5, 1.5};
Point(18) = {0, 0, 1E-5, 1.5};
Line(25) = {17, 18};


Torus(1) = {0, 0, 0, r1, r2, 2*Pi};


Physical Volume("T0_ybco") = {1};
Physical Line("fone") = {25};

Mesh 3;

Save "loop.msh";

