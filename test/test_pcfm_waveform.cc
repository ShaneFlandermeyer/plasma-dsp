#include "matrix_utils.h"
#include "pcfm.h"
#include <random>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <unsupported/Eigen/FFT>

class PCFMWaveformTest : public testing::Test {
protected:
};

TEST_F(PCFMWaveformTest, RandomSinglePRF) {
  // Choose a random bandwidth, pulse width, and PRF, then use it to instantiate
  // the waveform object
  std::default_random_engine engine(std::random_device{}());
  double prf = 1e3;
  size_t num_chips = 100;
  double samp_rate = 1e6;

  // Expected result
  // Generate the oversampled phase change vector
  size_t num_samps_chip = 3;
  size_t num_samps_code = num_samps_chip * num_chips;
  size_t num_samps_pulse = round(samp_rate / prf);
  std::uniform_real_distribution<> code_values(-M_PI, M_PI);
  Eigen::VectorXd code(num_chips);
  Eigen::ArrayXd difference(num_chips);
  Eigen::VectorXd oversampled_diff = Eigen::VectorXd::Zero(num_samps_code);
  for (size_t i = 0; i < num_chips; i++) {
    code(i) = code_values(engine);
    if (i == 0) {
      difference(i) = code(i);
      oversampled_diff(i * num_samps_chip) = difference(i);
    } else {
      difference(i) = code(i) - code(i - 1);
      // Wrap to [-pi, pi]
      if (std::abs(difference(i)) > M_PI)
        difference(i) -= 2 * M_PI * difference.sign()(i);
      oversampled_diff(i * num_samps_chip) = difference(i);
    }
  }
  
  // Create the shaping filter (zero padded to the size of the oversampled
  // difference vector)
  Eigen::VectorXd filter = Eigen::VectorXd::Zero(num_samps_code);
  filter.head(num_samps_chip) =
      Eigen::VectorXd::Ones(num_samps_chip) * num_samps_chip;

  // Apply the shaping filter in frequency
  Eigen::FFT<double> fft;
  Eigen::VectorXcd filter_fft, impulse_train_fft;
  filter_fft = fft.fwd(filter);
  impulse_train_fft = fft.fwd(oversampled_diff);
  Eigen::VectorXd frequency =
      fft.inv(filter_fft.cwiseProduct(impulse_train_fft).eval());

  // Integrate frequency back to phase
  Eigen::ArrayXd phase(num_samps_code);
  std::partial_sum(frequency.begin(), frequency.end(), phase.begin());

  // Zero pad the waveform to the size of the PRF
  Eigen::ArrayXcd expected = plasma::vcat(
      exp(plasma::Im * phase).eval(),
      Eigen::ArrayXcd::Zero(num_samps_pulse - num_samps_code).eval());

  // Generate the waveform from the obnect
  plasma::PCFMWaveform waveform(code, filter.head(num_samps_chip), samp_rate,
                                prf);
  Eigen::ArrayXcd actual = waveform.step();

  // Check the pulse length
  ASSERT_EQ(actual.size(), expected.size());

  // Check that the values are the same
  EXPECT_THAT(actual.real(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.real()));
  EXPECT_THAT(actual.imag(),
              testing::Pointwise(testing::FloatNear(1e-10), expected.imag()));
}