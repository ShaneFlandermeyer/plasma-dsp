#ifndef B50A8067_E867_4FD6_AE82_CDA1990F0971
#define B50A8067_E867_4FD6_AE82_CDA1990F0971

#include "waveform.h"

namespace plasma {

class FMCWWaveform : public Waveform {
 protected:
  /**
   * @brief Sweep duration (s)
   *
   */
  double d_sweep_time;
  /**
   * @brief Sweep bandwidth (Hz)
   *
   */
  double d_sweep_bandwidth;
  /**
   * @brief Generate the non-zero portion of the waveform at complex baseband
   *
   * @return std::vector<std::complex<double>>
   */
  std::vector<std::complex<double>> sample() override;

 public:
  /**
   * @brief Construct a new FMCWWaveform object
   *
   */
  FMCWWaveform() = default;
  /**
   * @brief Construct a new FMCWWaveform object
   *
   * @param sweep_time Sweep time (s)
   * @param sweep_bandwidth Sweep bandwidth (Hz)
   * @param samp_rate Sample rate (samples/s)
   */
  FMCWWaveform(double sweep_time, double sweep_bandwidth, double samp_rate);

  /**
   * @brief Get the sweep time (s)
   *
   * @return auto
   */
  auto sweep_time() const { return d_sweep_time; }
  /**
   * @brief Get the sweep bandwidth (Hz)
   *
   * @return auto Sweep bandwidth
   */
  auto sweep_bandwidth() const { return d_sweep_bandwidth; }
  /**
   * @brief Set the sweep time (s)
   *
   * @param sweep_time
   */
  void sweep_time(double sweep_time) { d_sweep_time = sweep_time; }
  /**
   * @brief Set the sweep bandwidth (Hz)
   *
   * @param sweep_bandwidth
   */
  void sweep_bandwidth(double sweep_bandwidth) {
    d_sweep_bandwidth = sweep_bandwidth;
  }
};
}  // namespace plasma
#endif /* B50A8067_E867_4FD6_AE82_CDA1990F0971 */
