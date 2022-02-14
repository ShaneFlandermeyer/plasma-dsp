#ifndef BD5E6A09_B96F_4379_84DF_C755B8C14BF8
#define BD5E6A09_B96F_4379_84DF_C755B8C14BF8

#include "pulsed_waveform.h"
#include <numeric>

namespace plasma {

/**
 * @brief A linear frequency-modulated waveform.
 *
 */
class LinearFMWaveform : public PulsedWaveform {
protected:
  /**
   * @brief Sweep bandwidth (Hz)
   *
   */
  double d_bandwidth;

public:
  /**
   * @brief Get the waveform bandwidth.
   *
   * @return auto bandwidth (Hz)
   */
  auto bandwidth() const { return d_bandwidth; }
  /**
   * @brief Set the waveform bandwidth
   *
   * @param bandwidth
   * @return auto
   */
  auto bandwidth(double bandwidth) { d_bandwidth = bandwidth; }
  /**
   * @brief Construct a new Linear FM waveform object.
   *
   */
  LinearFMWaveform();
  /**
   * @brief Construct a new Linear FM waveform object.
   *
   * @param bandwidth Sweep bandwidth (Hz)
   * @param pulse_width Pulse width (s)
   * @param prf Pulse repetition frequency (Hz)
   * @param samp_rate Sample rate (samples/s)
   */
  LinearFMWaveform(double bandwidth, double pulse_width, double prf,
                   double samp_rate);
  /**
   * @brief Construct a new Linear FM Waveform object
   *
   * @param bandwidth Sweep bandwidth (Hz)
   * @param pulse_width Pulse width (s)
   * @param prf Vector of pulse repetition frequency values (Hz)
   * @param samp_rate Sample rate (samples/s)
   */
  LinearFMWaveform(double bandwidth, double pulse_width,
                   Eigen::ArrayXd prf, double samp_rate);
  /**
   * @brief Destroy the Linear FM Waveform object
   *
   */
  ~LinearFMWaveform() = default;

protected:
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return std::vector<std::complex<double>> The pulse data
   */
  Eigen::ArrayXcd sample(double t1 = -1, double t2 = -1) override;
};
} // namespace plasma
#endif /* BD5E6A09_B96F_4379_84DF_C755B8C14BF8 */
