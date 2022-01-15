#include "pcfm.h"
#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <matplot/matplot.h>
#include <unsupported/Eigen/FFT>

class PCFMWaveformTest : public testing::Test {
protected:
};

TEST_F(PCFMWaveformTest, RandomSinglePRF) {
  // Choose a random bandwidth, pulse width, and PRF, then use it to instantiate
  // the waveform object
  std::default_random_engine engine(std::random_device{}());
  std::uniform_int_distribution uniform(1, 10);
  double prf = uniform(engine) * 1e3;
  // size_t num_chips = uniform(engine);
  size_t num_chips = 10;
  double chip_width = uniform(engine) * 1e-6;
  double samp_rate = 1e6;

  // Expected result
  // Generate the oversampled phase change vector
  // size_t num_samps_chip = round(chip_width * samp_rate);
  size_t num_samps_chip = 3;
  size_t num_samps_code = num_samps_chip * num_chips;
  std::uniform_real_distribution<> code_values(-M_PI, M_PI);
  Eigen::VectorXd code(num_chips);
  Eigen::VectorXd alpha = Eigen::VectorXd::Zero(num_chips);
  Eigen::VectorXd impulse_train = Eigen::VectorXd::Zero(num_samps_code);
  for (size_t i = 0; i < num_chips; i++) {
    code(i) = code_values(engine);
    if (i == 0)
      // impulse_train(i * num_samps_chip) = code(i);
      impulse_train(i * num_samps_chip) = 1;
    else
      // impulse_train(i * num_samps_chip) = code(i) - code(i - 1);
      impulse_train(i * num_samps_chip) = 1;
  }
  // Create the shaping filter and apply it to the impulse train
  Eigen::VectorXd filter(num_samps_code);
  filter << Eigen::VectorXd::Ones(num_samps_chip) / num_samps_chip,
      Eigen::VectorXd::Zero(num_samps_code - num_samps_chip);
  
  Eigen::FFT<double> fft;
  Eigen::VectorXcd filter_fft, impulse_train_fft;
  filter_fft = fft.fwd(filter);
  impulse_train_fft = fft.fwd(impulse_train);
  Eigen::VectorXd chi = fft.inv(filter_fft.cwiseProduct(impulse_train_fft).eval());

  // Cumsum back to phase
  Eigen::ArrayXd phase(num_samps_code);
  std::partial_sum(chi.begin(),chi.end(),phase.begin());

  // TODO: Take the PRF into account and compare to the actual result

  // TODO: Remove this after the test is implemented
  ASSERT_TRUE(false);
}