from conans import ConanFile, CMake
import os

class PlasmaConan(ConanFile):
    scm = {
      "type": "git",
      "subfolder": "plasma-dsp",
      "url": "auto",
      "revision": "auto",
      "password": os.environ.get("SECRET", None)
    }
    name = "plasma_dsp"
    version = "0.1"
    # url = "<Package recipe repository url here, for issues about the package>"
    description = "A free and open-source C++ library for RF (mostly radar) signal processing."
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": True, "*:shared": True}
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "lib/*", "include/*", "examples/*", "test/*", "cmake/*"

    def requirements(self):
        self.requires("fftw/3.3.9")
        self.requires("eigen/3.4.0")
        
    def configure(self):
        self.options["fftw"].precision = "single"
        self.options["fftw"].threads = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["plasma_dsp"]
