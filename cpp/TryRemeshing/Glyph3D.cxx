/**
 * remeshing
 */

#include "remesh.h"

using namespace std;

int main(int argc, char *argv[]) {

    std::string inputFilename = argv[1];
    remesh::generateBgMesh(inputFilename);

    return EXIT_SUCCESS;
}