# Waveform lib source files
list(APPEND PLASMA_SOURCES
  linearfmwaveform.cc
  pulsedwaveform.cc
  squarewaveform.cc
  utils.cc
  window.cc)
set(PLASMA_SOURCES "${PLASMA_SOURCES}" PARENT_SCOPE)
# Create the waveform library
add_library(waveform SHARED ${PLASMA_SOURCES})
# Specify the library include dirs
target_include_directories(waveform
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>)