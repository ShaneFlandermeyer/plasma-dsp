# plasma-dsp

A free and open-source C++ library for RF (mostly radar) signal processing.

## Modules and Features

### Waveforms

- Frequency modulated continuous wave (FMCW)
  - Linear upsweep
  - Linear downsweep
- Linear frequency modulated (LFM)
- Phase codes
  - Barker
  - Frank
- Polyphase-coded frequency modulated (PCFM)
- Square wave

### Windows

- Rectangular
- Blackman
- Hamming
- Hanning

### Signal Processing

- 1D Constant False Alarm Rate (CFAR) detector
  - Cell averaging (CA)
- 2D CFAR detector
  - Cell averaging (CA)
- Convolution
- Finite impulse response (FIR) filters
- FFT/IFFT
- fftshift/ifftshift
- Matched filtering
- Range-doppler maps
- Spectrograms

## Dependencies

- C++20
- [Eigen](https://eigen.tuxfamily.org/)
- [FFTW3](https://www.fftw.org/)
- [Matplot++](https://alandefreitas.github.io/matplotplusplus/)

When the tool is more mature, I might make the Matplot++ dependency optional.

## Installation

The easiest way to use this tool is to obtain the source code from git

```bash
git clone https://github.com/ShaneFlandermeyer/plasma-dsp.git
```

To install the tool system-wide (currently only possible on Linux), run the
following commands from the project's base directory

```bash
cmake -S . -B build
make
sudo make install
sudo ldconfig
```

To uninstall, run the following from the build folder

```bash
sudo make uninstall
```

## Wishlist

- Eigen support for waveform generators
- Complex float option for generated waveform
- Further FMCW processing
- Separate repo for simulation tools (plasma-sim?)
- GNU Radio integration (gr-plasma)
- Make matplot++ optional (i.e., only needed to build examples)
  