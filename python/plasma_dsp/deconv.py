import jax.numpy as jnp
from common import delay, doppler_shift
from linear_fm import lfm
import matplotlib.pyplot as plt
from pulse_doppler import filter_lti, process_doppler


def richardson_lucy(range_doppler: jnp.ndarray,
                    psf: jnp.ndarray,
                    ) -> jnp.ndarray:
  pass


if __name__ == '__main__':
  # Try to reproduce the results from the paper

  # Base waveforms
  fs = 100e6
  pw = 10e-6
  bw = 40e6
  x1 = lfm(bandwidth=bw,
           pulsewidth=pw,
           samp_rate=fs,
           start_freq=-bw)
  x2 = lfm(bandwidth=bw,
           pulsewidth=pw,
           samp_rate=fs,
           start_freq=-bw / 4)

  # TODO: Simulate the pulses with a delay and/or doppler shift
  # Logic: 8 pulses of x1 are sent, followed by 2 pulses of x2
  prf = 10e3
  np = 128
  ipulse = jnp.arange(np)
  fast_slow_time = jnp.zeros((x1.shape[0], np), dtype=x1.dtype)
  fast_slow_time = fast_slow_time.at[:, ipulse % 10 < 8].set(x1.reshape(-1, 1))
  fast_slow_time = fast_slow_time.at[:,
                                     ipulse % 10 >= 8].set(x2.reshape(-1, 1))

  # Apply a matched filter to each pulse
  h = jnp.zeros((x1.shape[0], np), dtype=x1.dtype)
  h = h.at[:, ipulse % 10 < 8].set(
      jnp.flipud(jnp.conjugate(x1)).reshape(-1, 1))
  h = h.at[:, ipulse % 10 >= 8].set(
      jnp.flipud(jnp.conjugate(x2)).reshape(-1, 1))
  range_slow_time = filter_lti(fast_slow_time, h)

  # Doppler processing
  dynamic_range_db = 70
  rdm = process_doppler(range_slow_time)
  rdm = rdm.at[jnp.abs(rdm) < 10**(-dynamic_range_db/20)
               ].set(10**(-dynamic_range_db/20))
  rdm = rdm / jnp.max(rdm)

  # freq_pulse = jnp.fft.fftshift(jnp.fft.fft(fast_slow_time, axis=0), axes=0)
  # Faxis = jnp.fft.fftshift(jnp.fft.fftfreq(freq_pulse.shape[0], d=1/fs))
  # plt.imshow(abs(freq_pulse), aspect='auto', origin='lower',
  #            extent=(0, np, Faxis[0] / 1e6, Faxis[-1] / 1e6))
  # plt.plot(20*jnp.log10(abs(range_slow_time)))
  plt.imshow(20*jnp.log10(jnp.abs(rdm)), aspect='auto',
             origin='lower', cmap='plasma')
  plt.colorbar()
  plt.clim([-dynamic_range_db, 0])
  plt.show()
