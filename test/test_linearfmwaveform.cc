#include <gtest/gtest.h>
#include "linearfmwaveform.h"

using namespace plasma;
TEST(LinearFMWaveformTest,HandlesWaveformGeneration) {
  auto bandwidth = 10e6;
  auto pulse_width = 100e-6;
  auto prf = 10e3;
  auto samprate = 20e6;
  LinearFMWaveform lfm(bandwidth,pulse_width,prf,samprate);

  auto actual = lfm.waveform();

  // EXPECT_EQ(waveform.sample(0.0), 0.0);
  // EXPECT_EQ(waveform.sample(0.5), 0.5);
  // EXPECT_EQ(waveform.sample(1.0), 1.0);
}