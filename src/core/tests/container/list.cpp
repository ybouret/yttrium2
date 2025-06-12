#include "y/container/sequence/list.hpp"
#include "y/utest/run.hpp"
#include "y/core/display.hpp"

using namespace Yttrium;

namespace {

    template <typename LIST> static inline
    void showList( LIST &list )
    {
        std::cerr << "capacity = " << list.capacity() << std::endl;
        std::cerr << "size     = " << list.size() << std::endl;
        std::cerr << "list     = " << list << std::endl;
        Core::Display(std::cerr,list.begin(),list.size()) << std::endl;
        Core::Display(std::cerr,list.rbegin(),list.size()) << std::endl;

        const LIST &lcst = list;
        Core::Display(std::cerr,lcst.begin(),lcst.size()) << std::endl;
        Core::Display(std::cerr,lcst.rbegin(),lcst.size()) << std::endl;

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

