
#include "y/hashing/ibj32.hpp"
#include "y/check/crc32.hpp"
#include "y/check/sfh32.hpp"

#include "y/core/linked/list/cxx.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

    template <
    typename      HASH32,
    const uint32_t INIT32
    >
    struct Hash32
    {
        template <typename T> static
        inline size_t Key(const T &args) noexcept
        {
            uint32_t h = INIT32;
            return HASH32::Run(h,&args,sizeof(T));
        }
    };

    class Node
    {
    public:
        typedef CxxListOf<Node> List;

        inline Node(const size_t i) noexcept :
        indx(i),
        next(0),
        prev(0)
        {
        }

        Node(const Node &_) noexcept :
        indx(_.indx),
        next(0),
        prev(0)
        {

        }

        static inline
        SignType Compare(const Node * const lhs, const Node * rhs) noexcept
        {
            return Sign::Of(lhs->indx,rhs->indx);
        }

        const size_t indx;
        Node *       next;
        Node *       prev;

    private:
        Y_Disable_Assign(Node);
    };

    template <
    unsigned p,
    unsigned q,
    size_t   delta>
    struct TestHash32
    {
        template <typename HASH>
        static inline void With(HASH &hash)
        {
            static const size_t _1        = 1;
            static const size_t TableSize = _1 << p;
            static const size_t TableMask = TableSize-1;
            static const size_t ItemCount = _1 << q;

            std::cerr << "Setting " << ItemCount << "/" << delta << " in " << TableSize << " slots" << std::endl;
            Node::List Table[TableSize];

            for(size_t i=delta;i<=ItemCount;i += delta)
            {
                Node * const node = new Node(i);
                Table[ hash(node->indx) & TableMask ].pushTail(node);
            }

            for(size_t i=0;i<TableSize;++i)
            {
                Node::List &slot = Table[i];
                slot.sort(Node::Compare);
                std::cerr << "[" << std::setw(4) << i << "]";
                std::cerr << "#" << std::setw(5) << slot.size << " |";
                for(const Node *node=slot.head;node;node=node->next)
                {
                    std::cerr << " " << node->indx;
                }
                std::cerr << std::endl;
            }

        }
    };


    static inline size_t UsingIBJ32(const size_t x)
    {
        return Hashing::IBJ32(uint16_t(x));
    }

    static inline size_t UsingCRC32(const size_t x)
    {
        const uint16_t xx = uint16_t(x);
        const size_t ans = Hash32<CRC32,0x0>::Key(xx);
        return ans;
    }

    static inline size_t UsingSFH32(const size_t x)
    {
        const uint16_t xx = uint16_t(x);
        const size_t ans = Hash32<SFH32,0xaaaaaaaa>::Key(xx);
        return ans;
    }

}

Y_UTEST(hashing_hash32)
{
    //TestHash32<5,8,2>::With(UsingIBJ32);
    //TestHash32<5,8,2>::With(UsingSFH32);
    TestHash32<5,9,1>::With(UsingCRC32);

}
Y_UDONE()
