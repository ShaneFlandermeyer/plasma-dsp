#ifndef D62729DA_CADC_457A_97F7_1CF6F2287795
#define D62729DA_CADC_457A_97F7_1CF6F2287795

#include "pulsed_waveform.h"
#include <arrayfire.h>

namespace plasma {

class CPMWaveform: public PulsedWaveform{
protected:
/**
   * @brief Encoded communications message
   *
   */
  af::array d_comms;
  /**
   * @brief Shaping filter
   *
   */
  af::array d_filter;
public:
  /**
   * @brief Construct a new PARCWaveform object
   *
   */
  CPMWaveform() = default;

  /**
   * @brief Construct a new CPMWaveform object
   *
   * @param comms The base radar waveform
   * @param filter Shaping filter taps
   * @param pulse_width Pulse width in sec
   * @param samp_rate sample rate 
   * @param prf pulse repition frequency
   * @param h modulation index
   */
  CPMWaveform(af::array radar, af::array filter, double pulse_width, double samp_rate, double prf, double h = 1./2);

  /**
   * @brief Destroy the CPMWaveform object
   *
   */
  ~CPMWaveform() = default;

  /**
   * @brief Generates non-zero samples for one pulse
   *
   * @return af::array the pulse samples
   */
  af::array sample() override;

  /**
   * @brief get the communication message
   *
   * @return auto communication message
   */
  af::array comms() const { return d_comms; }

  /**
   * @brief Set the communication message
   *
   * @param code Desired communication message
   * @return auto
   */
  void comms(af::array comms) { d_comms = comms; }

  /**
   * @brief Get the shaping filter
   *
   * @return Shaping filter
   */
  af::array filter() const { return d_filter; }

  /**
   * @brief Set the shaping filter
   *
   * @param filt Desired shaping filter
   * @return auto The vector of filter taps
   */
  void filter(af::array filt) { d_filter = filt; }


};
} // namespace plasma

#endif /* D62729DA_CADC_457A_97F7_1CF6F2287795 */
