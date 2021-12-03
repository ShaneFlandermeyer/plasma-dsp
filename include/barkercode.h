#ifndef D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#define D44B01D2_E99D_42FF_9E9A_BFDE907AE626
#include "phasecodedwaveform.h"
#include "pulsedwaveform.h"

class BarkerCode : public PulsedWaveform, public PhaseCodedWaveform {
  // TODO: Constructors
 public:
 /**
  * @brief Generate data for a single pulse
  * 
  * @return std::vector<std::complex<double>> Pulse data 
  */
  std::vector<std::complex<double>> pulse();
  /**
   * @brief Generate data for a full PRF schedule
   * 
   * @return std::vector<std::complex<double>> Pulse data for at least 1 PRF
   */
  std::vector<std::complex<double>> step();
  /**
   * @brief Construct a new Barker Code object
   *
   */
  BarkerCode();
  // TODO: Set code length
};

#endif /* D44B01D2_E99D_42FF_9E9A_BFDE907AE626 */
