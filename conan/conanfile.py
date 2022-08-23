from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout

from os import path


class Handy(ConanFile):
    name = "handy"
    license = "MIT"
    author = "adnn"
    url = "https://github.com/ShredEagle/handy"
    description = "Handy classes and functions"
    topics = ("utils")
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "build_tests": [True, False],
    }
    default_options = {
        "shared": False,
        "build_tests": False,
    }

    #requires = ()

    build_policy = "missing"
    generators = "CMakeDeps", "CMakeToolchain"

    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto",
        "submodule": "recursive",
    }


    python_requires="shred_conan_base/0.0.3@adnn/stable"
    python_requires_extend="shred_conan_base.ShredBaseConanFile"
