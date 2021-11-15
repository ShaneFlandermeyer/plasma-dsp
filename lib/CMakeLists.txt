# Waveform lib source files
list(APPEND WAVEFORM_SOURCES
  SquareWaveform.cc
  LinearFMWaveform.cc)
set(WAVEFORM_SOURCES "${WAVEFORM_SOURCES}" PARENT_SCOPE)
# Create the waveform library
add_library(waveform SHARED ${WAVEFORM_SOURCES})
# Specify the library include dirs
target_include_directories(waveform
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>)