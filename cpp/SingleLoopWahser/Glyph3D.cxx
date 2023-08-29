#define debug


//debugging 
#ifdef debug
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkDecimatePolylineFilter.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCellData.h>
#include <vtkLabeledDataMapper.h>
#include <vtkDoubleArray.h>
#include <vtkTextProperty.h>
#include <vtkActor2D.h>
#include <vtkPointData.h>
#endif

/*
Units: All lengths are in um -> this extends to areas, volumes etc.. !
*/


#include <vtkGenericDataObjectReader.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>



#include "geom.hh"
#include <cmath>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream &s, Cell cell){
    return s << cell.toString();
}

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

using namespace std;

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
    vtkPoints *PointArray = output->GetPoints();
    
    //vector to store cell data
    vector <Cell *> Cells;
    // compute cell neighbors 
    output->BuildLinks();
    
    // loop through all points  output->GetNumberOfPoints()
    auto num = output->GetNumberOfPoints();
    for (int i = 0; i < num; i++ ){
      // This gets each cell connected to this point (each triangle)
      //reused variables
      vtkIdType ncells;
      vtkIdType * tcells;
      output->GetPointCells(i, ncells, tcells);

      // point vector that hopefully gets cleared lol
      vector<Point> point_vec;
      
      for (int k = 0; k < ncells; k++) {

        
        vtkIdType npts;
        vtkIdType const * pts;

        // Then use cell ids to get points
        output->GetCellPoints(tcells[k],npts,pts);
        Point ptot = {0 , 0, 0, 0};
        // cout << "Cell: " << tcells[k] << " Pts: " << " CharPt: i";
        for (int j = 0; j< npts; j++){
          //ensure characteristic point is not included
          // cout << pts[j] << " ";
          if(pts[j] != i){
            // this is the incorrect implementation. We must find the geometric mean of all cells
            point_vec.push_back(Cell::MeanPoints(
              Cell::vtkPtsToPoint(PointArray,pts[j]),
              Cell::vtkPtsToPoint(PointArray,i)
              ));
          }
          // ptot = ptot + Cell::vtkPtsToPoint(PointArray,pts[j]);
          
        }
        Point p1 = Cell::vtkPtsToPoint(PointArray,pts[0]);
        Point p2 = Cell::vtkPtsToPoint(PointArray,pts[1]);
        Point p3 = Cell::vtkPtsToPoint(PointArray,pts[2]);
        // find circumcenter TODO: test
        double X_sol =  (p1.x*p1.x*p2.y - p1.x*p1.x*p3.y - p2.x*p2.x*p1.y + p2.x*p2.x*p3.y + p3.x*p3.x*p1.y - p3.x*p3.x*p2.y + p1.y*p1.y*p2.y - p1.y*p1.y*p3.y - p1.y*p2.y*p2.y + p1.y*p3.y*p3.y + p2.y*p2.y*p3.y - p2.y*p3.y*p3.y)/(2*(p1.x*p2.y - p2.x*p1.y - p1.x*p3.y + p3.x*p1.y + p2.x*p3.y - p3.x*p2.y));
        double Y_sol = (- p1.x*p1.x*p2.x + p1.x*p1.x*p3.x + p1.x*p2.x*p2.x - p1.x*p3.x*p3.x + p1.x*p2.y*p2.y - p1.x*p3.y*p2.y - p2.x*p2.x*p3.x + p2.x*p3.x*p3.x - p2.x*p1.y*p1.y + p2.x*p3.y*p3.y + p3.x*p1.y*p1.y - p3.x*p2.y*p2.y)/(2*(p1.x*p2.y - p2.x*p1.y - p1.x*p3.y + p3.x*p1.y + p2.x*p3.y - p3.x*p2.y));
        double Z_sol = p1.z;
        ptot = ptot/(double) npts;
        point_vec.push_back(ptot);
        // cout << endl;

      }
      //create new cell object
        Cells.push_back(new Cell(point_vec, Cell::vtkPtsToPoint(PointArray,i), point_vec.size(),i));

    }

    // surface area example
    // double SurfaceArea = 0.0;
    // t_Point pt1;
    // t_Point pt2;
    // t_Point pt3;  
    // for (int i = 0; i < ConnectivityArray->GetNumberOfTuples()-2;i+=3){
    //   // get 3 connected points
    //   double n_p1 = *(ConnectivityArray->GetTuple(i));
    //   double n_p2 = *(ConnectivityArray->GetTuple(i+1));
    //   double n_p3 = *(ConnectivityArray->GetTuple(i+2));
    //   // get points from Point array
    //   double *p1 = PointArray->GetPoint((int) n_p1);
    //   pt1.x = 1E6*p1[0]; pt1.y = 1E6*p1[1]; pt1.z = 1E6*p1[2];
    //   double *p2 = PointArray->GetPoint((int) n_p2);
    //   pt2.x = 1E6*p2[0]; pt2.y = 1E6*p2[1]; pt2.z = 1E6*p2[2];
    //   double *p3 = PointArray->GetPoint((int) n_p3);
    //   pt3.x = 1E6*p3[0]; pt3.y = 1E6*p3[1]; pt3.z = 1E6*p3[2];
    // }

    #ifdef debug
    // draw poly data
    vtkSmartPointer<vtkUnsignedCharArray> col = vtkSmartPointer<vtkUnsignedCharArray>::New();
    col->SetName("Colors");
    col->SetNumberOfComponents(3);

    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> polygon = vtkSmartPointer<vtkCellArray>::New();
    int increment = 0;
    auto n = (double) Cells.size();
    double inc = 0.f;
    for (Cell *c : Cells){
      for (int i = 0; i < c->getNumPts(); i++){
        points->InsertNextPoint(PT(c->GetPoint(i)));
      }
      polygon->InsertNextCell(c->getNumPts()+1);
      for (int j = 0; j < c->getNumPts(); j++){
        polygon->InsertCellPoint(j+increment);
      }
      polygon->InsertCellPoint(increment);
      increment += c->getNumPts();
      double p[3] = {0+inc/n*255,0+inc/n*255,0+inc/n*255};
      col->InsertNextTuple(p);
      inc++;
    }

    polyData->SetPoints(points);
    polyData->SetLines(polygon);
    
    polyData->GetPointData()->SetScalars(col);
    
    // plotting stuff
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkPolyDataMapper> c_mapper;
    c_mapper->SetInputData(polyData);
    c_mapper->ScalarVisibilityOff();


    vtkNew<vtkActor> c_actor;
    c_actor->SetMapper(c_mapper);
//    c_actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    c_actor->GetProperty()->SetLineWidth(3);
    vtkNew<vtkRenderer> ren;
    ren->AddActor(c_actor);
    ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
    vtkNew<vtkRenderWindow> renwin;
    renwin->AddRenderer(ren);
    renwin->SetSize(640, 480);
    renwin->SetWindowName("DecimatePolyline");
    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renwin);
    renwin->Render();
    iren->Start();
    #endif


    //clean up memory
    double area = 0; 
    for(Cell * c : Cells){
      area += c->getArea();
      // cout << *c << endl;
      delete c;
    }
    cout << area;

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