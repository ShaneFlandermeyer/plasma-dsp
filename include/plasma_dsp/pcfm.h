#ifndef F9D71799_6DD6_49D7_89EC_155A8D8D6228
#define F9D71799_6DD6_49D7_89EC_155A8D8D6228

#include <numeric>
#include <vector>

#include "pulsed_waveform.h"
#include "filter.h"
#include "fft.h"
#include <arrayfire.h>

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
  af::array d_code;
  /**
   * @brief Shaping filter vector
   *
   */
  af::array d_filter;
  /**
   * @brief Waveform samples
   *
   */
  af::array d_waveform;

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
  PCFMWaveform(af::array code, af::array filter,
               double samp_rate, double prf);

  /**
   * @brief Destroy the PCFMWaveform object
   *
   */
  ~PCFMWaveform() = default;

  /**
   * @brief Generate the non-zero samples for a single pulse
   *
   * @return af::array Nonzero pulse samples
   */
  af::array sample() override;

  /**
   * @brief Get the phase code
   *
   * @return auto Phase code vector
   */
  af::array code() const { return d_code; }

  /**
   * @brief Set the phase code vector
   *
   * @param code Desired code vector
   * @return auto
   */
  void code(af::array code) { d_code = code; }

  /**
   * @brief Get the shaping filter
   *
   * @return Shaping filter taps
   */
  af::array filter() const { return d_filter; }

  /**
   * @brief Set the shaping filter
   *
   * @param filt Desired shaping filter
   * @return auto The vector of filter taps
   */
  void filter(af::array filt) { d_filter = filt; }

protected:
private:
  // Compute the phase change between successive phase code chips
  af::array ComputePhaseChange();

  af::array oversample(af::array in, size_t factor);

  // af::array filter(const af::array &in, const af::array &filter);

  af::array cumsum(const af::array &in);
};

} // namespace plasma
#endif /* F9D71799_6DD6_49D7_89EC_155A8D8D6228 */
