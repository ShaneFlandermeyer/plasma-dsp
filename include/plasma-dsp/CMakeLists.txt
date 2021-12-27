# List of headers
list(APPEND
  PLASMA_HEADERS
  barkercode.h
  constants.h
  fmcwwaveform.h
  linearfmwaveform.h
  pcfm.h
  phasecode.h
  phasecodedwaveform.h
  pulsedwaveform.h
  rangedoppler.h
  signal-processing.h
  spectrogram.h
  squarewaveform.h
  waveform.h
  window.h
  vector-utils.h
)

# System-wide installation
install(FILES
  ${PLASMA_HEADERS}
  DESTINATION ${PLASMA_INCLUDE_DIR}
)