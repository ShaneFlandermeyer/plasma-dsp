#ifndef D468419A_4F55_442A_997B_F6CD1989C7F6
#define D468419A_4F55_442A_997B_F6CD1989C7F6
#include "waveform.h"

namespace plasma {

/**
 * @brief An abstract base class for pulsed waveforms.
 *
 */
class PulsedWaveform : virtual public Waveform {
 protected:
  /**
   * @brief Pulse repetition frequency (Hz)
   *
   */
  std::vector<double> d_prf;
  /**
   * @brief Pulse width (seconds)
   *
   */
  double d_pulse_width;

 public:
  /**
   * @brief Generate the full PRF schedule defined by the waveform object.
   *
   * @return std::vector<std::complex<double>>
   */
  std::vector<std::complex<double>> pulse();
  /**
   * @brief Get the PRF schedule.
   *
   * @return auto Vector of PRFs
   */
  auto prf() const { return d_prf; }
  /**
   * @brief Get the pulse width.
   *
   * @return auto Pulse width (seconds)
   */
  auto pulse_width() const { return d_pulse_width; }
  /**
   * @brief Set the PRF as a double
   *
   * @param prf Desired PRF
   */
  auto prf(double prf) { d_prf.push_back(prf); }
  /**
   * @brief Set the PRF as a vector
   *
   * @param prf Desired PRF
   */
  auto prf(const std::vector<double> &prf) { d_prf = prf; }
  /**
   * @brief Set the pulse width
   *
   * @param pulse_width Desired pulse width
   */
  auto pulse_width(double pulse_width) { d_pulse_width = pulse_width; }
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
  PulsedWaveform(double pulse_width, std::vector<double> prf);
};
}  // namespace plasma
#endif /* D468419A_4F55_442A_997B_F6CD1989C7F6 */
