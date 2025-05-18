#include <iostream>
#include "y/core/variadic.hpp"

using namespace Yttrium;

int main()
{
    char buf[4];
    memset(buf,0,sizeof(buf));
    const int res = Core::Variadic::Sprintf(buf, sizeof(buf), "%s", "Hello");
    std::cerr << buf << ", res=" << res << std::endl;
    return 0;
}
