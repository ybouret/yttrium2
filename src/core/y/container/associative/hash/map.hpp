//! \file


#ifndef Y_Associative_HashMap_Included
#define Y_Associative_HashMap_Included 1

#include "y/container/associative/knot/master.hpp"
#include "y/container/associative/lexicon.hpp"
#include "y/container/htable.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/hashing/key/hasher.hpp"
#include "y/hashing/fnv.hpp"
#include "y/type/ingress.hpp"

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
        class Knot : public Ingress<T>
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
            inline virtual ~Knot() noexcept {}

            //! display \param os output stream \param knot *this \return os
            inline friend std::ostream & operator<<(std::ostream &os, const Knot &knot)
            {
                return os << knot.key << ':' << knot.data;
            }
            
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
            inline virtual ConstType & locus() const noexcept { return data; }
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
    class HashMap :
    public Lexicon<KEY,T>,
    public Core::MasterOf< HashMapAPI::Knot<KEY,T> >,
    public Collectable
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
        typedef Core::MasterOf<Knot>             Base;  //!< alias
        using Base::list;
        using Base::pool;
        using Base::clearList;
        using Base::purgeList;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit HashMap() : table(), hash()
        {
        }

        //! cleanup
        inline virtual ~HashMap() noexcept
        {
            purge();
        }

        //! duplicate \param other another map
        inline HashMap(const HashMap &other) :
        Lexicon<KEY,T>(), Base(), Collectable(),
        table(), hash()
        {
            try {
                for(const Knot *knot = other.list.head;knot;knot=knot->next)
                    (void) insert(knot->key,knot->data);
            }
            catch(...) { purge(); throw; }
        }

        //! assign by copy/swap \param hmap another map \return *this
        inline HashMap & operator=(const HashMap &hmap)
        {
            if(this != &hmap ) {
                HashMap tmp(hmap);
                swapFor(tmp);
            }
            return *this;
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

        inline virtual void gc(const uint8_t amount) noexcept
        {
            table.gc(amount);
            pool.gc(amount);
        }


        //! exchange contents \param hmap another ma[
        inline void swapFor(HashMap &hmap) noexcept
        {
            table.swapFor(hmap.table);
            list.swapListFor(hmap.list);
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________

    private:
        HTable             table; //!< inner hash table
    public:
        mutable KEY_HASHER hash;  //!< key hasher
    private:

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
            clearList();
        }

        //! purge content
        inline void purge() noexcept
        {
            table.release();
            purgeList();
        }

    };

}

#endif
