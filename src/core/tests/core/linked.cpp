#include "y/core/linked/pool/cxx.hpp"
#include "y/core/linked/pool/raw.hpp"
#include "y/core/linked/list/cloneable.hpp"
#include "y/core/linked/list/cxx.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class Node
    {
    public:
        static int Count;

        explicit Node() noexcept :
        next(0),
        prev(0),
        value(Count)
        {
            ++Count;
        }

        virtual ~Node() noexcept
        {
            --Count;
        }

        Node(const Node &node) noexcept :
        next(0), prev(0), value(node.value)
        {
            ++Count;
        }

        Node * clone() const
        {
            return new Node(*this);
        }

        const int & operator*() const noexcept { return value; }

        Node *next;
        Node *prev;
        const int value;

    private:
        Y_Disable_Assign(Node);
    };

    int Node:: Count = 0;
}

Y_UTEST(core_linked)
{
    
    System::Rand ran;

    std::cerr << "Pool" << std::endl;
    {
        Core::PoolOf<Node> pool;

        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            if( ran.choice() )  pool.store( new Node() ); else pool.stash( new Node() );
            std::cerr << pool << std::endl;
        }

        while(pool.size>0)
        {
            delete pool.query();
            std::cerr << pool << std::endl;
        }

        Y_CHECK(0==Node::Count);
    }

    std::cerr << "CxxPool" << std::endl;
    {
        CxxPoolOf<Node> pool;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            pool.store( new Node() );
        }
        std::cerr << pool << std::endl;

        CxxPoolOf<Node> lhs, rhs;
        pool.split(lhs,rhs);
        std::cerr << "lhs=" << lhs << std::endl;
        std::cerr << "rhs=" << rhs << std::endl;

    }

    {
        Core::ListOf<Node> list;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            if( ran.choice() ) list.pushTail( new Node() ); else list.pushHead( new Node() );
            std::cerr << list << std::endl;
        }

        while(list.size>0)
        {
            delete (ran.choice() ? list.popTail() : list.popHead());
            std::cerr << list << std::endl;
        }

    }

    {
        CxxListOf<Node> list;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            if( ran.choice() ) list.pushTail( new Node() ); else list.pushHead( new Node() );
            std::cerr << list << std::endl;
        }

        {
            CxxListOf<Node> copy(list);
            copy.release();
        }


    }

    {
        ListOfCloneable<Node> list;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            if( ran.choice() ) list.pushTail( new Node() ); else list.pushHead( new Node() );
            std::cerr << list << std::endl;
        }

        {
            ListOfCloneable<Node> copy(list);
            copy.release();
        }

    }


}
Y_UDONE()

