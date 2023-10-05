#pragma once

#include "Filesystem.h" // IWYU pragma: export

namespace ad {
namespace platform {


filesystem::path getExecutableFilePath();


inline filesystem::path getExecutableFileDirectory()
{
    return getExecutableFilePath().parent_path();
}


} // namespace platform
} // namespace ad
