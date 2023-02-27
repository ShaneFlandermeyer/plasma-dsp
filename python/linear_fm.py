import jax.numpy as jnp
import matplotlib.pyplot as plt


def lfm(bandwidth: float,
        pulsewidth: float,
        samp_rate: float,
        start_freq: float,
        prf: float = None,
        ) -> jnp.ndarray:
  """
  Generate a linear frequency modulated (LFM) waveform.

  Parameters
  ----------
  bandwidth : float
      Sweep bandwidth (Hz)
  pulsewidth : float
      Pulse duration (s)
  samp_rate : float
      Sample rate (samples/s)
  start_freq : float
      Starting frequency of the sweep(Hz)
  prf : float, optional
      Pulse repetition frequency (PRF). If this is None, only the nonzero waveform samples are returned, by default None

  Returns
  -------
  jnp.ndarray
      Waveform samples
  """
  # Create the base waveform
  ts = 1.0 / samp_rate
  n_samp_pulse = int(jnp.round(pulsewidth * samp_rate))
  t = jnp.arange(0, n_samp_pulse) * ts
  phase = 2 * jnp.pi * (start_freq * t + bandwidth / (2*pulsewidth) * t**2)
  x = jnp.exp(1j * phase)
  # If no PRF is requested, return the base waveform
  if not prf:
    return x

  # Zero pad to the PRF
  n_samp_pri = int(jnp.round(samp_rate / prf))
  return jnp.pad(x,
                 pad_width=(0, n_samp_pri - n_samp_pulse),
                 mode='constant', constant_values=0)