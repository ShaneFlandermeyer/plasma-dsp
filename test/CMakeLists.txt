
add_executable(
  waveform-test
  # test_fmcw_waveform.cc
  test_linear_fm_waveform.cc
  # test_pcfm_waveform.cc
  # test_phase_coded_waveform.cc
  test_square_waveform.cc
)

target_link_libraries(
  waveform-test
  ${CONAN_LIBS_GTEST}
  plasma_dsp
)

include(GoogleTest)
gtest_discover_tests(waveform-test)

