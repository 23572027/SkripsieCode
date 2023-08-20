#define debug1


/*
Units: All lengths are in um -> this extends to areas, volumes etc.. !
*/


#include <vtkGenericDataObjectReader.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>


#include <cmath>
#include <string>


double AreaFromPoints(double *p1, double *p2, double *p3);

// type to store points
typedef struct t_Point {
  double x;
  double y; 
  double z;
} t_Point;

// type to store point objects
typedef struct t_VTK_Pt  {
  t_Point loc;
  int pid;
}t_VTK_Pt;

int main(int argc, char* argv[])
{
  // Ensure a filename was specified.
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " InputFilename e.g. blow.vtk" << endl;
    return EXIT_FAILURE;
  }

  std::string inputFilename = argv[1];

  //init vtk generic data object
  vtkNew<vtkGenericDataObjectReader> reader;
  reader->SetFileName(inputFilename.c_str());
  reader->Update();

  if(reader->IsFileUnstructuredGrid()){
    std::cout << "Reading file" << std::endl;
    auto output = reader->GetUnstructuredGridOutput();
    vtkDataArray *ConnectivityArray = output->GetCells()->GetConnectivityArray();
    vtkPoints *PointArray = output->GetPoints();
    vtkPointData *PointData = output->GetPointData();

    // surface area example
    double SurfaceArea = 0.0;
    t_Point pt1;
    t_Point pt2;
    t_Point pt3;  
    for (int i = 0; i < ConnectivityArray->GetNumberOfTuples()-2;i+=3){
      // get 3 connected points
      double n_p1 = *(ConnectivityArray->GetTuple(i));
      double n_p2 = *(ConnectivityArray->GetTuple(i+1));
      double n_p3 = *(ConnectivityArray->GetTuple(i+2));
      // get points from Point array
      double *p1 = PointArray->GetPoint((int) n_p1);
      pt1.x = 1E6*p1[0]; pt1.y = 1E6*p1[1]; pt1.z = 1E6*p1[2];
      double *p2 = PointArray->GetPoint((int) n_p2);
      pt2.x = 1E6*p2[0]; pt2.y = 1E6*p2[1]; pt2.z = 1E6*p2[2];
      double *p3 = PointArray->GetPoint((int) n_p3);
      pt3.x = 1E6*p3[0]; pt3.y = 1E6*p3[1]; pt3.z = 1E6*p3[2];
      
      // perform area calculation.
      SurfaceArea += AreaFromPoints((double *) &pt1, ( double *) &pt2, (double *) &pt3);

    }
    // for testing purposes
    #ifdef debug
    std::cout << SurfaceArea;
    #endif

    // compute cell neighbors example
    output->BuildLinks();
    vtkIdType ncells;
    vtkIdType * cells;
    // woah we can select all cells belonging to a point using this function
    output->GetPointCells(28 , ncells, cells);
    // then take cells and get points with vtkgetcellpoints
    for (int i = 0; i < ncells; i++){
      std::cout << cells[i] << std::endl;
    }
    
  } else {
    std::cout << "Unkown file format (must be an unstructured grid)" << std::endl;
  }

  return EXIT_SUCCESS;
}



double AreaFromPoints(double *p1, double *p2, double *p3){
  // (p1 - p3) X (p2 - p3) -> norm -> div 2
  double diff1[3] = {p1[0] - p3[0], p1[1] - p3[1], p1[2] - p3[2]};
  double diff2[3] = {p2[0] - p3[0], p2[1] - p3[1], p2[2] - p3[2]};
  // double diff1[3] = {1.0,3.0,4.0};
  // double diff2[3] = {2.0,7.0,-5};

  // diff1 x diff2
  double cDiff[3] = {diff1[1]*diff2[2] - diff2[1]*diff1[2], diff1[2]*diff2[0] - diff2[2]*diff1[0],diff1[0]*diff2[1] - diff2[0]*diff1[1]};
  // magnitude
  double magCdiff = std::sqrt(std::pow(cDiff[0],2)+std::pow(cDiff[1],2)+std::pow(cDiff[2],2));


  // std::cout << cDiff[0] << "i "<< cDiff[1] << "j " << cDiff[2] << "k " << std::endl; 

  return magCdiff/2.0L;
}