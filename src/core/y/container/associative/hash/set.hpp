

#ifndef Y_Associative_HashSet_Included
#define Y_Associative_HashSet_Included 1

#include "y/container/associative.hpp"
#include "y/container/htable.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/threading/multi-threaded-object.hpp"

namespace Yttrium
{
    struct HashSetAPI
    {
        typedef HTable::Node Node;

        template <typename KEY, typename T>
        class Knot
        {
        public:
            Y_Args_Declare(T,Type);
            Y_Args_Declare(KEY,Key);
            typedef Protean::WarpedCacheOf<Knot,MultiThreadedObject> Pool;
            typedef Core::ListOf<Knot>                               List;

            inline  Knot(ParamType    v,
                         const size_t h) :
            data(v),
            hkey(h),
            next(0),
            prev(0)
            { }

            inline  Knot(const Knot &knot) :
            data(knot.data),
            hkey(key),
            next(0),
            prev(0)
            {}

            inline ~Knot() noexcept {}

            ConstKey & key() const noexcept { return data.key(); }

            Type         data;
            const size_t hkey;
            Knot *       next;
            Knot *       prev;

        private:
            Y_Disable_Assign(Knot);
        };
    };

    template <
    typename KEY,
    typename T,
    typename KEY_HASHER>
    class HashSet
    {
    public:
        Y_Args_Declare(T,Type);
        Y_Args_Declare(KEY,Key);
        typedef typename HashSetAPI::Node        Node;
        typedef typename HashSetAPI::Knot<KEY,T> Knot;
        typedef typename Knot::Pool              KPool;
        typedef typename Knot::List              KList;

        inline explicit HashSet() : table(), list(), pool()
        {
        }

        inline virtual ~HashSet() noexcept
        {
            //purge();
        }

        inline virtual void free()    noexcept { clear(); }
        inline virtual void release() noexcept { purge(); }

#if 0 
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
#endif



    private:
        HTable     table;
        KList      list;
        KPool      pool;
        KEY_HASHER hash;
        
        Y_Disable_Copy_And_Assign(HashSet);

        inline void clear() noexcept {
            table.free();
            while(list.size) pool.banish( list.popTail() );
        }

        inline void purge() noexcept
        {
            table.free();
            while(list.size) pool.remove( list.popTail() );
        }

    };

}

#endif
