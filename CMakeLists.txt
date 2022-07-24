cmake_minimum_required(VERSION 3.16)
project(
  plasma_dsp
  VERSION 0.1
  LANGUAGES CXX
)

# ##############################################################################
# Build options
# ##############################################################################
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# ##############################################################################
# Configure Compiler
# ##############################################################################
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Include custom cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

########################################################################
# Install directories
########################################################################
# CMake module base path
if (NOT CMAKE_MODULES_DIR)
  set(CMAKE_MODULES_DIR lib/cmake)
endif()

set(PLASMA_INCLUDE_DIR include/${CMAKE_PROJECT_NAME})
set(PLASMA_LIB_DIR     lib)
set(PLASMA_CMAKE_DIR   ${CMAKE_MODULES_DIR}/plasma_dsp)
set(PLASMA_EXAMPLE_DIR bin)

########################################################################
# Find build dependencies
######################################################################
find_package(ArrayFire REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
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

# ##############################################################################
# Add subdirectories
# ##############################################################################
add_subdirectory(include/plasma_dsp)
add_subdirectory(lib)
add_subdirectory(examples)

enable_testing()
add_subdirectory(test)

########################################################################
# Install cmake search helper for this library
########################################################################
install(FILES cmake/plasma_dsp-config.cmake
    DESTINATION ${PLASMA_CMAKE_DIR}
)
