#include "pulse_doppler.h"

#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <matplot/matplot.h>

class PulseDopplerTest : public testing::Test {
protected:
};

TEST_F(PulseDopplerTest, TestIntegerDelay) {
  // TODO: For some reason the solution to this test changes every run
  // Eigen::MatrixXd x = Eigen::MatrixXd::Ones(10,1);
  // size_t num_samps_delay = 10;
  // size_t nfft = 30;
  // double fs = 1e6;
  // double ts = 1 / fs;
  // double t = num_samps_delay * ts;
  // // Eigen::MatrixXd y = plasma::delay(x,t,nfft,fs);
  // plasma::delay(x,t,nfft,fs);
}