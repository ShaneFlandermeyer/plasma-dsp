# Waveform lib source files
list(
  APPEND
  PLASMA_SOURCES
  # cfar1d.cc
  # cfar2d.cc
  fft.cc
  fmcw_waveform.cc
  linear_fm_waveform.cc
  optimization.cc
  pcfm.cc
  phase_code.cc
  phase_coded_waveform.cc
  pulsed_waveform.cc
  square_waveform.cc
  waveform.cc
  window.cc
)

# Create the waveform library
add_library(plasma_dsp ${PLASMA_SOURCES})
# Specify the library include dirs
target_include_directories(
  plasma_dsp 
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/plasma_dsp>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include/plasma_dsp>
  PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(plasma_dsp 
  PUBLIC ArrayFire::af
  PRIVATE ${CONAN_LIBS_FFTW})

# Install the shared library file
install(TARGETS plasma_dsp
  EXPORT plasma_dsp
  DESTINATION ${PLASMA_LIB_DIR})
# Install .cmake files
install(EXPORT plasma_dsp
  DESTINATION ${PLASMA_CMAKE_DIR})
# Install shared dependency libraries
# install(DIRECTORY ${CONAN_LIB_DIRS}/
#   DESTINATION ${PLASMA_LIB_DIR})