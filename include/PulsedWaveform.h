#ifndef PULSED_WAVEFORM_H
#define PULSED_WAVEFORM_H
#include "Waveform.h"

/**
 * @brief An abstract base class for pulsed waveforms.
 * 
 */
class PulsedWaveform : public Waveform {
 protected:
  // Pulse repetition frequency (Hz)
  std::vector<double> d_prf;
  // Pulse width (s)
  double d_pulsewidth;

 public:
  /**
   * @brief Generate the full PRF schedule defined by the waveform object.
   *
   * @return std::vector<std::complex<double>>
   */
  std::vector<std::complex<double>> step();
  /**
   * @brief Get the PRF schedule.
   * 
   * @return auto 
   */
  auto prf() const { return d_prf; }
  /**
   * @brief Get the pulse width.
   * 
   * @return auto 
   */
  auto pulsewidth() const { return d_pulsewidth; }
  /**
   * @brief Set the PRF as a double
   * 
   * @param prf 
   * @return auto 
   */
  auto prf(double prf) { d_prf.push_back(prf); }
  /**
   * @brief Set the PRF as a vector
   * 
   * @param prf 
   * @return auto 
   */
  auto prf(std::vector<double> prf) { d_prf = prf; }
  /**
   * @brief Set the pulse width
   * 
   * @param pulsewidth 
   * @return auto 
   */
  auto pulsewidth(double pulsewidth) { d_pulsewidth = pulsewidth; }
};
#endif