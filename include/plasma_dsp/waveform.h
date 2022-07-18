#ifndef EB650315_AD21_460C_9B80_13EA6DC8F155
#define EB650315_AD21_460C_9B80_13EA6DC8F155

#include <algorithm>
#include <complex>
#include <vector>
#include <arrayfire.h>
#include "constants.h"

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
  virtual af::array step() = 0;

  /**
   * @brief Generate the non-zero portion of the waveform at complex baseband
   *
   * @return Eigen::ArrayXcd
   */
  virtual af::array sample() = 0;

  /**
   * @brief Generate the matched filter for the waveform.
   *
   * The matched filter is the time-reversed complex conjugate of the nonzero
   * samples of the waveform.
   *
   * @return Eigen::ArrayXcd Matched filter vector
   */
  af::array MatchedFilter();

  /**
   * @brief Get the sample rate
   *
   * @return double sample rate
   */
  double samp_rate() const { return d_samp_rate; }

  /**
   * @brief Set the sample rate
   *
   * @param samp_rate
   */
  void samp_rate(double samp_rate) { d_samp_rate = samp_rate; }


protected:

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
