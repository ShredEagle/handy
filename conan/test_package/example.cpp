#include <handy/vector_utils.h>
#include <platform/Path.h>
#include <resource/ResourceFinder.h>

#include <vector>

#include <cstdlib>


int main()
{
    // handy lib
    std::vector<int> aVector;
    ad::getStoredSize(aVector);

    // platform lib
    std::filesystem::path exePath = ad::platform::getExecutableFilePath();

    // resource lib
    ad::resource::ResourceFinder finder{ {exePath,} };

    return EXIT_SUCCESS;
}
