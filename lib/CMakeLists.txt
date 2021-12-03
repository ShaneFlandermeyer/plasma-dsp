# Waveform lib source files
list(APPEND PLASMA_SOURCES
  linearfmwaveform.cc
  phasecode.cc
  phasecodedwaveform.cc
  pulsedwaveform.cc
  squarewaveform.cc
  utils.cc
  window.cc)
set(PLASMA_SOURCES "${PLASMA_SOURCES}" PARENT_SCOPE)
# Create the waveform library
add_library(plasma-dsp SHARED ${PLASMA_SOURCES})
target_link_libraries(plasma-dsp Eigen3::Eigen)
# Specify the library include dirs
target_include_directories(plasma-dsp
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>)