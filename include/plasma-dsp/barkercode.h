#ifndef D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#define D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#include "phasecode.h"
#include "phasecodedwaveform.h"
#include "pulsedwaveform.h"

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
   * @param chipwidth Chip duration (seconds)
   * @param prf Pulse repetition frequency (Hz)
   * @param sampRate Sample Rate (Samples/second)
   */
  BarkerCode(int n, double chipwidth, double prf, double sampRate);

  /**
   * @brief Construct a new Barker Code object
   * 
   * @param n Code length
   * @param chipwidth Chip duration (seconds)
   * @param prf Pulse repetition frequency (Hz)
   * @param sampRate Sample Rate (Samples/second)
   */
  BarkerCode(int n, double chipwidth, std::vector<double> prf, double sampRate);
};

}  // namespace plasma

#endif /* D44B01D2_E99D_42FF_9E9A_BFDE907AE626 */
