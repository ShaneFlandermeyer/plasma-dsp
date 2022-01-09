# List of headers
list(APPEND
  PLASMA_HEADERS
  barkercode.h
  cfar1d.h
  cfar2d.h
  circ_shift.h
  constants.h
  detector.h
  fmcwwaveform.h
  linearfmwaveform.h
  matrix-utils.h
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

configure_file(
  "${PROJECT_SOURCE_DIR}/include/plasma-dsp/eigen-config.h.in"
  "${PROJECT_BINARY_DIR}/include/plasma-dsp/eigen-config.h"
)

# System-wide installation
install(FILES
  ${PLASMA_HEADERS}
  DESTINATION ${PLASMA_INCLUDE_DIR}
)
