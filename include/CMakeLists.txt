# List of header files
set(WAVEFORM_HEADERS
  Waveform.h
  PulsedWaveform.h
  LinearFMWaveform.h)
# Make headers visible to the entire project
set(WAVEFORM_HEADERS "${WAVEFORM_HEADERS}" PARENT_SCOPE)