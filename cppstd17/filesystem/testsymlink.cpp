#include "symlink.hpp"

int main()
{
    std::filesystem::path p{"."};
    testSymLink(p);
    return 0;
}