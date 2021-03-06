#ifndef F76EB5C6_3C7E_46B6_AC56_C303873CDA4A
#define F76EB5C6_3C7E_46B6_AC56_C303873CDA4A

#include <vector>

#include "constants.h"
#include "waveform.h"

namespace plasma {
/**
 * @brief Phase coded waveform object.
 *
 */
class PhaseCodedWaveform : virtual public Waveform {
 protected:
  /**
   * @brief Number of phase chips in the waveform
   *
   */
  int d_num_chips;
  /**
   * @brief Chip duration (seconds)
   *
   */
  double d_chip_width;
  /**
   * @brief Vector of phase code values
   *
   */
  std::vector<double> d_code;

 public:
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return std::vector<std::complex<double>> The pulse data
   */
  virtual std::vector<std::complex<double>> sample() override;
  /**
   * @brief Get the phase code vector
   *
   * @return auto Code values
   */
  auto code() const { return d_code; }

  /**
   * @brief Get the number of chips
   *
   * @return int Number of chips
   */
  auto num_chips() const { return d_num_chips; }

  /**
   * @brief Get the chip width
   *
   * @return int Chip width (seconds)
   */
  auto chip_width() const { return d_chip_width; }

  /**
   * @brief Set the phase code vector
   *
   * @param code New code values
   */
  auto code(const std::vector<double>& code) { d_code = code; }

  /**
   * @brief Set the number of chips
   *
   * @param num_chips
   */
  auto num_chips(int num_chips) { d_num_chips = num_chips; };

  /**
   * @brief Set the chip width
   *
   * @param chipWidth New chip width
   */
  auto chip_width(int chip_width) { d_chip_width = chip_width; };

  /**
   * @brief Construct a new Phase Coded Waveform object
   *
   */
  PhaseCodedWaveform();

  /**
   * @brief Construct a new Phase Coded Waveform object
   *
   * @param num_chips Number of phase code values
   * @param chip_width Duration of each code value (seconds)
   * @param code Vector of code values
   */
  PhaseCodedWaveform(int num_chips, double chip_width, std::vector<double> code);
};
}  // namespace plasma
#endif /* F76EB5C6_3C7E_46B6_AC56_C303873CDA4A */
