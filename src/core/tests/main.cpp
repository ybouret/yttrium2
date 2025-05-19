#include <iostream>
#include "y/system/platform.hpp"
#include "y/system/compiler.hpp"
#include "y/core/variadic.hpp"

using namespace Yttrium;

int main()
{
    std::cerr << "Plaftorm = " << Y_Platform << std::endl;
    std::cerr << "Compiler = " << Y_Compiler << std::endl;
    char buf[4];
    memset(buf,0,sizeof(buf));
    const int res = Core::Variadic::Sprintf(buf, sizeof(buf), "%s", "Hello");
    std::cerr << buf << ", res=" << res << std::endl;
    return 0;
}
