/**
 * remeshing
 */

#include "remesh.h"

using namespace std;

int main(int argc, char *argv[]) {

    std::string inputFilename = argv[1];
    remesh::generateBgMesh(inputFilename);
    remesh::runGMSH();
//    remesh::cleanUp();
    return EXIT_SUCCESS;
}