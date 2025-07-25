

#ifndef Y_Associative_HashSet_Included
#define Y_Associative_HashSet_Included 1

#include "y/container/associative.hpp"
#include "y/container/htable.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/hashing/key/hasher.hpp"
#include "y/hashing/fnv.hpp"

namespace Yttrium
{
    struct HashSetAPI
    {
        typedef HTable::Node Node;
        typedef Hashing::FNV Function;

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
    typename KEY_HASHER = Hashing::KeyWith<HashSetAPI::Function>
    >
    class HashSet : public Associative<KEY,T>
    {
    public:
        Y_Args_Declare(T,Type);
        Y_Args_Declare(KEY,Key);
        typedef typename HashSetAPI::Node        Node;
        typedef typename HashSetAPI::Knot<KEY,T> Knot;
        typedef typename Knot::Pool              KPool;
        typedef typename Knot::List              KList;
        typedef typename KPool::Lock             Lock;
        
        inline explicit HashSet() : table(), list(), pool(), hash()
        {
        }

        inline virtual ~HashSet() noexcept
        {
            purge();
        }

        inline virtual void free()    noexcept { clear(); }
        inline virtual void release() noexcept { purge(); }

        inline bool insert(ParamType value)
        {
            ConstKey &   key  = value.key();
            const size_t hkey = hashKey(key);
            Knot * const knot = pool.summon(value,hkey);
            try {
                Node * const node = table.insert(hkey,knot,SameKnot);
                if(!node) { pool.banish(knot); return false; }
                list.pushTail(knot);
                assert(table.size == list.size);
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
            const size_t hkey = hashKey(key);
            void * const addr = table.remove(hkey,&key,SameKey);
            if(!addr) return false;
            pool.banish( list.pop(static_cast<Knot *>(addr)) );
            assert(table.size == list.size);
            return true;
        }

        inline ConstType * search(ParamKey key) const noexcept
        {
            const size_t        hkey = hashKey(key);
            const HTable::Slot *slot = 0;
            const Node * const  node = table.search(hkey,&key,SameKey,slot);
            if(!node) return 0;
            const Knot * const knot = static_cast<const Knot *>(node->data);
            return & knot->data;
        }


        inline  Type * search(ParamKey key) noexcept
        {
            const size_t   hkey = hashKey(key);
            HTable::Slot * slot = 0;
            Node * const   node = table.search(hkey,&key,SameKey,slot);
            if(!node) return 0;
            Knot * const knot = static_cast<Knot *>(node->data);
            return & knot->data;
        }



#if 0
        inline  Type * search(ParamKey key) noexcept
        {
            Node * const node = tree.search( key.begin(), key.size() );
            if(!node) return 0;
            assert(0!=node->addr);
            return static_cast<Type *>(node->addr);
        }
#endif



    private:
        HTable             table;
        KList              list;
        KPool              pool;
        mutable KEY_HASHER hash;

        Y_Disable_Copy_And_Assign(HashSet);

        static inline bool SameKnot(const void * const lhs, const void * const rhs)
        {
            return static_cast<const Knot *>(lhs)->key() == static_cast<const Knot *>(rhs)->key();
        }

        static inline bool SameKey(const void * const lhs, const void * const rhs)
        {
            return *static_cast<ConstKey *>(lhs)== static_cast<const Knot *>(rhs)->key();
        }

        inline size_t hashKey(ConstKey &key) const
        {
            volatile Lock lock(pool);
            return hash(key);
        }


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
