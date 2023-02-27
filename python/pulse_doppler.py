from typing import Optional

import jax
import jax.numpy as jnp
import matplotlib.pyplot as plt
from python.linear_fm import lfm


def filter(x: jnp.ndarray,
           h: jnp.ndarray,
           axis: int = 0) -> jnp.ndarray:
  """
  Compute the response of a linear time invariant (LTI) system 
  h to an input signal x.

  This operation is performed for each element along a given axis using FFTs


  Parameters
  ----------
  x : jnp.ndarray
      Input signal
  h : jnp.ndarray
      Filter coefficients
  axis : int, optional
      Axis along which to filter, by default -1


  Returns
  -------
  jnp.ndarray
      Filtered signal
  """
  # Do a multiplication in the frequency domain
  nfft = x.shape[axis] + h.shape[axis] - 1
  x_fft = jnp.fft.fft(x, axis=axis, n=nfft)
  h_fft = jnp.fft.fft(h, axis=axis, n=nfft)
  y_fft = x_fft * h_fft

  # Transform back to the time domain
  y = jnp.fft.ifft(y_fft, axis=axis)
  return y


def process_doppler(range_pulse: jnp.ndarray,
                    nfft: Optional[int] = None,
                    axis: int = 1
                    ) -> jnp.ndarray:
  """
  Perform doppler processing on a range-pulse plot by computing a DFT across slow time  
  Parameters
  ----------
  range_pulse : jnp.ndarray
      Range-pulse map, where column i is the matched filter output for pulse i
  nfft : Optional[int], optional
      Number of doppler DFT points. If none, this is equal to the size of the range pulse plot along the given axis, by default None
  axis : int, optional
      Axis along which to perform doppler processing, by default 1  

  Returns
  -------
  jnp.ndarray
    Range-dopper map    
  """
  rdm = jnp.fft.fftshift(jnp.fft.fft(
      range_pulse, n=nfft, axis=axis), axes=axis)
  return rdm


if __name__ == '__main__':
  # Create the waveform and matched filter
  samp_rate = 50e6
  pw = 10e-6
  bw = samp_rate / 2
  start_freq = -bw / 2
  np = 512
  x = lfm(bandwidth=bw,
          pulsewidth=pw,
          samp_rate=samp_rate,
          start_freq=start_freq,).reshape((-1, 1))
  h = jnp.flipud(jnp.conjugate(x))

  # Simulate noisy pulses with zero delay/doppler
  x = x.repeat(np, axis=1)
  noise = jax.random.normal(jax.random.PRNGKey(
      0), x.shape) + 1j * jax.random.normal(jax.random.PRNGKey(0), x.shape)
  x = x + 1e0*noise

  # Do pulse-doppler processing
  y = filter(x, h, axis=0)
  rdm = process_doppler(y, nfft=2*np)
  rdm = rdm.at[jnp.abs(rdm) < 10**(-80/20)].set(10**(-80/20))

  plt.figure()
  plt.plot(x[:, 0].real)
  plt.plot(x[:, 0].imag)
  plt.figure()
  plt.plot(20*jnp.log10(jnp.abs(y)))
  plt.figure()
  plt.imshow(20*jnp.log10(jnp.abs(rdm)), aspect='auto')
  plt.clim([0, 80])
  plt.colorbar()

  plt.show()
