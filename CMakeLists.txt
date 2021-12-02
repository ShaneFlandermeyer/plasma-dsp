cmake_minimum_required(VERSION 3.16)
project(plasma-dsp VERSION 1.0 LANGUAGES CXX)

########################################################################
# Configure Compiler
########################################################################
set(CMAKE_CXX_STANDARD 20)
add_definitions(-DEIGEN_FFTW_DEFAULT)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

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
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(app)