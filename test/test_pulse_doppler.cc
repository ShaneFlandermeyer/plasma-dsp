#include "pulse_doppler.h"

#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <matplot/matplot.h>

class PulseDopplerTest : public testing::Test {
protected:
};

TEST_F(PulseDopplerTest, Delay) {
  Eigen::ArrayXd x = Eigen::ArrayXd::Ones(10);
  size_t num_samps_delay = 10;
  size_t nfft = 10;
  double fs = 1e6;
  double t = 10 / fs;
  auto y = plasma::delay(x,t,nfft+num_samps_delay,fs);
}