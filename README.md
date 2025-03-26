# Handy

Heterogeneous pieces of code that come in handy.

Growing organically, it is composed of several modules:
* `handy`: Miscellaneous low-level types and operations, ranging from *hashes* and *bitmasks* to *string utilities* and *pools*.
* `platform`: Platform abstraction (system paths, locale, gui).
* `resource`: Prototype of a generic `ResourceManager` and related utilities.

## Build (with Conan 2)

* Ensure [the pre-requisites](https://github.com/ShredEagle/public_build_info?tab=readme-ov-file#requirements) are met.
* Clone:
    ```bash
    git clone --recurse-submodule https://github.com/ShredEagle/handy.git
    cd handy
    ```
* Build:
    ```bash
    conan build ./conan/
    ```

## Build System and Dependencies

The project uses CMake for its build scripts, which is sufficient for building the project.
However, CMake does not manage upstream dependencies.

To address this, a Conan recipe is provided on top of the CMake scripts.
It handles dependency management and facilitates the integration inside a dependency graph.
