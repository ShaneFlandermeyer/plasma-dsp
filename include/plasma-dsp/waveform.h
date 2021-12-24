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
  /**
   * @brief Sample rate (samples/second)
   * 
   */
  double d_samp_rate;
  /**
   * @brief Frequency offset (Hz)
   * 
   */
  double d_freq_offset;

 public:
 /**
  * @brief Generate only the nonzero sample of the waveform.
  * 
  * @return std::vector<std::complex<double>> 
  */
  std::vector<std::complex<double>> waveform();
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
  auto samp_rate() const { return d_samp_rate; }
  /**
   * @brief Get the frequency offset (Hz)
   *
   * @return auto
   */
  auto freq_offset() const { return d_freq_offset; }
  /**
   * @brief Set the sample rate
   *
   * @param samp_rate
   * @return auto
   */
  auto samp_rate(double samp_rate) { d_samp_rate = samp_rate; }
  /**
   * @brief Set the frequency offset (Hz)
   *
   * @param freq_offset
   * @return auto
   */
  auto freq_offset(double freq_offset) { d_freq_offset = freq_offset; }
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
   * @param samp_rate Sample Rate
   */
  Waveform(double samp_rate);

 protected:
  /**
   * @brief Generate a the non-zero portion of the waveform, without accounting
   * for a frequency shift
   *
   * @return std::vector<std::complex<double>>
   */
  virtual std::vector<std::complex<double>> sample() = 0;
};
}  // namespace plasma

#endif /* EB650315_AD21_460C_9B80_13EA6DC8F155 */
