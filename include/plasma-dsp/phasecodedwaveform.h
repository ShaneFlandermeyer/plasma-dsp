#ifndef F76EB5C6_3C7E_46B6_AC56_C303873CDA4A
#define F76EB5C6_3C7E_46B6_AC56_C303873CDA4A

#include <vector>

#include "constants.h"
#include "waveform.h"

/**
 * @brief Phase coded waveform object.
 * 
 */
class PhaseCodedWaveform : virtual public Waveform {
 protected:
  int d_nChips;
  double d_chipwidth;
  std::vector<double> d_code;

 public:
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return std::vector<std::complex<double>> The pulse data
   */
  virtual std::vector<std::complex<double>> pulse();
  /**
   * @brief Get the phase code vector
   *
   * @return auto
   */
  auto code() const { return d_code; }

  /**
   * @brief Get the number of chips
   *
   * @return int
   */
  auto nChips() const { return d_nChips; }

  /**
   * @brief Get the chip width
   *
   * @return int
   */
  auto chipwidth() const { return d_chipwidth; }

  /**
   * @brief Set the phase code vector
   *
   * @param code New code values
   * @return auto
   */
  auto code(const std::vector<double>& code) { d_code = code; }

  /**
   * @brief Set the number of chips
   *
   * @param nChips
   * @return auto
   */
  auto nChips(int nChips) { d_nChips = nChips; };

  /**
   * @brief Set the chip width
   *
   * @param chipWidth New chip width
   * @return auto
   */
  auto chipwidth(int chipwidth) { d_chipwidth = chipwidth; };

  /**
   * @brief Construct a new Phase Coded Waveform object
   *
   */
  PhaseCodedWaveform();

  /**
   * @brief Construct a new Phase Coded Waveform object
   *
   * @param nChips Number of phase code values
   * @param chipwidth Duration of each code value (seconds)
   * @param code Vector of code values
   */
  PhaseCodedWaveform(int nChips, double chipwidth, std::vector<double> code);

};

#endif /* F76EB5C6_3C7E_46B6_AC56_C303873CDA4A */
