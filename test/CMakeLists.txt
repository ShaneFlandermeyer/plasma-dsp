
add_executable(
  waveform-test
  test_fmcw_waveform.cc
  test_linear_fm_waveform.cc
  test_pcfm_waveform.cc
  test_phase_coded_waveform.cc
  test_square_waveform.cc
)

target_link_libraries(
  waveform-test
  PRIVATE
  ${GTest_LIBRARIES}
  plasma_dsp
)

target_include_directories(waveform-test 
  PRIVATE ${GTest_INCLUDE_DIRS})

include(GoogleTest)
gtest_discover_tests(waveform-test)

