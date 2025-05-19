#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/core/variadic.hpp"
#include "y/core/setup.hpp"
#include "y/exception.hpp"
#include "y/utest/driver.hpp"
#include <cstring>
#include <iostream>

Y_UTEST_DECL(4)
{
    Y_UTEST(error);
}
Y_UTEST_EXEC()


#if 0
using namespace Yttrium;

extern void testError();

int main(int argc, char **argv)
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

    UTest::Driver<4> driver;

    {
        extern int Y_UTest_error(int,char **);
        UTest::CFunction   call =  Y_UTest_error;
        const char * const name = "error";
        driver(call,name);
    }

    driver(argc,argv);

    return 0;
}

#endif
