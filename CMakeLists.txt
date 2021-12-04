cmake_minimum_required(VERSION 3.16)
project(plasma-dsp 
        VERSION 1.0 
        LANGUAGES CXX)
  
# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()


########################################################################
# Configure Compiler
########################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(EIGEN_FFTW_DEFAULT)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
# Include custom cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(BuildType)


########################################################################
# External packages
########################################################################
find_package(Matplot++ REQUIRED)
if(Matplot++_FOUND)
  message(STATUS "Matplot++ found")
endif(Matplot++_FOUND)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
if (Eigen3_FOUND)
  message(STATUS "Eigen3 found")
endif(Eigen3_FOUND)


########################################################################
# Add subdirectories
########################################################################
add_subdirectory(lib)
add_subdirectory(app)