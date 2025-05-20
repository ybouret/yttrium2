#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/core/variadic.hpp"
#include "y/core/setup.hpp"
#include "y/exception.hpp"
#include "y/utest/driver.hpp"
#include <cstring>
#include <iostream>

Y_UTEST_DECL(32)
{
    Y_UTEST(exception);
    Y_UTEST(core_variadic);
    
    Y_UTEST(system_error);
    Y_UTEST(system_at_exit);

    Y_UTEST(calculus_integer_log2);
}
Y_UTEST_EXEC()

