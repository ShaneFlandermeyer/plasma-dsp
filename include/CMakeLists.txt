# List of header files
set(WAVEFORM_HEADERS
  consants.h
  waveform.h
  pulsedwaveform.h
  squarewaveform.h
  linearfmwaveform.h)
# Make headers visible to the entire project
set(WAVEFORM_HEADERS "${WAVEFORM_HEADERS}" PARENT_SCOPE)