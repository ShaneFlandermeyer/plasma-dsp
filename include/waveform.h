#ifndef EB650315_AD21_460C_9B80_13EA6DC8F155
#define EB650315_AD21_460C_9B80_13EA6DC8F155

#include <complex>
#include <vector>

#include "constants.h"

/**
 * @brief Abstract base class for waveform objects.
 *
 */
class Waveform {
 protected:
  // Waveform sample rate
  double d_sampRate;

 public:
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return std::vector<std::complex<double>>
   */
  // TODO: Rename this (Candidates: pulse)
  virtual std::vector<std::complex<double>> sample() = 0;
  /**
   * @brief Generate the full PRF schedule defined by the waveform object.
   *
   * @return std::vector<std::complex<double>>
   */
  // TODO: Rename this
  virtual std::vector<std::complex<double>> step() = 0;
  // Getters and setters
  auto sampRate() const { return d_sampRate; }
  auto sampRate(double sampRate) { d_sampRate = sampRate; }
};

#endif /* EB650315_AD21_460C_9B80_13EA6DC8F155 */
