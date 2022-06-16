# plasma_dsp

plasma_dsp is a radar signal processing library written in C++. It is primarily
useful for generating radar waveforms, although it has some algorithm
implementations that have not yet been optimized. To support experimentation on
software-defined radio platforms, a GNU Radio module using plasma can also be
found [here](https://github.com/ShaneFlandermeyer/gr-plasma).

## Modules and Features

### Waveforms

Several objects have been implemented to generate common radar waveforms. A list
of waveforms that can be generated is given below:

- Linear FM (LFM)
- FMCW
  - Linear upsweep and downsweep
- Polyphase-coded FM
  - 

- Frequency modulated continuous wave (FMCW)
  - Linear upsweep
  - Linear downsweep
- Linear frequency modulated (LFM)
- [Polyphase coded frequency modulated (PCFM)](https://ieeexplore.ieee.org/document/6965769)
- Phase codes
  - Barker
  - Frank
- Square wave

### Windows

- Rectangular
- Blackman
- Hamming
- Hanning

### Signal Processing

- FFT/IFFT
- 1D Constant False Alarm Rate (CFAR) detector
  - Cell averaging (CA)
- 2D CFAR detector
  - Cell averaging (CA)


## Dependencies

- C++20
- [Eigen v3.4](https://gitlab.com/libeigen/eigen/-/tree/3.4)
- [FFTW3](https://www.fftw.org/)
- [OpenMP](https://www.openmp.org/)

On an Ubuntu 22.04 system, these dependencies can be installed by running the
following command as root:

```bash
apt install libeigen3-dev fftw-dev libomp-dev
```

**NOTE:** I am working on removing the C++20 dependency. It is currently used to
generate the PCFM waveforms.

## Installation

The easiest way to use this tool is to obtain the source code from git

```bash
git clone https://github.com/ShaneFlandermeyer/plasma_dsp.git
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
sudo ldconfig
```