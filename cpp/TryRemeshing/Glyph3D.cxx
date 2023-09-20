/**
 * remeshing
 */

#define B_PT(v) {v[0], v[1], v[3]}



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
#include <iostream>
#include <fstream>
#include <vector>

std::ostream &operator<<(std::ostream &s, Cell cell) {
    return s << cell.toString();
}


using namespace std;

int main(int argc, char *argv[]) {

    // Ensure a filename was specified.
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " InputFilename e.g. blow.vtk" << endl;
        return EXIT_FAILURE;
    }

    std::string inputFilename = argv[1];

    //init vtk generic data object
    vtkNew<vtkGenericDataObjectReader> reader;
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    if (reader->IsFileUnstructuredGrid()) {

        // create t file
        ofstream POS("post.pos");
        std::cout << "Reading file" << std::endl;
        auto output = reader->GetUnstructuredGridOutput();
        vtkPoints *PointArray = output->GetPoints();
        // get data array
        vtkDoubleArray *D_array = vtkDoubleArray::SafeDownCast(output->GetPointData()->GetArray("10.000GHz_fone_imag"));

        const double maxNorm =  D_array->GetMaxNorm();
        const double minNorm = 0.0;
        const long double minMeshSize = 0.5E-7f;
        const long double maxMeshSize = 10E-7f;
        const long double m = (maxMeshSize - minMeshSize)/(minNorm-maxNorm);
        POS << "View \"background mesh\" {" << endl;

        // loop through each cell
        auto num = output->GetNumberOfCells();
        for(vtkIdType i = 0; i < num; i++){

            vtkIdType npts;
            vtkIdType const * pts;
            // Then use cell ids to get points
            output->GetCellPoints(i,npts,pts);
            POS << "ST(";
            for (vtkIdType k = 0; k < npts-1; k++){
                double * pt = PointArray->GetPoint(pts[k]);
                Point p = B_PT(pt);
                POS << p.x << "," << p.y << "," << p.z << ',';
            }
            double * pt = PointArray->GetPoint(pts[npts-1]);
            Point p = B_PT(pt);
            POS << p.x << "," << p.y << "," << p.z;

            double p1 = ((Point) B_PT(D_array->GetTuple3(pts[0]))).norm();
            double p2 = ((Point) B_PT(D_array->GetTuple3(pts[1]))).norm();
            double p3 = ((Point) B_PT(D_array->GetTuple3(pts[2]))).norm();


//            cout << 1/(p1*1E8) << endl;
            POS << "){" << 1/(p1*1E8) << "," << 1/(p2*1E8) << "," << 1/(p3*1E8) << "};" << endl;
        }



        POS << "};";
        POS.close();

    } else {
        std::cout << "Unkown file format (must be an unstructured grid)" << std::endl;
    }

    return EXIT_SUCCESS;
}