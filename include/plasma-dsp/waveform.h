#ifndef EB650315_AD21_460C_9B80_13EA6DC8F155
#define EB650315_AD21_460C_9B80_13EA6DC8F155

#include <algorithm>
#include <complex>
#include <vector>
#include <Eigen/Dense>

#include "constants.h"
#include "vector_utils.h"

namespace plasma {

/**
 * @brief Abstract base class for waveform objects.
 *
 */

class Waveform {
public:
  /**
   * @brief Construct a new Waveform object
   *
   */
  Waveform();

  /**
   * @brief Construct a new Waveform object
   *
   *
   * @param samp_rate Sample Rate
   */
  Waveform(double samp_rate);

  /**
   * @brief Generate the nonzero samples of the waveform.
   *
   * If the frequency shift parameter is zero, this is the complex baseband
   * representation of the waveform. Otherwise, this returns a waveform centered
   * at the frequency offset.
   *
   * @return Eigen::ArrayXcd
   */
  Eigen::ArrayXcd waveform();

  /**
   * @brief Generate the matched filter for the waveform.
   *
   * The matched filter is the time-reversed complex conjugate of the nonzero
   * samples of the waveform.
   *
   * @return Eigen::ArrayXcd Matched filter vector
   */
  Eigen::ArrayXcd MatchedFilter();

  /**
   * @brief Get the sample rate
   *
   * @return double sample rate
   */
  double samp_rate() const { return d_samp_rate; }

  /**
   * @brief Get the frequency offset (Hz)
   *
   * @return double Frequency offset (Hz)
   */
  double freq_offset() const { return d_freq_offset; }

  /**
   * @brief Set the sample rate
   *
   * @param samp_rate
   */
  void samp_rate(double samp_rate) { d_samp_rate = samp_rate; }

  /**
   * @brief Set the frequency offset (Hz)
   *
   * @param freq_offset
   */
  void freq_offset(double freq_offset) { d_freq_offset = freq_offset; }

protected:
  /**
   * @brief Generate the non-zero portion of the waveform at complex baseband
   *
   * @return Eigen::ArrayXcd
   */
  virtual Eigen::ArrayXcd sample() = 0;

  /**
   * @brief Apply a frequency shift to the input waveform
   *
   * @param waveform Complex baseband waveform samples
   * @param offset Frequency offset (Hz)
   */
  void FrequencyShift(Eigen::ArrayXcd &waveform, double offset);

  /**
   * @brief Sample rate (waveform/second)
   *
   */
  double d_samp_rate;

  /**
   * @brief Frequency offset (Hz)
   *
   * TODO: This parameter currently cannot be set in any constructors.
   *
   */
  double d_freq_offset;
};

} // namespace plasma

#endif /* EB650315_AD21_460C_9B80_13EA6DC8F155 */
