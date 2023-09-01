#define debug

#include <gmsh.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <argparse/argparse.hpp>
#include <cstdlib>
#include <regex>

using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv) {

    argparse::ArgumentParser program("NosieEx");
    program.add_argument("Geometry File")
    .required()
    .help("The file path to you .geo file in the directory inductEx was run");

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto fileName = program.get("Geometry File");
    string Name = fileName.substr(0,fileName.length() - 4);


    // find file
    ifstream inputFile(fileName);
    // Check if the input file is open
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    // Open the output file for writing
    std::ofstream outputFile(Name+"FIELD.geo");

    // Check if the output file is open
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }
    // Read and process each line in the input file
    int FieldCount = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        // Check if the line contains "physical" or "volume"
        if (line.find("Physical") == std::string::npos && line.find("Volume") == std::string::npos && line.find("Save") == string::npos) {
            // If the line does not contain these words, write it to the output file
            outputFile << line << std::endl;
        }
        if (line.find("Plane Surface") != std::string::npos) {
            // Extract the "somenumber" from the line
            FieldCount++;
            size_t pos1 = line.find('(');
            size_t pos2 = line.find(')');

            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                std::string number = line.substr(pos1 + 1, pos2 - pos1 - 1);

                // Create the new line in the desired format and write it to the output file
                outputFile << "Physical Surface(\"Fieldplane"<< stoi(number) - 1 << "\") = {" << number << "};" << std::endl;
            }
        }
    }
    outputFile << "Save \""<< Name << "FIELD.msh" <<"\";" << endl;
    // Close both input and output files
    inputFile.close();
    outputFile.close();


#ifndef debug
    // run gmsh
    cout << "Running gmsh on " << Name+"FIELD.geo -0 -v 1" << endl;
    string run_gmsh = "gmsh "+Name+"FIELD.geo -0 -v 1";
    if(system(run_gmsh.c_str())){
        cout << "An error occurred runnign gmsh" << endl;
        return 1;
    }
#endif


    cout << "Done!" <<  endl << "Writing changes to setting.json" << endl;
#ifdef debug
    std::ifstream f("test.json");
    json curr = json::parse(f);
#else
    ifstream f("settings_"+Name+".json");
    json curr = json::parse(f);
#endif
    f.close();

    // add mesh entities
    json adjusted = curr;
    for (int i = 1; i < FieldCount; i++){
        adjusted["MESHES"]["IXMeshField0"]["ENTITIES"].push_back("FieldPlane"+to_string(i));
        adjusted["OUTPUT"]["PLOT"]["B"]["ENTITIES"].push_back("IXMeshField0::FieldPlane" + to_string(i));
    }

// write adjusted file to new json file
#ifdef debug
//    cout<<regex_replace(adjusted.dump(4),regex(R"(PLOT\d+)"),"PLOT");
    ofstream newJson("debug.json");
#else
    ofstream newJson("settings_"+Name+".json");
#endif
    newJson << regex_replace(adjusted.dump(4),regex(R"(PLOT\d+)"),"PLOT");

    newJson.close();

    cout << "Running tth" << endl;

#ifdef debug
    system("tth debug.json");
#else
    system("tth "+"settings_"+Name+".json");
#endif


    return 0;
}
