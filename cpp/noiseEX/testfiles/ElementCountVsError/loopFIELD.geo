// vars
r1 = 15e-6; //15e-6
r2 = 0.2e-6; //0.2e-6


Mesh.MeshSizeFromPoints = 0;
Mesh.MeshSizeExtendFromBoundary = 0;
Mesh.MeshSizeFromCurvature = %c;

Mesh.CharacteristicLengthMin = 1e-10;
Mesh.CharacteristicLengthMax = 1e-6;

SetFactory("OpenCASCADE");
Mesh.MshFileVersion = 2.2;    //  Fix the mesh version to 2.2 - this works best for TTH
Mesh.Algorithm = 5;
Mesh.Algorithm3D = 1;
Mesh.OptimizeNetgen = 1;  



Torus(1) = {0, 0, 0, r1, r2, 2*Pi};

Physical Surface("Fieldplane0") = {1};


Mesh 2;

Save "loopFIELD.msh";

Print.PostGamma = 1;
