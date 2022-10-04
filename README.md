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

Most of the heavy signal processing lifting is handled by
[ArrayFire](https://arrayfire.com/), which can be installed through apt by
running the following

```bash
wget https://repo.arrayfire.com/GPG-PUB-KEY-ARRAYFIRE-2020.PUB
gpg --no-default-keyring --keyring ./temp-keyring.gpg --import GPG-PUB-KEY-ARRAYFIRE-2020.PUB
gpg --no-default-keyring --keyring ./temp-keyring.gpg --export --output arrayfire.gpg
rm temp-keyring.gpg
sudo mkdir -p /etc/apt/keyrings/
sudo mv arrayfire.gpg /etc/apt/keyrings/arrayfire.gpg
echo "deb [signed-by=/etc/apt/keyrings/arrayfire.gpg, arch=amd64] https://repo.arrayfire.com/debian all main" | sudo tee -a /etc/apt/sources.list.d/arrayfire.list
sudo apt update
sudo apt install arrayfire
```

If this process fails, you can choose an installation method from the [official
repository](https://github.com/arrayfire/arrayfire/wiki/Getting-ArrayFire)

[GoogleTest](https://github.com/google/googletest) is also a dependency, but it
is installed through a FetchContent call if it is not found.

## Installation

The easiest way to use this tool is to obtain the source code from git

```bash
git clone https://github.com/ShaneFlandermeyer/plasma_dsp.git
```


To install the tool system-wide, run the commands below
from the top-level CMake directory:

```bash
mkdir -p build
cd build
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

## Python Usage
Although no Python bindings have been explicitly written for this project,
[cppyy](https://cppyy.readthedocs.io/en/latest/index.html) has been tested and
works for all objects. Below is a minimal working example for generating a
waveform, converting the data to a numpy array, and plotting

```python
import cppyy
import cppyy.gbl.std as std
import numpy as np
import matplotlib.pyplot as plt

# Load the library and any headers you want to use in Python
cppyy.load_library('libplasma_dsp')
cppyy.include('plasma_dsp/linear_fm_waveform.h')


# Generate the waveform data
waveform = cppyy.gbl.plasma.LinearFMWaveform(10e6, 10e-6, 10e3, 20e6)
samps = waveform.sample()
x = std.vector[std.complex['double']](samps.elements())
samps.host(x.data())
x = np.array(list(x),dtype=np.complex128)

# Plot for verification
plt.plot(np.real(x))
plt.show()
```
## Publications and Presentations
- https://pubs.gnuradio.org/index.php/grcon/article/view/121
- https://events.gnuradio.org/event/18/contributions/253/
