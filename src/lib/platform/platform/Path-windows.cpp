#include "Path.h"


namespace ad {
namespace platform {


filesystem::path getExecutableFilePath()
{
    char * programPath;
    _get_pgmptr(&programPath);
    return programPath;
}


} // namespace platform
} // namespace ad