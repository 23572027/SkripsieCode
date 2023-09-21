cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(Glyph3D)

find_package(VTK COMPONENTS 
  CommonCore
  CommonDataModel
  IOLegacy
  CommonColor
  FiltersCore
  FiltersSources
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  RenderingLabel
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Glyph3D: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
add_executable(Glyph3D MACOSX_BUNDLE Glyph3D.cxx
        remesh.h
        Point.cpp)
  target_link_libraries(Glyph3D PRIVATE ${VTK_LIBRARIES}
)
# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS Glyph3D
  MODULES ${VTK_LIBRARIES}
)