
#include "y/container/associative.hpp"
#include "y/container/tree/suffix.hpp"
#include "y/container/htable.hpp"

#include "y/utest/run.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"

#include "y/string.hpp"

namespace Yttrium
{

    typedef SingleThreadedClass AssociativeThreading;

    struct SuffixSetAPI
    {
        typedef SuffixTree::Node Node;

        template <typename KEY, typename T>
        class Knot
        {
        public:
            Y_Args_Declare(T,Type);
            Y_Args_Declare(KEY,Key);
            typedef Protean::WarpedCacheOf<Knot,AssociativeThreading> Pool;
            typedef Core::ListOf<Knot> List;

            inline Knot(ParamType arg) :
            data(arg),
            node(0),
            next(0),
            prev(0)
            {
            }

            inline Knot(const Knot &knot) :
            data(knot.data),
            node(0),
            next(0),
            prev(0)
            {
            }


            inline ~Knot() noexcept
            {}

            ConstKey & key() const noexcept { return data.key(); }

            Type   data;
            Node * node;
            Knot * next;
            Knot * prev;

        private:
            Y_Disable_Assign(Knot);
        };
    };

    template <typename KEY, typename T>
    class SuffixSet
    {
    public:
        Y_Args_Declare(T,Type);
        Y_Args_Declare(KEY,Key);
        typedef typename SuffixSetAPI::Node        Node;
        typedef typename SuffixSetAPI::Knot<KEY,T> Knot;
        typedef typename Knot::Pool                KPool;
        typedef typename Knot::List                KList;

        inline explicit SuffixSet() : tree(), list(), pool()
        {
        }

        inline virtual ~SuffixSet() noexcept
        {
            purge();
        }

        inline bool insert(ParamType value)
        {
            Knot * const knot = pool.summon(value);
            try {
                ConstKey &   key  = knot->key();
                Node * const node = tree.insert(key.begin(), key.size(), knot);
                if(!node) { pool.banish(knot); return false; }
                list.pushTail(knot)->node = node;
                assert(tree.size == list.size);
                return true;
            }
            catch(...)
            {
                pool.banish(knot); throw;
            }
            return false;
        }

        inline bool remove(ParamKey key) noexcept
        {
            Node * node = tree.search(key.begin(),key.size());

        }


    private:
        SuffixTree tree;
        KList      list;
        KPool      pool;

        Y_Disable_Copy_And_Assign(SuffixSet);

        inline void clear() noexcept {
            tree.free();
            while(list.size) pool.banish( list.popTail() );
        }

        inline void purge() noexcept
        {
            tree.release();
            while(list.size) pool.remove( list.popTail() );
        }

    };




}

using namespace Yttrium;

namespace
{
    class Dummy : public CountedObject
    {
    public:
        explicit Dummy(const char * const id) :
        CountedObject(),
        name(id)
        {

        }

        Dummy(const Dummy &other) :
        CountedObject(), name(other.name)
        {
        }

        virtual ~Dummy() noexcept
        {
        }

        const String & key() const noexcept { return name; }

        const String name;

    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_associative)
{

    {
        typedef SuffixSetAPI::Knot<String,Dummy> Knot;
        typedef Knot::Pool  KPool;

        const Dummy dum1("dum1");

        KPool  kpool;
        Knot * knot = kpool.summon(dum1);
        std::cerr << "knot: " << knot->key() << std::endl;
        Knot * kcpy = kpool.mirror(knot);
        std::cerr << "kcpy: " << knot->key() << std::endl;

        kpool.banish(knot);
        kpool.remove(kcpy);
    }

    {
        SuffixSet<String,Dummy> set;
        const Dummy dum1("dum1");
        Y_ASSERT(set.insert(dum1));
        Y_ASSERT(!set.insert(dum1));

    }

}
Y_UDONE()

