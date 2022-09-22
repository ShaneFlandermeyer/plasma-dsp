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
   * @param prf_schedule PRF schedule (Hz)
   */
  PulsedWaveform(double pulse_width, std::vector<double> prf_schedule);

  /**
   * @brief Generate the full PRF schedule defined by the waveform object.
   *
   * @return af::array A PRI of data
   */
  af::array step() override;

  /**
   * @brief Get the PRF schedule
   *
   * @return std::vector<double>
   */
  std::vector<double> prf_schedule() const { return d_prf_schedule; }

  /**
   * @brief Get the current PRF
   *
   * @return double
   */
  double prf() const { return d_prf; }

  /**
   * @brief Get the pulse width.
   *
   * @return double
   */
  double pulse_width() const { return d_pulse_width; }

  void prf_schedule(const std::vector<double> schedule) {
    d_prf_schedule = schedule;
  }
  /**
   * @brief Set the PRF as a double
   *
   * @param prf Desired PRF
   */
  void prf(double prf) { d_prf = prf; }

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
  double d_prf;

  /**
   * @brief PRF schedule
   *
   * If specified, the step() method cycles through this vector to determine the
   * PRF at each pulse
   *
   */
  std::vector<double> d_prf_schedule;

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
