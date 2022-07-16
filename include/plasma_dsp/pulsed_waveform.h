#ifndef D468419A_4F55_442A_997B_F6CD1989C7F6
#define D468419A_4F55_442A_997B_F6CD1989C7F6
#include "waveform.h"

namespace plasma {

/**
 * @brief An abstract base class for pulsed waveforms.
 *
 */
class PulsedWaveform : virtual public Waveform {
public:
  /**
   * @brief Construct a new Pulsed Waveform object
   *
   */
  PulsedWaveform();

  /**
   * @brief Construct a new Pulsed Waveform object
   *
   * @param pulse_width Pulse width (s)
   * @param prf Pulse repetition frequency (Hz)
   */
  PulsedWaveform(double pulse_width, double prf);

  /**
   * @brief Construct a new Pulsed Waveform object
   *
   * @param pulse_width Pulse width (s)
   * @param prf Pulse repetition frequency (Hz)
   */
  PulsedWaveform(double pulse_width, af::array prf);

  /**
   * @brief Generate the full PRF schedule defined by the waveform object.
   *
   * @return af::array A PRI of data
   */
  af::array step() override;

  /**
   * @brief Get the PRF schedule.
   *
   * @return af::array An array of PRFs
   */
  af::array prf() const { return d_prf; }

  /**
   * @brief Get the pulse width.
   *
   * @return double Pulse width (seconds)
   */
  double pulse_width() const { return d_pulse_width; }

  /**
   * @brief Set the PRF as a double
   *
   * @param prf Desired PRF
   */
  void prf(double prf) { d_prf = prf; }

  /**
   * @brief Set the PRF as a vector
   *
   * @param prf Desired PRF
   */
  auto prf(const af::array &prf) { d_prf = prf; }

  /**
   * @brief Set the pulse width
   *
   * @param pulse_width Desired pulse width
   */
  auto pulse_width(double pulse_width) { d_pulse_width = pulse_width; }

protected:
  /**
   * @brief Pulse repetition frequency (Hz)
   *
   */
  af::array d_prf;

  /**
   * @brief Pulse width (seconds)
   *
   */
  double d_pulse_width;

  /**
   * @brief PRF index
   *
   */
  size_t d_prf_counter = 0;
};
} // namespace plasma
#endif /* D468419A_4F55_442A_997B_F6CD1989C7F6 */
