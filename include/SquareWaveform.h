#ifndef SQUARE_WAVE_H
#define SQUARE_WAVE_H
#include "PulsedWaveform.h"

/**
 * @brief A square (constant-amplitude) pulsed waveform.
 * 
 */
class SquareWaveform : public PulsedWaveform {
 public:
  /**
   * @brief Generate a single pulse of the waveform.
   *
   * @return std::vector<std::complex<double>> The pulse data
   */
  std::vector<std::complex<double>> sample();
  /**
   * @brief Construct a new Square Waveform object
   * 
   */
  SquareWaveform();
  /**
   * @brief Construct a new Square Waveform object
   * 
   * @param pulsewidth 
   * @param prf 
   * @param sampRate 
   */
  SquareWaveform(double pulsewidth, double prf, double sampRate);
  /**
   * @brief Construct a new Square Waveform object
   * 
   * @param pulsewidth 
   * @param prf 
   * @param sampRate 
   */
  SquareWaveform(double pulsewidth, std::vector<double> prf, double sampRate);
  /**
   * @brief Destroy the Square Waveform object
   * 
   */
  ~SquareWaveform();
};
#endif
