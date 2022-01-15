# List of headers
list(APPEND
  PLASMA_HEADERS
  # barker-coded-waveform.h
  cfar1d.h
  cfar2d.h
  circ-shift.h
  constants.h
  detector.h
  fmcw-waveform.h
  linear-fm-waveform.h
  matrix-utils.h
  pcfm.h
  phase-code.h
  phase-coded-waveform.h
  pulsed-waveform.h
  range-doppler.h
  signal-processing.h
  spectrogram.h
  square-waveform.h
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
