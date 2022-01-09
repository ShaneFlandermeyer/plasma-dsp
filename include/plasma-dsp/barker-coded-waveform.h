#ifndef D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#define D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#include "phase-code.h"
#include "phase-coded-waveform.h"
#include "pulsed-waveform.h"

namespace plasma {

/**
 * @brief Barker-coded waveform
 *
 */
class BarkerCode : public PulsedWaveform, public PhaseCodedWaveform {
 public:
  /**
   * @brief Construct a new Barker Code object
   *
   */
  BarkerCode();

  /**
   * @brief Construct a new Barker Code object
   *
   * @param n Code length
   */
  BarkerCode(int n);

  /**
   * @brief Construct a new Barker Code object
   *
   * @param n Code length
   * @param chip_width Chip duration (seconds)
   * @param prf Pulse repetition frequency (Hz)
   * @param samp_rate Sample Rate (Samples/second)
   */
  BarkerCode(int n, double chip_width, double prf, double samp_rate);

  /**
   * @brief Construct a new Barker Code object
   *
   * @param n Code length
   * @param chip_width Chip duration (seconds)
   * @param prf Pulse repetition frequency (Hz)
   * @param samp_rate Sample Rate (Samples/second)
   */
  BarkerCode(int n, double chip_width, std::vector<double> prf,
             double samp_rate);
};

}  // namespace plasma

#endif /* D44B01D2_E99D_42FF_9E9A_BFDE907AE626 */
