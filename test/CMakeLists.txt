add_executable(
  waveform-test
  test_fmcw_waveform.cc
  test_linear_fm_waveform.cc
  # test_pcfm_waveform.cc
  test_phase_coded_waveform.cc
  # test_pulse_doppler.cc
  test_square_waveform.cc
)

# add_executable(
#   fft-test
#   test_fft.cc

# )

target_link_libraries(
  waveform-test
  gtest_main
  gmock
  plasma_dsp
)

# target_include_directories(waveform-test
#   PUBLIC
#   ${CONAN_INCLUDE_DIRS}
# )


# target_link_libraries(fft-test
#   gtest_main
#   gmock
#   plasma_dsp
# )

include(GoogleTest)
gtest_discover_tests(waveform-test)

