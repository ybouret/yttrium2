
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_school_of)
{

    Memory::SchoolOf<int>  data(10);
    Memory::Operating<int> op(data.entry,data.count);
    


}
Y_UDONE()

