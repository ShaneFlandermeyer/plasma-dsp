add_executable(
  waveform-test
  test_fmcw_waveform.cc
  test_linear_fm_waveform.cc
  test_pcfm_waveform.cc
  test_phase_coded_waveform.cc
  # test_pulse_doppler.cc
  test_square_waveform.cc
)

target_link_libraries(
  waveform-test
  gtest_main
  gmock
  plasma-dsp
)

# Matplot++ is handy for debugging. Link to it if the user wants it anyways
if(${Matplot++_FOUND})
  target_link_libraries(
    waveform-test
    Matplot++::matplot
  )
endif()

include(GoogleTest)
gtest_discover_tests(waveform-test)

