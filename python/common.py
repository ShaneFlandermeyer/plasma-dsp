from typing import Optional

import jax.numpy as jnp
from matplotlib import pyplot as plt

from python.linear_fm import lfm


def delay(x: jnp.ndarray,
          tau: float,
          fs: float) -> jnp.ndarray:
  """
  Delay the input signal by tau seconds.

  The delay is formed as a phase shift in the frequency domain. 

  Parameters
  ----------
  x : jnp.ndarray
      Input signal
  tau : float
      Time delay (s)
  fs : float
      Sample rate (samples/s)

  Returns
  -------
  jnp.ndarray
      Delayed signal
  """
  assert x.ndim == 1, "Only 1D signals are supported for now"

  # To avoid aliasing during the delay operation, the FFT length has to be increased so that the entire delay "fits". These extra samples are chopped off from the end of the signal before returning
  int_delay_samps = int(jnp.round(tau * fs))
  nfft = x.shape[0] + max(0, int_delay_samps)

  # Apply the delay
  Faxis = jnp.fft.fftfreq(nfft, d=1/fs)
  x_fft = jnp.fft.fft(x, n=nfft) * jnp.exp(-1j * 2 * jnp.pi * Faxis * tau)
  return jnp.fft.ifft(x_fft)[:-int_delay_samps]


if __name__ == '__main__':
  fs = 50e6
  pw = 10e-6
  bw = fs / 2
  start_freq = -bw / 2
  np = 512
  x = lfm(bandwidth=bw,
          pulsewidth=pw,
          samp_rate=fs,
          start_freq=start_freq,
          prf=None)

  tau = 5e-6
  y = delay(x, tau, fs)

  plt.figure()
  plt.plot(jnp.real(y))
  plt.show()
