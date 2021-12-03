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
  virtual std::vector<std::complex<double>> pulse() = 0;
  /**
   * @brief Generate the full PRF schedule defined by the waveform object.
   *
   * @return std::vector<std::complex<double>>
   */
  // TODO: Rename this
  virtual std::vector<std::complex<double>> step() = 0;
  /**
   * @brief Get the sample rate
   * 
   * @return auto sample rate
   */
  auto sampRate() const { return d_sampRate; }
  /**
   * @brief Set the sample rate
   * 
   * @param sampRate 
   * @return auto 
   */
  auto sampRate(double sampRate) { d_sampRate = sampRate; }
  /**
   * @brief Construct a new Waveform object
   * 
   */
  Waveform();
  /**
   * @brief Construct a new Waveform object
   * 
   * @param sampRate Sample Rate
   */
  Waveform(double sampRate);
};

#endif /* EB650315_AD21_460C_9B80_13EA6DC8F155 */
