# plasma-dsp

A free and open-source C++ signal processing library primarily for generating
and analyzing RF waveforms.

## Modules and Features

### Waveforms

- Barker Codes
- Linear FM
- Square wave


### Windows

- Rectangular
- Blackman
- Hamming
- Hanning

### Signal Processing

- FFT (including fftshift/ifftshift)
- Spectrogram

## Dependencies

- [Eigen](https://eigen.tuxfamily.org/)
- [FFTW3](https://www.fftw.org/)
- [Matplot++](https://alandefreitas.github.io/matplotplusplus/)

When the tool is more mature, I might make the Matplot++ dependency optional.

## Installation

The easiest way to use this tool is to obtain the source code from git

  <https://github.com/ShaneFlandermeyer/plasma-dsp>

There is currently no way to install the tool system-wide.

## Wishlist

- CMake system installation option
- FMCW waveforms
- PCFM
