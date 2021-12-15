# Waveform lib source files
list(
  APPEND
  PLASMA_SOURCES
  barkercode.cc
  linearfmwaveform.cc
  phasecode.cc
  phasecodedwaveform.cc
  pulsedwaveform.cc
  squarewaveform.cc
  utils.cc
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
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PUBLIC $<INSTALL_INTERFACE:include>)
target_link_libraries(plasma-dsp Eigen3::Eigen)

# TODO: Make this work
install(TARGETS plasma-dsp
  DESTINATION lib)
# # TODO: Complete this
# install(TARGETS plasma-dsp
#     LIBRARY DESTINATION lib
# )

