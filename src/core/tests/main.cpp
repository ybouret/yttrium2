#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/core/variadic.hpp"
#include "y/core/setup.hpp"
#include <cstring>
#include <iostream>

using namespace Yttrium;

extern void testError();

int main()
{
    std::cerr << "Plaftorm = " << Y_Platform << std::endl;
    std::cerr << "Compiler = " << Y_Compiler << std::endl;
    char buf[4];
    memset(buf,0,sizeof(buf));
    const int res = Core::Variadic::Sprintf(buf, sizeof(buf), "%s", "Hello");
    std::cerr << buf << ", res=" << res << std::endl;

    testError();
    return 0;
}
