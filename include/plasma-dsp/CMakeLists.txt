# List of headers
list(APPEND
  PLASMA_HEADERS
  cfar1d.h
  cfar2d.h
  constants.h
  detector.h
  fmcw_waveform.h
  linear_fm_waveform.h
  matrix_utils.h
  pcfm.h
  phase_code.h
  phase_coded_waveform.h
  pulse_doppler.h
  pulsed_waveform.h
  range-doppler.h
  signal_processing.h
  spectrogram.h
  square_waveform.h
  waveform.h
  window.h
  vector_utils.h
)

configure_file(
  "${PROJECT_SOURCE_DIR}/include/plasma-dsp/eigen_config.h.in"
  "${PROJECT_BINARY_DIR}/include/plasma-dsp/eigen_config.h"
)

# System-wide installation
install(FILES
  ${PLASMA_HEADERS}
  DESTINATION ${PLASMA_INCLUDE_DIR}
)
