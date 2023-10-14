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
private:
/**
   * @brief Radar waveform
   *
   */
  af::array d_radar;
  /**
   * @brief Communications waveform
   *
   */
  af::array d_comm;
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
   * @brief Get the communication waveform
   *
   * @return auto Communication waveform signal
   */
  af::array comm() const { return d_comm; }

  /**
   * @brief Set the communication waveform
   *
   * @param code Desired communication waveform
   * @return auto
   */
  void comm(af::array comm_signal) { d_comm = comm_signal; }

  /**
   * @brief Get the radar waveform
   *
   * @return Radar waveform signal
   */
  af::array radar() const { return d_radar; }

  /**
   * @brief Set the radar waveform
   *
   * @param filt Desired radar waveform
   * @return auto The desired radar waveform to transmit
   */
  void radar(af::array radar) { d_radar = radar; }

  /**
   * @brief Demodulate the PARC waveform
   *
   * @details This function demodulates the input PARC signal into just
   * the radar waveform or just the communications waveform.
   * This is achieved by mixing the original signal with the complex
   * conjugate of the waveform you want to remove.
   *
   * @param in The signal you want to remove
   * @param ref Reference signal (PARC waveform)
   * @return af::array demodulated signal
   */
  af::array demod(const af::array &in);

};
} // namespace plasma
#endif /* DBD95BD8_925A_418D_81A9_D8E23B2E7EC6 */
