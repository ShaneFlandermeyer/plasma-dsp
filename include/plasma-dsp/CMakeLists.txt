# List of headers
list(APPEND
  PLASMA_HEADERS
  barkercode.h
  constants.h
  linearfmwaveform.h
  phasecode.h
  phasecodedwaveform.h
  pulsedwaveform.h
  spectrogram.h
  squarewaveform.h
  utils.h
  waveform.h
  window.h
)

# System-wide installation
install(FILES
  ${PLASMA_HEADERS}
  DESTINATION include/plasma-dsp
)