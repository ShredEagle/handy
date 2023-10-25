#include "Path.h"


namespace ad {
namespace platform {


filesystem::path getExecutableFilePath()
{
    //see: https://stackoverflow.com/a/1528493/1027706
    return filesystem::canonical("/proc/self/exe");
}


} // namespace platform
} // namespace ad
