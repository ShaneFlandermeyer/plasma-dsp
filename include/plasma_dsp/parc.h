#ifndef DBD95BD8_925A_418D_81A9_D8E23B2E7EC6
#define DBD95BD8_925A_418D_81A9_D8E23B2E7EC6

#include "pulsed_waveform.h"
#include <arrayfire.h>

namespace plasma {
/**
 * @brief A class that represents a phase-attached radar/communications waveform.
 *
 */

class PARCWaveform : public PulsedWaveform {
public:
    /**
   * @brief Construct a new PARCWaveform object
   *
   */
  PARCWaveform() = default;

  /**
   * @brief Construct a new PARCWaveform object
   *
   * @param radar The base radar waveform
   * @param comm The communication waveform
   */
  PARCWaveform(af::array radar, af::array comm);

  /**
   * @brief Destroy the PARCWaveform object
   *
   */
  ~PARCWaveform() = default;

  /**
   * @brief Creates data for one pulse
   *
   * @return af::array Nonzero pulse samples
   */
  af::array sample() override;

  /**
   * @brief Demodulate the PARC waveform
   *
   * @details This function demodulates the input PARC signal by mixing it 
   * with the base radar waveform. This leaves just the communication signal.
   * This is achieved by multiplying the input signal with the radar waveform's 
   * complex conjugate.
   *
   * @param in Input signal
   * @param ref Reference signal
   * @return af::array communication waveform
   */
  af::array demod(const af::array &in);

};
} // namespace plasma
#endif /* DBD95BD8_925A_418D_81A9_D8E23B2E7EC6 */
