#ifndef BD5E6A09_B96F_4379_84DF_C755B8C14BF8
#define BD5E6A09_B96F_4379_84DF_C755B8C14BF8

#include "pulsed_waveform.h"
// #include <numeric>

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

  /**
   * @brief Sweep start frequency (Hz)
   *
   */
  double d_start_freq;

public:
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
   * @param start_freq Starting sweep frequency (Hz)
   */
  LinearFMWaveform(double bandwidth, double pulse_width, double samp_rate,
                   double prf = 0, double start_freq = 0);

  /**
   * @brief Construct a new Linear FM Waveform object
   *
   * @param bandwidth Sweep bandwidth (Hz)
   * @param pulse_width Pulse width (s)
   * @param prf Vector of pulse repetition frequency values (Hz)
   * @param samp_rate Sample rate (samples/s)
   * @param start_freq Starting sweep frequency (Hz)
   */
  LinearFMWaveform(double bandwidth, double pulse_width, double samp_rate,
                   std::vector<double> prf, double start_freq = 0);

  /**
   * @brief Destroy the Linear FM Waveform object
   *
   */
  ~LinearFMWaveform() = default;

  /**
   * @brief Get the waveform bandwidth.
   *
   * @return auto bandwidth (Hz)
   */
  double bandwidth() const { return d_bandwidth; }

  /**
   * @brief Set the waveform bandwidth
   *
   * @param bandwidth
   * @return auto
   */
  void bandwidth(double bandwidth) { d_bandwidth = bandwidth; }

  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return af::array The pulse data
   */
  af::array sample() override;
};
} // namespace plasma
#endif /* BD5E6A09_B96F_4379_84DF_C755B8C14BF8 */
