# Waveform lib source files
list(
  APPEND
  PLASMA_SOURCES
  # barker_coded_waveform.cc
  cfar1d.cc
  cfar2d.cc
  fmcw_waveform.cc
  linear_fm_waveform.cc
  pcfm.cc
  phase_code.cc
  phase_coded_waveform.cc
  pulse_doppler.cc
  pulsed_waveform.cc
  square_waveform.cc
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
  PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include/plasma-dsp>
  PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(plasma-dsp PUBLIC Eigen3::Eigen fftw3)

if(OpenMP_CXX_FOUND)
  target_compile_definitions(plasma-dsp PUBLIC USE_OPENMP)
  target_link_libraries(plasma-dsp PUBLIC OpenMP::OpenMP_CXX)
endif()

# Install the shared library file
install(TARGETS plasma-dsp
  EXPORT plasma-dsp
  DESTINATION ${PLASMA_LIB_DIR})
# Install the cmake config file
install(EXPORT plasma-dsp
  DESTINATION ${PLASMA_CMAKE_DIR})

