#include "y/utest/run.hpp"
#include "y/core/variadic.hpp"

using namespace Yttrium;

Y_UTEST(core_variadic)
{
    char buffer[4];
    const int res = Core::Variadic::Sprintf(buffer, sizeof(buffer), "%s", "Hello");
    std::cerr << '|' << buffer << '|' << '=' << res << std::endl;
 }
Y_UDONE()
