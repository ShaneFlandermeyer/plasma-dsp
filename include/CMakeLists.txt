# List of header files
set(PLASMA_HEADERS
  constants.h
  linearfmwaveform.h
  pulsedwaveform.h
  spectrogram.h
  squarewaveform.h
  utils.h
  waveform.h)
# Make headers visible to the entire project
set(PLASMA_HEADERS "${PLASMA_HEADERS}" PARENT_SCOPE)