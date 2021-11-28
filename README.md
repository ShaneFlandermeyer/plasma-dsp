# plasma-dsp

A free and open-source C++ signal processing library primarily for generating
and analyzing RF waveforms.

## Modules and Features

### Waveforms

- Square wave
- Linear FM

### Windows

- Rectangular
- Blackman
- Hamming
- Hanning

### Signal Processing

- FFT (including fftshift/ifftshift)
- Spectrogram

## Dependencies

- [FFTW3](https://www.fftw.org/)
- [Matplot++](https://alandefreitas.github.io/matplotplusplus/)

When the tool is more mature, I plan on dropping the Matplot++ dependency.

## Installation

The easiest way to use this tool is to obtain the source code from git

  <https://github.com/ShaneFlandermeyer/waveform.git>

There is currently no way to install the tool.

## Wishlist

- A matrix class
- Phase coded waveforms
- CMake installation option
  