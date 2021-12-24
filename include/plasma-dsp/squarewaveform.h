#ifndef B13D1A87_AACE_484D_9498_899C106CD35A
#define B13D1A87_AACE_484D_9498_899C106CD35A
#include "pulsedwaveform.h"
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
   * @param pulsewidth Pulse width (seconds)
   * @param prf PRF (Hz)
   * @param sampRate Sample Rate (samples/second)
   */
  SquareWaveform(double pulsewidth, double prf, double sampRate);
  /**
   * @brief Construct a new Square Waveform object
   *
   * @param pulsewidth Pulse width (seconds)
   * @param prf PRF (Hz)
   * @param sampRate Sample Rate (samples/second)
   */
  SquareWaveform(double pulsewidth, std::vector<double> prf, double sampRate);
  /**
   * @brief Destroy the Square Waveform object
   *
   */
  ~SquareWaveform();

 protected:
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return std::vector<std::complex<double>> Nonzero pulse samples
   */
  std::vector<std::complex<double>> sample() override;
};
}  // namespace plasma
#endif /* B13D1A87_AACE_484D_9498_899C106CD35A */
