#ifndef F9D71799_6DD6_49D7_89EC_155A8D8D6228
#define F9D71799_6DD6_49D7_89EC_155A8D8D6228

#include <numeric>
#include <vector>

#include "pulsed-waveform.h"
#include "signal-processing.h"

namespace plasma {

/**
 * @brief Polyphase-coded frequency modulated waveform
 *
 */
class PCFMWaveform : public PulsedWaveform {
 protected:
  /**
   * @brief Phase code vector
   * 
   */
  std::vector<double> d_code;
  /**
   * @brief Shaping filter vector
   * 
   */
  std::vector<double> d_filter;
  /**
   * @brief Waveform samples
   * 
   */
  std::vector<std::complex<double>> d_waveform;

 public:
  /**
   * @brief Construct a new PCFMWaveform object
   *
   */
  PCFMWaveform();
  /**
   * @brief Construct a new PCFMWaveform object
   *
   * @param code Vector of phase code values
   * @param filter Shaping filter taps
   */
  PCFMWaveform(const std::vector<double>& code,
               const std::vector<double>& filter);

  /**
   * @brief Destroy the PCFMWaveform object
   * 
   */
  ~PCFMWaveform() = default;

  /**
   * @brief Get the phase code
   *
   * @return auto Phase code vector
   */
  auto code() const { return d_code; }

  /**
   * @brief Set the phase code vector
   *
   * @param code Desired code vector
   * @return auto
   */
  auto code(std::vector<double> code) { d_code = code; }

  /**
   * @brief Get the shaping filter
   *
   * @return Shaping filter taps
   */
  auto filter() const { return d_filter; }

  /**
   * @brief Set the shaping filter
   *
   * @param filt Desired shaping filter
   * @return auto The vector of filter taps
   */
  auto filter(std::vector<double> filt) { d_filter = filt; }

 protected:
  /**
   * @brief Generate the non-zero samples for a single pulse
   *
   * @return std::vector<std::complex<double>>
   */
  std::vector<std::complex<double>> sample() override;
};

}  // namespace plasma
#endif /* F9D71799_6DD6_49D7_89EC_155A8D8D6228 */
