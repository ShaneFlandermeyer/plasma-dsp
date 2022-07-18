# List of headers
list(APPEND
  PLASMA_HEADERS
  # cfar1d.h
  # cfar2d.h
  # constants.h
  # detector.h
  # fftshift.h
  file.h
  fmcw_waveform.h
  linear_fm_waveform.h
  pcfm.h
  phase_code.h
  phase_coded_waveform.h
  pulsed_waveform.h
  square_waveform.h
  waveform.h
  # window.h
)

# System-wide installation
install(FILES
  ${PLASMA_HEADERS}
  DESTINATION ${PLASMA_INCLUDE_DIR}
)
