add_executable(
  waveform-test
  test-fmcw-waveform.cc
  test-linear-fm-waveform.cc
  test-pcfm-waveform.cc
  test-phase-coded-waveform.cc
  test-square-waveform.cc
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

