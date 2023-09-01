cmake_minimum_required(VERSION 3.26)
project(GMSHEx)


find_package(nlohmann_json 3.2.0 REQUIRED)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

include(FetchContent)
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_executable(GMSHEx main.cpp)
target_link_libraries(GMSHEx PRIVATE nlohmann_json::nlohmann_json gmsh argparse)
