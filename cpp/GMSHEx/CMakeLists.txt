cmake_minimum_required(VERSION 3.26)
project(GMSHEx)


find_package(nlohmann_json 3.2.0 REQUIRED)
set(CMAKE_CXX_STANDARD 17)


add_executable(GMSHEx main.cpp)
target_link_libraries(GMSHEx PRIVATE nlohmann_json::nlohmann_json gmsh)
