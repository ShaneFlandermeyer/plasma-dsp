# List of header files
set(WAVEFORM_HEADERS
  consants.h
  linearfmwaveform.h
  pulsedwaveform.h
  squarewaveform.h
  waveform.h)
# Make headers visible to the entire project
set(WAVEFORM_HEADERS "${WAVEFORM_HEADERS}" PARENT_SCOPE)