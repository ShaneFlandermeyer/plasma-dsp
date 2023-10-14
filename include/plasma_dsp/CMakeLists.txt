# List of headers
list(APPEND
  PLASMA_HEADERS
  # cfar1d.h
  cfar2d.h
  constants.h
  cpm.h
  detector.h
  fft.h
  file.h
  fmcw_waveform.h
  lfm.h
  optimization.h
  parc.h
  pcfm.h
  phase_code.h
  phase_coded_waveform.h
  pulsed_waveform.h
  square_waveform.h
  utils.h
  waveform.h
  window.h
)

# System-wide installation
install(FILES
  ${PLASMA_HEADERS}
  DESTINATION ${PLASMA_INCLUDE_DIR}
)
