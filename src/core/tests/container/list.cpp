#include "y/container/sequence/list.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace {

    template <typename LIST> static inline
    void showList( LIST &list )
    {
        std::cerr << "capacity=" << list.capacity() << std::endl;
    }

}

Y_UTEST(sequence_list)
{

    List<int> l;
    l.reserve(10);
    showList(l);

}
Y_UDONE()

