# Waveform lib source files
list(
  APPEND
  PLASMA_SOURCES
  barkercode.cc
  fmcwwaveform.cc
  linearfmwaveform.cc
  pcfm.cc
  phasecode.cc
  phasecodedwaveform.cc
  pulsedwaveform.cc
  rangedoppler.cc
  squarewaveform.cc
  waveform.cc
  window.cc)
set(PLASMA_SOURCES
    "${PLASMA_SOURCES}"
    PARENT_SCOPE)
# Create the waveform library
add_library(plasma-dsp SHARED ${PLASMA_SOURCES})
# Specify the library include dirs
target_include_directories(
  plasma-dsp PRIVATE
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/plasma-dsp>
  PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(plasma-dsp Eigen3::Eigen fftw3)

# Install the shared library file
install(TARGETS plasma-dsp
  EXPORT plasma-dsp
  DESTINATION ${PLASMA_LIB_DIR})
# Install the cmake config file
install(EXPORT plasma-dsp
  DESTINATION ${PLASMA_CMAKE_DIR})

