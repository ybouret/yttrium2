
#include "y/utest/run.hpp"
#include "y/system/at-exit.hpp"
#include <cassert>

using namespace Yttrium;

namespace
{
    static int a = 1;
    static int b = 2;

    static void todo(void *args)
    {
        Y_CHECK( 0 != args );
        std::cerr << "todo: " << *(int *)args << std::endl;
    }

}

Y_UTEST(system_at_exit)
{

    System::AtExit::Perform(todo,&a,0x04);
    System::AtExit::Perform(todo,&b,0x02);

}
Y_UDONE()

