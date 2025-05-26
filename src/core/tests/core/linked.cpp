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

        static inline SignType Compare(const Node * const lhs, const Node * const rhs) noexcept
        {
            assert(0!=lhs);
            assert(0!=rhs);
            return Sign::Of(lhs->value,rhs->value);
        }

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
        std::cerr << "CoreList" << std::endl;
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
        std::cerr << "CxxList" << std::endl;
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
        std::cerr << "CloneableList..." << std::endl;
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

    {
        std::cerr << "Merging..." << std::endl;
        CxxListOf<Node> lhs;
        CxxListOf<Node> rhs;

        for(size_t nl=0;nl<=5;++nl)
        {
            for(size_t nr=0;nr<=5;++nr)
            {
                lhs.release();
                rhs.release();
                for(size_t i=0;i<nl;++i) lhs.pushTail( new Node() );
                for(size_t i=0;i<nr;++i) rhs.pushTail( new Node() );
                std::cerr << lhs << " <-" << rhs << " : ";
                Y_ASSERT(nl==lhs.size);
                Y_ASSERT(nr==rhs.size);
                lhs.mergeTail(rhs);
                Y_ASSERT(0==rhs.size);
                Y_ASSERT(nl+nr==lhs.size);
                std::cerr << lhs << std::endl;
            }
        }

    }

    {
        std::cerr << "Sorting..." << std::endl;
        CxxListOf<Node> list;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            if( ran.choice() ) list.pushTail( new Node() ); else list.pushHead( new Node() );
        }
        std::cerr << list << std::endl;
        list.sort(Node::Compare);
        std::cerr << list << std::endl;
    }

    {
        std::cerr << "Pop" << std::endl;
        CxxListOf<Node> list;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            if( ran.choice() ) list.pushTail( new Node() ); else list.pushHead( new Node() );
        }
        std::cerr << list << std::endl;
        delete list.pop( list.head );
        std::cerr << list << std::endl;
        delete list.pop( list.tail );
        std::cerr << list << std::endl;
        while( list.size > 0 )
        {
            delete list.pop( list[ ran.in(list.size) ] );
            std::cerr << list << std::endl;
        }

    }

    {
        std::cerr << "Insert After" << std::endl;
        CxxListOf<Node> list;
        list.pushHead( new Node() );
        std::cerr << list << std::endl;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            list.insertAfter( list[ ran.in(list.size) ], new Node() );
            std::cerr << list << std::endl;
        }
    }

    {
        std::cerr << "Insert Before" << std::endl;
        CxxListOf<Node> list;
        list.pushHead( new Node() );
        std::cerr << list << std::endl;
        for(size_t i=10+ran.leq(10);i>0;--i)
        {
            list.insertBefore( list[ ran.in(list.size) ], new Node() );
            std::cerr << list << std::endl;
        }
    }

    {
        std::cerr << "Towards Head" << std::endl;
        for(size_t n=1;n<=10;++n)
        {
            CxxListOf<Node> list;
            for(size_t i=n;i>0;--i)
            {
                list.pushTail( new Node() );
            }
            Y_ASSERT(n==list.size);
            std::cerr << list << std::endl;
            for(size_t i=1;i<=n;++i)
            {
                list.towardsHead( list[i] );
                std::cerr << "\t" << list << std::endl;
            }
        }
    }




}
Y_UDONE()

