add_executable(
  waveformTest
  test_squarewaveform.cc
)

target_link_libraries(
  waveformTest
  gtest_main
  gmock
  plasma-dsp
)

include(GoogleTest)
gtest_discover_tests(waveformTest)

