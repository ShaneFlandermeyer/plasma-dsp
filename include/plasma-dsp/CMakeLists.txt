# List of headers
list(APPEND
  PLASMA_HEADERS
  barkercode.h
  cfar.h
  circ_shift.h
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

# FIXME: This may not work properly for the system-wide installation
configure_file(
  "${PROJECT_SOURCE_DIR}/include/plasma-dsp/config.h.in"
  "${PROJECT_BINARY_DIR}/include/plasma-dsp/config.h"
)

# System-wide installation
install(FILES
  ${PLASMA_HEADERS}
  DESTINATION ${PLASMA_INCLUDE_DIR}
)
