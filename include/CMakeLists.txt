# List of header files
set(WAVEFORM_HEADERS
  Waveform.h
  LinearFMWaveform.h)
# Prepend the include directory path to WAVEFORM_HEADERS 
list(TRANSFORM WAVEFORM_HEADERS
  PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
# Make headers visible to the entire project
set(WAVEFORM_HEADERS "${WAVEFORM_HEADERS}" PARENT_SCOPE)