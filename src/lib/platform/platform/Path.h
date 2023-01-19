#pragma once


#include "Filesystem.h"


namespace ad {
namespace platform {


filesystem::path getExecutableFilePath();


inline filesystem::path getExecutableFileDirectory()
{
    return getExecutableFilePath().parent_path();
}


} // namespace platform
} // namespace ad
