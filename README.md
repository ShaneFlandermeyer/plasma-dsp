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

All other dependencies in this project are currently managed through
[conan](https://conan.io/), which can be installed through pip

```bash
pip install conan
```

## Installation

The easiest way to use this tool is to obtain the source code from git

```bash
git clone https://github.com/ShaneFlandermeyer/plasma_dsp.git
```

There are two ways that Plasma DSP can be installed: as a Conan package and as a
traditional system-wide install. The following command installs it as a Conan
package, which is necessary for the companion
[gr-plasma](git@github.com:ShaneFlandermeyer/gr-plasma.git) GNU Radio module.

```bash
conan create . -s compiler.libcxx=libstdc++11
```

To install the tool system-wide (for non-conan projects), run the commands below
from the top-level CMake directory:

```bash
mkdir -p build
cd build
conan install ..
cmake ..
make
sudo make install
sudo ldconfig
```

To uninstall, run the following from the build folder

```bash
sudo make uninstall
sudo ldconfig
```
