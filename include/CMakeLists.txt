# List of header files
set(WAVEFORM_HEADERS
  consants.h
  Waveform.h
  PulsedWaveform.h
  LinearFMWaveform.h)
# Make headers visible to the entire project
set(WAVEFORM_HEADERS "${WAVEFORM_HEADERS}" PARENT_SCOPE)