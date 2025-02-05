#include <handy/vector_utils.h>
#include <vector>

#include <cstdlib>


int main()
{
    // TODO test filesystem and resources too
    std::vector<int> aVector;
    ad::getStoredSize(aVector);
    return EXIT_SUCCESS;
}
