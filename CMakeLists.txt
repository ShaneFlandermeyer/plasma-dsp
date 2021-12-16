cmake_minimum_required(VERSION 3.16)
project(
  plasma-dsp
  VERSION 1.0
  LANGUAGES CXX)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(
    FATAL_ERROR
      "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles."
  )
endif()

# ##############################################################################
# Configure Compiler
# ##############################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(EIGEN_FFTW_DEFAULT)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
# Include custom cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(BuildType)

########################################################################
# Install directories
########################################################################

# CMake module base path
if (NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib/cmake)
endif()

set(PLASMA_INCLUDE_DIR include/plasma-dsp/${CMAKE_BUILD_TYPE})
set(PLASMA_LIB_DIR     lib)
set(PLASMA_CMAKE_DIR   ${CMAKE_MODULES_DIR}/plasma-dsp)
########################################################################
# Find build dependencies
########################################################################
find_package(Matplot++ REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

########################################################################
# TODO: Create uninstall target
########################################################################

# ##############################################################################
# Add subdirectories
# ##############################################################################
add_subdirectory(include/plasma-dsp)
add_subdirectory(lib)
add_subdirectory(app)

########################################################################
# Install cmake search helper for this library
########################################################################

install(FILES cmake/plasma-dsp-config.cmake
    DESTINATION ${PLASMA_CMAKE_DIR}
)
