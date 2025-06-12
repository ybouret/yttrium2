#include "y/container/sequence/list.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace {

    template <typename LIST> static inline
    void showList( LIST &list )
    {
        std::cerr << "capacity = " << list.capacity() << std::endl;
        std::cerr << "size     = " << list.size() << std::endl;
        std::cerr << "list     = " << list << std::endl;
    }

}

Y_UTEST(sequence_list)
{

    List<int> l;
    l.reserve(2);
    showList(l);
    l.pushTail(2);
    l.pushTail(3);
    l.pushTail(4);
    showList(l);


}
Y_UDONE()

