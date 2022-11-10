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
        "gtk_dialog": [True, False],
    }
    default_options = {
        "shared": False,
        "build_tests": False,
        "gtk_dialog": False
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

    def requirements(self):
        if self.options.gtk_dialog:
            #Gtk version should also be set using -o gtk:version=x
            self.requires("gtk/system")


    python_requires="shred_conan_base/0.0.5@adnn/stable"
    python_requires_extend="shred_conan_base.ShredBaseConanFile"
