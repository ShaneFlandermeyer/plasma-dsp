#ifndef BD5E6A09_B96F_4379_84DF_C755B8C14BF8
#define BD5E6A09_B96F_4379_84DF_C755B8C14BF8

#include "pulsedwaveform.h"
#include "waveform.h"

/**
 * @brief A linear frequency-modulated waveform.
 *
 */
class LinearFMWaveform : public PulsedWaveform {
 protected:
  // Sweep bandwidth (Hz)
  double d_bandwidth;

 public:
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return std::vector<std::complex<double>> The pulse data
   */
  std::vector<std::complex<double>> sample();
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
   * @brief Default constructor
   *
   * @param bandwidth Sweep bandwidth (Hz)
   * @param pulsewidth Pulse width (s)
   * @param prf Pulse repetition frequency (Hz)
   * @param sampRate Sample rate (samples/s)
   */
  LinearFMWaveform(double bandwidth, double pulsewidth, double prf,
                   double sampRate);
  /**
   * @brief Construct a new Linear FM Waveform object
   *
   * @param bandwidth Sweep bandwidth (Hz)
   * @param pulsewidth Pulse width (s)
   * @param prf Vector of pulse repetition frequency values (Hz)
   * @param sampRate Sample rate (samples/s)
   */
  LinearFMWaveform(double bandwidth, double pulsewidth, std::vector<double> prf,
                   double sampRate);
  /**
   * @brief Destroy the Linear FM Waveform object
   *
   */
  ~LinearFMWaveform();
};

#endif /* BD5E6A09_B96F_4379_84DF_C755B8C14BF8 */
