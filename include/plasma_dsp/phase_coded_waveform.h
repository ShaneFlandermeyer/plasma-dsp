#ifndef F76EB5C6_3C7E_46B6_AC56_C303873CDA4A
#define F76EB5C6_3C7E_46B6_AC56_C303873CDA4A

#include "constants.h"
#include "pulsed_waveform.h"
#include "waveform.h"
#include <vector>
#include <arrayfire.h>

namespace plasma {
/**
 * @brief Phase coded waveform object.
 *
 */
class PhaseCodedWaveform : virtual public PulsedWaveform {
protected:
  /**
   * @brief Vector of phase code values
   *
   */
  af::array d_code;

  /**
   * @brief Chip duration (seconds)
   *
   */
  double d_chip_width;

  /**
   * @brief Number of phase chips in the waveform
   *
   */
  size_t d_num_chips;

public:
  /**
   * @brief Construct a new Phase Coded Waveform object
   *
   */
  PhaseCodedWaveform();

  /**
   * @brief Construct a new Phase Coded Waveform object
   *
   * @param code Code values
   * @param chip_width chip duration (seconds)
   * @param prf Pulse repetition frequency (Hz)
   * @param samp_rate Sample rate (Hz)
   */
  PhaseCodedWaveform(const af::array &code, double chip_width, double prf,
                     double samp_rate);

  /**
   * @brief Construct a new Phase Coded Waveform object
   *
   * @param code Code values
   * @param chip_width chip duration (seconds)
   * @param prf Pulse repetition frequency (Hz)
   * @param samp_rate Sample rate (Hz)
   */
  PhaseCodedWaveform(af::array code, double chip_width, std::vector<double> prf,
                     double samp_rate);
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return af::array The pulse data
   */
  virtual af::array sample() override;

  /**
   * @brief Get the phase code vector
   *
   * @return auto Code values
   */
  af::array code() const { return d_code; }

  /**
   * @brief Get the number of chips
   *
   * @return int Number of chips
   */
  size_t num_chips() const { return d_num_chips; }

  /**
   * @brief Get the chip width
   *
   * @return double Chip width (seconds)
   */
  double chip_width() const { return d_chip_width; }

  /**
   * @brief Set the phase code vector
   *
   * @param code New code values
   */
  void code(const af::array &code) { d_code = code; }

  /**
   * @brief Set the number of chips
   *
   * @param num_chips
   */
  void num_chips(size_t num_chips) { d_num_chips = num_chips; };

  /**
   * @brief Set the chip width
   *
   * @param chip_width New chip width
   */
  void chip_width(double chip_width) { d_chip_width = chip_width; };
};
} // namespace plasma
#endif /* F76EB5C6_3C7E_46B6_AC56_C303873CDA4A */
