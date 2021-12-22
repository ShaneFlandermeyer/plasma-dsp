#ifndef F9D71799_6DD6_49D7_89EC_155A8D8D6228
#define F9D71799_6DD6_49D7_89EC_155A8D8D6228

#include <numeric>
#include <vector>

#include "pulsedwaveform.h"
#include "utils.h"

namespace plasma {

/**
 * @brief Polyphase-coded frequency modulated waveform
 *
 */
class PCFMWaveform : public PulsedWaveform {
 protected:
  // Phase code vector
  std::vector<double> d_code;
  // Shaping filter taps
  std::vector<double> d_filter;
  // Waveform vector
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
   * @param code Phase code
   * @param filter Shaping filter taps
   */
  PCFMWaveform(const std::vector<double>& code,
               const std::vector<double>& filter);

  ~PCFMWaveform() = default;

  /**
   * @brief Generate the non-zero samples for a single pulse
   *
   * @return std::vector<std::complex<double>>
   */
  std::vector<std::complex<double>> waveform() override;

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
   * @return auto
   */
  auto filter(std::vector<double> filt) { d_filter = filt; }
};

}
#endif /* F9D71799_6DD6_49D7_89EC_155A8D8D6228 */
