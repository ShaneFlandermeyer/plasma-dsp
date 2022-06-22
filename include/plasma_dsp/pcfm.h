#ifndef F9D71799_6DD6_49D7_89EC_155A8D8D6228
#define F9D71799_6DD6_49D7_89EC_155A8D8D6228

#include <numeric>
#include <vector>

#include "pulsed_waveform.h"
#include "filter.h"
#include "fft.h"
#include <Eigen/Dense>

namespace plasma {

/**
 * @brief Polyphase_coded frequency modulated waveform
 *
 */
class PCFMWaveform : public PulsedWaveform {
protected:
  /**
   * @brief Phase code vector
   *
   */
  Eigen::ArrayXd d_code;
  /**
   * @brief Shaping filter vector
   *
   */
  Eigen::ArrayXd d_filter;
  /**
   * @brief Waveform samples
   *
   */
  Eigen::ArrayXcd d_waveform;

public:
  /**
   * @brief Construct a new PCFMWaveform object
   *
   */
  PCFMWaveform() = default;

  /**
   * @brief Construct a new PCFMWaveform object
   *
   * @param code Phase code values
   * @param filter Shaping filter taps
   * @param samp_rate Sample rate
   * @param prf Pulse repetition frequency (Hz)
   */
  PCFMWaveform(const Eigen::ArrayXd &code, const Eigen::ArrayXd &filter,
               double samp_rate, double prf);

  /**
   * @brief Destroy the PCFMWaveform object
   *
   */
  ~PCFMWaveform() = default;

  /**
   * @brief Generate the non-zero samples for a single pulse
   *
   * @return Eigen::ArrayXcd Nonzero pulse samples
   */
  Eigen::ArrayXcd sample() override;

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
  auto code(Eigen::ArrayXd code) { d_code = code; }

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
  auto filter(Eigen::ArrayXd filt) { d_filter = filt; }

protected:
private:
  // Compute the phase change between successive phase code chips
  Eigen::ArrayXd ComputePhaseChange();

  Eigen::ArrayXd oversample(const Eigen::ArrayXd &in, size_t factor);

  // Eigen::ArrayXd filter(const Eigen::ArrayXd &in, const Eigen::ArrayXd &filter);

  Eigen::ArrayXd cumsum(const Eigen::ArrayXd &in);
};

} // namespace plasma
#endif /* F9D71799_6DD6_49D7_89EC_155A8D8D6228 */
