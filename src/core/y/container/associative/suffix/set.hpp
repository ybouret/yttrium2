
#ifndef Y_Associative_SuffixSet_Included
#define Y_Associative_SuffixSet_Included 1

#include "y/container/associative/glossary.hpp"
#include "y/container/tree/suffix.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"

namespace Yttrium
{
    struct SuffixSetAPI
    {
        typedef SuffixTree::Node Node;

        template <typename KEY, typename T>
        class Knot
        {
        public:
            Y_Args_Declare(T,Type);
            Y_Args_Declare(KEY,Key);
            typedef Protean::WarpedCacheOf<Knot,SingleThreadedClass> Pool;
            typedef Core::ListOf<Knot> List;

            inline  Knot(ParamType arg) : data(arg), next(0), prev(0) { }
            inline  Knot(const Knot &knot) : data(knot.data), next(0), prev(0) {}
            inline ~Knot() noexcept {}

            ConstKey & key() const noexcept { return data.key(); }

            Type   data;
            Knot * next;
            Knot * prev;

        private:
            Y_Disable_Assign(Knot);
        };
    };

    template <typename KEY, typename T>
    class SuffixSet : public Glossary<KEY,T>
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

        inline virtual void free()    noexcept { clear(); }
        inline virtual void release() noexcept { purge(); }


        inline bool insert(ParamType value)
        {
            Knot * const knot = pool.summon(value);
            try {
                ConstKey &   key  = knot->key();
                Node * const node = tree.insert(key.begin(), key.size(), knot);
                if(!node) { pool.banish(knot); return false; }
                list.pushTail(knot);
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
            void * const addr = tree.remove(key.begin(),key.size());
            if(!addr) return false;
            pool.banish( list.pop(static_cast<Knot *>(addr)) );
            assert(tree.size == list.size);
            return true;
        }

        inline ConstType * search(ParamKey key) const noexcept
        {
            const Node * const node = tree.search( key.begin(), key.size() );
            if(!node) return 0;
            assert(0!=node->addr);
            return static_cast<ConstType *>(node->addr);
        }

        inline  Type * search(ParamKey key) noexcept
        {
            Node * const node = tree.search( key.begin(), key.size() );
            if(!node) return 0;
            assert(0!=node->addr);
            return static_cast<Type *>(node->addr);
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

#endif
