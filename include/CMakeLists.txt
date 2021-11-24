# List of header files
set(WAVEFORM_HEADERS
  constants.h
  linearfmwaveform.h
  pulsedwaveform.h
  spectrogram.h
  squarewaveform.h
  utils.h
  waveform.h)
# Make headers visible to the entire project
set(WAVEFORM_HEADERS "${WAVEFORM_HEADERS}" PARENT_SCOPE)