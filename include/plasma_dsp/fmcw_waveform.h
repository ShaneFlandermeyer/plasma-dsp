#ifndef B50A8067_E867_4FD6_AE82_CDA1990F0971
#define B50A8067_E867_4FD6_AE82_CDA1990F0971

#include "waveform.h"
#include <numeric>

namespace plasma {

/**
 * @brief Class representing an FMCW waveform
 *
 * TODO: Implement triangular sweep
 * TODO: Implement nonlinear FMCW
 */
class FMCWWaveform : public Waveform {

public:
    /**
   * @brief Location of FM Sweep interval
   *
   */
  enum SweepInterval {
    /**
     * @brief Waveform sweeps the interval 0 to sweep_bandwidth
     *
     */
    POSITIVE = 0,
    /**
     * @brief Waveform sweeps the interval -sweep_bandwidth to sweep_bandwidth
     *
     */
    SYMMETRIC = 1
  };

  /**
   * @brief FM sweep direction
   *
   */
  enum SweepDirection {
    /**
     * @brief Sweep from low to high frequency
     *
     */
    UP = 1,
    /**
     * @brief Sweep from high to low frequency
     *
     */
    DOWN = -1
  };

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
  FMCWWaveform(double sweep_time, double sweep_bandwidth, double samp_rate,
               SweepInterval interval = SYMMETRIC,
               SweepDirection direction = UP);

  /**
   * @brief Generate samples of the complex baseband waveform
   *
   * @return af::array
   */
  af::array sample() override;
  /**
   * @brief Return a single sweep of the FMCW waveform
   *
   * @return af::array
   */
  af::array step() override;

  /**
   * @brief Dechirp the FMCW signal
   *
   * @details This function demodulates the input FMCW signal by mixing it with
   * the transmitted reference signal. For a discrete-time signal, this mixing
   * operation is defined as y[n] = ref[n] * conj(x[n]), and produces a
   * narrowband beat signal
   *
   * @param in Input signal
   * @param ref Reference signal
   * @return af::array dechirped beat signal
   */
  af::array demod(const af::array &in);

  /**
   * @brief Get the sweep time (s)
   *
   * @return double
   */
  double sweep_time() const { return d_sweep_time; }

  /**
   * @brief Get the sweep bandwidth (Hz)
   *
   * @return double
   */
  double sweep_bandwidth() const { return d_sweep_bandwidth; }

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
   * @brief Sweep direction
   *
   */
  SweepDirection d_sweep_direction;

  /**
   * @brief
   *
   */
  SweepInterval d_sweep_interval;

  /**
   * @brief Number of sweeps
   *
   */
  double d_num_sweeps;
};
} // namespace plasma
#endif /* B50A8067_E867_4FD6_AE82_CDA1990F0971 */
