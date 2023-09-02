#define B_PT(v) {v[0], v[1], v[3]}

#include "Geommetry.h"
// Temporary current data for loop
#define curr 0.79190019755 Amps

#define debug


//debugging 
#ifdef debug
//#include <vtkDecimatePolylineFilter.h>
//#include <vtkMath.h>
//#include <vtkLabeledDataMapper.h>
//#include <vtkTextProperty.h>
//#include <vtkActor2D.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#endif

/*
Units: All lengths are in um -> this extends to areas, volumes etc.. !
*/


#include <vtkGenericDataObjectReader.h>
//#include <vtkNew.h>
//#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
//#include <vtkUnstructuredGrid.h>



#include "geom.hh"
#include <cmath>
#include <string>
#include <vector>

std::ostream& operator<<(std::ostream &s, Cell cell){
    return s << cell.toString();
}


using namespace std;

int main(int argc, char* argv[])
{

//  // Ensure a filename was specified.
//  if (argc != 2)
//  {
//    std::cerr << "Usage: " << argv[0] << " InputFilename e.g. blow.vtk" << endl;
//    return EXIT_FAILURE;
//  }
//
//  std::string inputFilename = argv[1];
//
//  //init vtk generic data object
//  vtkNew<vtkGenericDataObjectReader> reader;
//  reader->SetFileName(inputFilename.c_str());
//  reader->Update();
//
//  if(reader->IsFileUnstructuredGrid()){
//
//    std::cout << "Reading file" << std::endl;
//    auto output = reader->GetUnstructuredGridOutput();
//    vtkPoints *PointArray = output->GetPoints();
//    // get data array
//    vtkDoubleArray* D_array = vtkDoubleArray::SafeDownCast(output->GetPointData()->GetArray("10.000GHz_fone_imag"));
//    //vector to store cell data
//    vector <Cell *> Cells;
//    // compute cell neighbors
//    output->BuildLinks();
//
//    // loop through all points  output->GetNumberOfPoints()
//    auto num = output->GetNumberOfPoints();
////    int num = 34;
//    for (int i = 0; i < num; i++ ){
//      // This gets each cell connected to this point (each triangle)
//      //reused variables
//      vtkIdType ncells;
//      vtkIdType * tcells;
//      output->GetPointCells(i, ncells, tcells);
//
//      // point vector that hopefully gets cleared lol
//      vector<Point> point_vec;
//
//      for (int k = 0; k < ncells; k++) {
//
//        vtkIdType npts;
//        vtkIdType const * pts;
//
//        // Then use cell ids to get points
//        output->GetCellPoints(tcells[k],npts,pts);
//        for (int j = 0; j< npts; j++){
//
//          if(pts[j] != i){
//              // for boundry conditions
//            point_vec.push_back(Cell::MeanPoints(
//              Cell::vtkPtsToPoint(PointArray,(int)pts[j]),
//              Cell::vtkPtsToPoint(PointArray,i)
//              ));
//          }
//          // ptot = ptot + Cell::vtkPtsToPoint(PointArray,pts[j]);
//
//        }
//        //compute circumcenter
//        Point p1 = Cell::vtkPtsToPoint(PointArray,(int)pts[0]);
//        Point p2 = Cell::vtkPtsToPoint(PointArray,(int)pts[1]);
//        Point p3 = Cell::vtkPtsToPoint(PointArray,(int)pts[2]);
//        double X_sol =  (p1.x*p1.x*p2.y - p1.x*p1.x*p3.y - p2.x*p2.x*p1.y + p2.x*p2.x*p3.y + p3.x*p3.x*p1.y - p3.x*p3.x*p2.y + p1.y*p1.y*p2.y - p1.y*p1.y*p3.y - p1.y*p2.y*p2.y + p1.y*p3.y*p3.y + p2.y*p2.y*p3.y - p2.y*p3.y*p3.y)/(2*(p1.x*p2.y - p2.x*p1.y - p1.x*p3.y + p3.x*p1.y + p2.x*p3.y - p3.x*p2.y));
//        double Y_sol = (-p1.x*p1.x*p2.x + p1.x*p1.x*p3.x + p1.x*p2.x*p2.x - p1.x*p3.x*p3.x + p1.x*p2.y*p2.y - p1.x*p3.y*p3.y - p2.x*p2.x*p3.x + p2.x*p3.x*p3.x - p2.x*p1.y*p1.y + p2.x*p3.y*p3.y + p3.x*p1.y*p1.y - p3.x*p2.y*p2.y)/(2*(p1.x*p2.y - p2.x*p1.y - p1.x*p3.y + p3.x*p1.y + p2.x*p3.y - p3.x*p2.y));
//        double Z_sol = p1.z;
//        point_vec.push_back({X_sol,Y_sol,Z_sol});
//
//      }
//        //create new cell object
//        double *vecDat = D_array->GetTuple3(i);
//        if (ncells <= 2) {
//            point_vec.push_back(Cell::vtkPtsToPoint(PointArray,i));
//            Point charpt = Cell::MeanPoints(point_vec);
//            Cells.push_back(new Cell(point_vec, charpt, (int)point_vec.size(),i, B_PT(vecDat)));
//        } else {
//            Cells.push_back(new Cell(point_vec, Cell::vtkPtsToPoint(PointArray,i), (int)point_vec.size(),i,B_PT(vecDat)));
//        }
////#ifdef debug
////        Point vec = Cells[i]->getB();
////        cout << vec << endl;
////#endif
//    }
//
//    #ifdef debug
//    // draw poly data
//    vtkSmartPointer<vtkUnsignedCharArray> col = vtkSmartPointer<vtkUnsignedCharArray>::New();
//    col->SetName("Colors");
//    col->SetNumberOfComponents(3);
//
//    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
//    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    vtkSmartPointer<vtkCellArray> polygon = vtkSmartPointer<vtkCellArray>::New();
//    int increment = 0;
//    auto n = (double) Cells.size();
//    double inc = 0.f;
//    for (Cell *c : Cells){
//      for (int i = 0; i < c->getNumPts(); i++){
//        points->InsertNextPoint(PT(c->GetPoint(i)));
//      }
//      polygon->InsertNextCell((int)c->getNumPts()+1);
//      for (int j = 0; j < c->getNumPts(); j++){
//        polygon->InsertCellPoint(j+increment);
//      }
//      polygon->InsertCellPoint(increment);
//      increment += (int) c->getNumPts();
//      double p[3] = {0+inc/n*255,0+inc/n*255,0+inc/n*255};
//      col->InsertNextTuple(p);
//      inc++;
//    }
//
//    polyData->SetPoints(points);
//    polyData->SetLines(polygon);
//
//    polyData->GetPointData()->SetScalars(col);
//
//    // plotting stuff
//    vtkNew<vtkNamedColors> colors;
//
//    vtkNew<vtkArrowSource> arrowSource;
//    vtkNew<vtkGlyph3D> Glyph3D;
//    Glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
////    Glyph3D->SetVectorModeToUseNormal();
//    Glyph3D->SetInputData(output);
//    Glyph3D->SetScaleFactor(.000002);
//    Glyph3D->Update();
//
//    vtkNew<vtkPolyDataMapper> g_mapper;
//    g_mapper->SetInputConnection(Glyph3D->GetOutputPort());
//
//    vtkNew<vtkPolyDataMapper> c_mapper;
//    c_mapper->SetInputData(polyData);
//    c_mapper->ScalarVisibilityOff();
//
//
//    vtkNew<vtkActor> c_actor;
//    c_actor->SetMapper(c_mapper);
////    c_actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
//    c_actor->GetProperty()->SetLineWidth(3);
//
//    vtkNew<vtkActor> g_actor;
//    g_actor->SetMapper(g_mapper);
//    g_actor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());
//
//    vtkNew<vtkRenderer> ren;
//    ren->AddActor(c_actor);
////    ren->AddActor(g_actor);
//    ren->SetBackground(colors->GetColor3d("SlateGray").GetData());
//    vtkNew<vtkRenderWindow> renwin;
//    renwin->AddRenderer(ren);
//    renwin->SetSize(640, 480);
//    renwin->SetWindowName("DecimatePolyline");
//    vtkNew<vtkRenderWindowInteractor> iren;
//    iren->SetRenderWindow(renwin);
//    renwin->Render();
//    iren->Start();
//    #endif
//
//
//    //clean up memory
//    double area = 0;
//    for(Cell * c : Cells){
//      area += c->getArea();
//      // cout << *c << endl;
//      delete c;
//    }
//    cout << area;
//
//  } else {
//    std::cout << "Unkown file format (must be an unstructured grid)" << std::endl;
//  }

    Geommetry g("B_washer.vtk");

    g.debugDraw();

  return EXIT_SUCCESS;
}