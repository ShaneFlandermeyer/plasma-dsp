# Waveform lib source files
list(
  APPEND
  PLASMA_SOURCES
  cfar1d.cc
  cfar2d.cc
  fft.cc
  fmcw_waveform.cc
  linear_fm_waveform.cc
  pcfm.cc
  phase_code.cc
  phase_coded_waveform.cc
  # processing.cc
  pulse_doppler.cc
  pulsed_waveform.cc
  square_waveform.cc
  waveform.cc
  window.cc)

set(PLASMA_SOURCES "${PLASMA_SOURCES}" PARENT_SCOPE)
# Create the waveform library
add_library(plasma_dsp SHARED ${PLASMA_SOURCES})
# Specify the library include dirs
target_include_directories(
  plasma_dsp PRIVATE
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/plasma_dsp>
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include/plasma_dsp>
  PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(plasma_dsp PUBLIC Eigen3::Eigen fftw3 fftw3f fftw3_threads fftw3f_threads)

if(OpenMP_CXX_FOUND)
  target_compile_definitions(plasma_dsp PUBLIC USE_OPENMP)
  target_link_libraries(plasma_dsp PUBLIC OpenMP::OpenMP_CXX)
endif()

# Install the shared library file
install(TARGETS plasma_dsp
  EXPORT plasma_dsp
  DESTINATION ${PLASMA_LIB_DIR})
# Install the cmake config file
install(EXPORT plasma_dsp
  DESTINATION ${PLASMA_CMAKE_DIR})

