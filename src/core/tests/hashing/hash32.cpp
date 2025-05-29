
#include "y/hashing/ibj32.hpp"
#include "y/core/linked/list/cxx.hpp"
//#include "y/hexadecimal.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

    class Node
    {
    public:
        typedef CxxListOf<Node> List;

        inline Node(const size_t i) noexcept :
        indx(i),
        hkey( Hashing::IBJ32(uint32_t(i)) ),
        next(0),
        prev(0)
        {
        }

        Node(const Node &_) noexcept :
        indx(_.indx),
        hkey(_.hkey),
        next(0),
        prev(0)
        {

        }

        const size_t indx;
        const size_t hkey;
        Node *       next;
        Node *       prev;

    private:
        Y_Disable_Assign(Node);
    };

    template <unsigned p, unsigned q>
    inline void testHash32()
    {
        static const size_t _1        = 1;
        static const size_t TableSize = _1 << p;
        static const size_t TableMask = TableSize-1;
        static const size_t ItemCount = _1 << q;

        Node::List Table[TableSize];

        for(size_t i=0;i<ItemCount;++i)
        {
            Node * const node = new Node(i);
            Table[node->hkey&TableMask].pushTail(node);
        }

    }
}

Y_UTEST(hashing_hash32)
{


    testHash32<5,10>();

}
Y_UDONE()
