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
   * @brief Sample rate (waveform/second)
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
   * @brief Generate the nonzero samples of the waveform.
   * 
   * If the frequency shift parameter is zero, this is the complex baseband
   * representation of the waveform. Otherwise, this returns a waveform centered
   * at the frequency offset.
   *
   * @return std::vector<std::complex<double>>
   */
  std::vector<std::complex<double>> waveform();
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
   * @brief Generate a the non-zero portion of the waveform at complex baseband
   *
   * @return std::vector<std::complex<double>>
   */
  virtual std::vector<std::complex<double>> sample() = 0;
  /**
   * @brief Apply a frequency shift to the input waveform
   * 
   * @param waveform Complex baseband waveform samples
   * @param offset Frequency offset (Hz)
   */
  void FrequencyShift(std::vector<std::complex<double>> &waveform,
                      double offset);
};
}  // namespace plasma

#endif /* EB650315_AD21_460C_9B80_13EA6DC8F155 */
