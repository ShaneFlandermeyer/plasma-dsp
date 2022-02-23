cmake_minimum_required(VERSION 3.16)
project(
  plasma-dsp
  VERSION 0.1
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
# Build options
# ##############################################################################
option(ENABLE_OPENMP "ENABLE_OPENMP" ON)
option(ENABLE_MATPLOT "ENABLE_MATPLOT" ON)

# ##############################################################################
# Configure Compiler
# ##############################################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "/utf-8")
add_compile_definitions(EIGEN_FFTW_DEFAULT)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
# Include custom cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(BuildType)
include(CPM)
include(FetchContent)

########################################################################
# Install directories
########################################################################
# CMake module base path
if (NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib/cmake)
endif()

set(PLASMA_INCLUDE_DIR include/${CMAKE_PROJECT_NAME})
set(PLASMA_LIB_DIR     lib)
set(PLASMA_CMAKE_DIR   ${CMAKE_MODULES_DIR}/plasma-dsp)

########################################################################
# Find build dependencies
########################################################################
if (${ENABLE_MATPLOT})
  find_package(Matplot++)
  if (TARGET Matplot++::matplot)
    message(STATUS "Using matplot++ from system")
  else()
    message(STATUS "Building Matplot++ from submodule...")
    FetchContent_Declare(Matplot++
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
    GIT_TAG origin/master)
    set(CMAKE_CXX_STANDARD 17)
    FetchContent_MakeAvailable(Matplot++)
    set(CMAKE_CXX_STANDARD 20)
  endif()
endif()

find_package(Eigen3 3.4 NO_MODULE)
if (TARGET Eigen3::Eigen)
  message(STATUS "Using Eigen v3.4 from system")
else()
  message(STATUS "Building Eigen v3.4 from submodule...")
  CPMAddPackage(
  NAME Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG origin/3.4
  # Eigen's CMakelists are not intended for library use
  DOWNLOAD_ONLY YES 
  )

  if(Eigen_ADDED)
    add_library(Eigen3::Eigen INTERFACE IMPORTED)
    target_include_directories(Eigen3::Eigen INTERFACE ${Eigen_SOURCE_DIR})
  endif()

endif()



if (${ENABLE_OPENMP})
  find_package(OpenMP REQUIRED)
endif()

########################################################################
# Create uninstall target
########################################################################
configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
@ONLY)

add_custom_target(uninstall
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    )

########################################################################
# Set up Google Test
########################################################################
# Declare gtest dependency and download it from git
# include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
) 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# ##############################################################################
# Add subdirectories
# ##############################################################################
add_subdirectory(include/plasma-dsp)
add_subdirectory(lib)
add_subdirectory(test)
if (${ENABLE_MATPLOT})
  add_subdirectory(examples)
else()
  message(STATUS "Matplot++ support disabled, example folder will not be built.")
endif()

########################################################################
# Install cmake search helper for this library
########################################################################
install(FILES cmake/plasma-dsp-config.cmake
    DESTINATION ${PLASMA_CMAKE_DIR}
)
