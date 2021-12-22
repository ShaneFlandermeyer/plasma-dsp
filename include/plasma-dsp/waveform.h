#ifndef EB650315_AD21_460C_9B80_13EA6DC8F155
#define EB650315_AD21_460C_9B80_13EA6DC8F155

#include <complex>
#include <vector>

#include "constants.h"
namespace plasma {
/**
 * @brief Abstract base class for waveform objects.
 *
 */
class Waveform {
 protected:
  // Waveform sample rate
  double d_sampRate;
  double d_freqOffset;

 public:
  /**
   * @brief Generate a the non-zero portion of the waveform.
   *
   * @return std::vector<std::complex<double>>
   */
  virtual std::vector<std::complex<double>> waveform() = 0;
  /**
   * @brief Generate the full PRF schedule defined by the waveform object.
   *
   * @return std::vector<std::complex<double>>
   */
  virtual std::vector<std::complex<double>> pulse() = 0;
  /**
   * @brief Get the sample rate
   *
   * @return auto sample rate
   */
  auto sampRate() const { return d_sampRate; }
  /**
   * @brief Get the frequency offset (Hz)
   * 
   * @return auto 
   */
  auto freqOffset() const { return d_freqOffset; }
  /**
   * @brief Set the sample rate
   *
   * @param sampRate
   * @return auto
   */
  auto sampRate(double sampRate) { d_sampRate = sampRate; }
  /**
   * @brief Set the frequency offset (Hz)
   *
   * @param freqOffset
   * @return auto
   */
  auto freqOffset(double freqOffset) { d_freqOffset = freqOffset; }
  /**
   * @brief Construct a new Waveform object
   *
   */
  Waveform();
  /**
   * @brief Construct a new Waveform object
   * 
   * TODO: Add frequency offset parameter
   * 
   * @param sampRate Sample Rate
   */
  Waveform(double sampRate);
};
}  // namespace plasma

#endif /* EB650315_AD21_460C_9B80_13EA6DC8F155 */
