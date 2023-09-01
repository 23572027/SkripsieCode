

#include <gmsh.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

int main(int argc, char** argv) {


    // find file
    ifstream inputFile("washer.geo");
    // Check if the input file is open
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    // Open the output file for writing
    std::ofstream outputFile("test.geo");

    // Check if the output file is open
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }
    // Read and process each line in the input file
    std::string line;
    while (std::getline(inputFile, line)) {
        // Check if the line contains "physical" or "volume"
        if (line.find("Physical") == std::string::npos && line.find("Volume") == std::string::npos && line.find("Save") == string::npos) {
            // If the line does not contain these words, write it to the output file
            outputFile << line << std::endl;
        }
        if (line.find("Plane Surface") != std::string::npos) {
            // Extract the "somenumber" from the line
            size_t pos1 = line.find('(');
            size_t pos2 = line.find(')');

            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                std::string number = line.substr(pos1 + 1, pos2 - pos1 - 1);

                // Create the new line in the desired format and write it to the output file
                outputFile << "Physical Surface(\"Fieldplane"<< stoi(number) - 1 << "\") = {" << number << "};" << std::endl;
            }
        }
    }
    outputFile << "Save \"testMesh.msh\";" << endl;
    // Close both input and output files
    inputFile.close();
    outputFile.close();


    return 1;
}
