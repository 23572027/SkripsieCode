/*
 * Author: Paul Rossouw
 * Date Created: 02/09/2023
 * Class description: Higher level abstraction to simplify the interface with the
 * cell class in geom.h
 */

#ifndef GLYPH3D_GEOMMETRY_H
#define GLYPH3D_GEOMMETRY_H

#define B_PT(v) {v[0], v[1], v[3]}
// Temporary current data for loop
#define curr 0.79190019755 Amps


// general includes
#include "geom.hh"
#include <cmath>
#include <string>
#include <vector>
//

// vtk imports
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
#include <vtkGenericDataObjectReader.h>
#include <vtkStructuredGrid.h>
//


using namespace std;

class Geommetry {
    public:
        /**
         * Class constructor
         * @param fileName: String, the file path to the desired vtk file.
         */

        Geommetry(string fileName, bool init_now = true, bool run_now = true);

        ~Geommetry();

        /**
         * Get file name of vtk file
         * @warning: Do not modify return value
         * @return return file name
         */
        [[nodiscard]] const string &getFileName() const;

        /**
         * Set file path
         * @param name : Path to vtk file.
         */
        void setFileName(const string &name);

        /**
         * Get Cell objects
         * @warning: Do not modify return value
         * @return Cell object VECTOR
         */

        [[nodiscard]] const vector<Cell *> &getCells() const;

        void init();

        /**
         * Runs the algorithm
         * @warning: Init must be run before this can be run
         */
        void run();

        void debugDraw();

    private:
        void _init();
        string fileName;
        vector<Cell*> Cells;


        vtkNew<vtkGenericDataObjectReader> reader;
        vtkUnstructuredGrid *output;
        bool isInit = false;

        vtkPoints *PointArray;
        vtkDoubleArray *D_array;
        vtkIdType num;
        bool hasRun = false;
};


#endif //GLYPH3D_GEOMMETRY_H