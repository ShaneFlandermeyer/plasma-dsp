#ifndef B13D1A87_AACE_484D_9498_899C106CD35A
#define B13D1A87_AACE_484D_9498_899C106CD35A

#include "pulsed_waveform.h"

namespace plasma {
/**
 * @brief A square (constant-amplitude) pulsed waveform.
 *
 */
class SquareWaveform : public PulsedWaveform {
public:
    /**
   * @brief Construct a new Square Waveform object
   *
   */
  SquareWaveform();

  /**
   * @brief Construct a new Square Waveform object
   *
   * @param pulse_width Pulse width (seconds)
   * @param prf PRF (Hz)
   * @param samp_rate Sample Rate (samples/second)
   */
  SquareWaveform(double pulse_width, double prf, double samp_rate);

  /**
   * @brief Construct a new Square Waveform object
   *
   * @param pulse_width Pulse width (seconds)
   * @param prf PRF (Hz)
   * @param samp_rate Sample Rate (samples/second)
   */
  SquareWaveform(double pulse_width, Eigen::ArrayXd prf, double samp_rate);

  /**
   * @brief Destroy the Square Waveform object
   *
   */
  ~SquareWaveform();

  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return Eigen::ArrayXcd Nonzero pulse samples
   */
  Eigen::ArrayXcd sample() override;
};
} // namespace plasma
#endif /* B13D1A87_AACE_484D_9498_899C106CD35A */
