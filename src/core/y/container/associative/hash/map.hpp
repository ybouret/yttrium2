


#ifndef Y_Associative_HashMap_Included
#define Y_Associative_HashMap_Included 1

#include "y/container/associative/lexicon.hpp"
#include "y/container/htable.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/hashing/key/hasher.hpp"
#include "y/hashing/fnv.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! management for HashSet
    //
    //
    //__________________________________________________________________________
    struct HashMapAPI
    {
        typedef HTable::Node Node;     //!< alias
        typedef Hashing::FNV Function; //!< alias

        //______________________________________________________________________
        //
        //
        //! inner knot
        //
        //______________________________________________________________________
        template <typename KEY, typename T>
        class Knot
        {
        public:
            //__________________________________________________________________
            //
            // Definitions
            //__________________________________________________________________
            Y_Args_Declare(T,Type);  //!< aliases
            Y_Args_Declare(KEY,Key); //!< aliases
            typedef Protean::WarpedCacheOf<Knot,MultiThreadedObject> Pool; //!< alias
            typedef Core::ListOf<Knot>                               List; //!< alias

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! setup \param k key \param v value \param h hkey
            inline  Knot(ParamKey     k,
                         ParamType    v,
                         const size_t h) :
            key(k),
            data(v),
            hkey(h),
            next(0),
            prev(0)
            { }

            //! duplicate \param knot another knot
            inline  Knot(const Knot &knot) :
            key(knot.key),
            data(knot.data),
            hkey(key),
            next(0),
            prev(0)
            {}

            //! cleanup
            inline ~Knot() noexcept {}

            

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            ConstKey     key;  //!< key
            Type         data; //!< object
            const size_t hkey; //!< hkey of key
            Knot *       next; //!< for list
            Knot *       prev; //!< for list

        private:
            Y_Disable_Assign(Knot); //!< discarding
        };
    };


    //__________________________________________________________________________
    //
    //
    //
    //! HTable based set
    //
    //
    //__________________________________________________________________________
    template <
    typename KEY,
    typename T,
    typename KEY_HASHER = Hashing::KeyWith<HashMapAPI::Function>
    >
    class HashMap : public Lexicon<KEY,T>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);  //!< alias
        Y_Args_Declare(KEY,Key); //!< alias
        typedef typename HashMapAPI::Node        Node;  //!< alias
        typedef typename HashMapAPI::Knot<KEY,T> Knot;  //!< alias
        typedef typename Knot::Pool              KPool; //!< alias
        typedef typename Knot::List              KList; //!< alias
        typedef typename KPool::Lock             Lock;  //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit HashMap() : table(), list(), pool(), hash()
        {
        }

        //! cleanup
        inline virtual ~HashMap() noexcept
        {
            purge();
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void free()    noexcept { clear(); } //!< free content, keep memory
        inline virtual void release() noexcept { purge(); } //!< release maximum memory

        inline virtual bool insert(ParamKey key, ParamType value)
        {
            const size_t hkey = hashKey(key);
            Knot * const knot = pool.summon(key,value,hkey);
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

        inline virtual bool remove(ParamKey key) noexcept
        {
            const size_t hkey = hashKey(key);
            void * const addr = table.remove(hkey,&key,SameKey);
            if(!addr) return false;
            pool.banish( list.pop(static_cast<Knot *>(addr)) );
            assert(table.size == list.size);
            return true;
        }

        inline virtual ConstType * search(ParamKey key) const noexcept
        {
            const size_t        hkey = hashKey(key);
            const Node * const  node = table.search(hkey,&key,SameKey);
            if(!node) return 0;
            const Knot * const knot = static_cast<const Knot *>(node->data);
            return & knot->data;
        }


        inline virtual Type * search(ParamKey key) noexcept
        {
            const size_t   hkey = hashKey(key);
            HTable::Slot * slot = 0;
            Node * const   node = table.search(hkey,&key,SameKey,slot);
            if(!node) return 0;
            Knot * const knot = static_cast<Knot *>(node->data);
            return & knot->data;
        }



        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________

    private:
        HTable             table; //!< inner hash table
        KList              list;  //!< list of knots
        KPool              pool;  //!< pool of knots
        mutable KEY_HASHER hash;  //!< key hasher

        Y_Disable_Copy_And_Assign(HashMap); //!< discarding

        //! \param lhs knot address \param rhs knot address \return same keys
        static inline bool SameKnot(const void * const lhs, const void * const rhs)
        {
            return static_cast<const Knot *>(lhs)->key == static_cast<const Knot *>(rhs)->key;
        }

        //! \param lhs key address \param rhs knot address \return same keys
        static inline bool SameKey(const void * const lhs, const void * const rhs)
        {
            return *static_cast<ConstKey *>(lhs)== static_cast<const Knot *>(rhs)->key;
        }

        //! protected hash call \param key key \return hash(key)
        inline size_t hashKey(ConstKey &key) const
        {
            volatile Lock lock(pool);
            return hash(key);
        }


        //! clear content
        inline void clear() noexcept {
            table.free();
            while(list.size) pool.banish( list.popTail() );
        }

        //! purge content
        inline void purge() noexcept
        {
            table.free();
            while(list.size) pool.remove( list.popTail() );
        }

    };

}

#endif
