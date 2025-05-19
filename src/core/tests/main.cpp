#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/core/variadic.hpp"
#include "y/core/setup.hpp"
#include "y/exception.hpp"
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

    Exception excp("from '%s'", Y_Platform);
    std::cerr << "sizeof(Exception)=" << sizeof(Exception) << std::endl;

    excp.show(std::cerr);

    excp.add(" and '%s'", Y_Compiler);
    excp.show(std::cerr);

    excp.pre("'%s': ", "Hello");
    excp.show(std::cerr);

    return 0;
}
