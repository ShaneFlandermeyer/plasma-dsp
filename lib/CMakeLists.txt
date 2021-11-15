# Waveform lib source files
list(APPEND WAVEFORM_SOURCES
  LinearFMWaveform.cc)
# Prepend full path to the above sources
list(TRANSFORM WAVEFORM_SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
set(WAVEFORM_SOURCES "${WAVEFORM_SOURCES}" PARENT_SCOPE)
# Create the waveform library
add_library(waveform SHARED ${WAVEFORM_SOURCES})
# Specify the library include dirs
target_include_directories(waveform
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>)