cmake_minimum_required(VERSION 3.16)
project(WAVEFORM VERSION 1.0 LANGUAGES CXX)

########################################################################
# Configure Compiler
########################################################################
set(CMAKE_CXX_STANDARD 20)

########################################################################
# External packages
########################################################################
find_package(Matplot++ REQUIRED QUIET)
if(Matplot++_FOUND)
  message(STATUS "Matplot++ found")
endif(Matplot++_FOUND)


########################################################################
# Add subdirectories
########################################################################
add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(app)