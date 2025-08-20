//! \file

#ifndef Y_Associative_HashSet_Included
#define Y_Associative_HashSet_Included 1

#include "y/container/associative/knot/master.hpp"
#include "y/container/associative/glossary.hpp"
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
    struct HashSetAPI
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

            //! setup \param v value \param h hkey
            inline  Knot(ParamType    v,
                         const size_t h) :
            data(v),
            hkey(h),
            next(0),
            prev(0)
            { }

            //! duplicate \param knot another knot
            inline  Knot(const Knot &knot) :
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
                return os << knot.data;
            }

            //__________________________________________________________________
            //
            // Methods
            //__________________________________________________________________
            ConstKey & key() const noexcept { return data.key(); } //!< \return data key



            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            Type         data; //!< object
            const size_t hkey; //!< hkey of data->key()
            Knot *       next; //!< for list
            Knot *       prev; //!< for list

        private:
            Y_Disable_Assign(Knot); //!< discarding
            inline virtual ConstType &locus() const noexcept { return data; }
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
    typename KEY_HASHER = Hashing::KeyWith<HashSetAPI::Function>
    >
    class HashSet :
    public Glossary<KEY,T>,
    public Core::MasterOf< HashSetAPI::Knot<KEY,T> >,
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
        typedef typename HashSetAPI::Node        Node;  //!< alias
        typedef typename HashSetAPI::Knot<KEY,T> Knot;  //!< alias
        typedef typename Knot::Pool              KPool; //!< alias
        typedef typename Knot::List              KList; //!< alias
        typedef typename KPool::Lock             Lock;  //!< alias
        typedef Core::MasterOf<Knot>               Base;  //!< alias
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
        inline explicit HashSet() : Base(), table(), hash()
        {
        }

        //! cleanup
        inline virtual ~HashSet() noexcept
        {
            purge();
        }

        //! duplicate \param other another set
        inline HashSet(const HashSet &other) :
        Glossary<KEY,T>(),
        Base(),
        Collectable(),
        table(), hash()
        {
            try {
                for(const Knot *knot = other.list.head;knot;knot=knot->next)
                    (void) insert(knot->data);
            }
            catch(...) { purge(); throw; }
        }


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void free()    noexcept { clear(); } //!< free content, keep memory
        inline virtual void release() noexcept { purge(); } //!< release maximum memory


        inline virtual bool insert(ParamType value)
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
            assert(node->data);
            const Knot * const knot = static_cast<const Knot *>(node->data);
            return & knot->data;
        }


        inline virtual Type * search(ParamKey key) noexcept
        {
            const size_t   hkey = hashKey(key);
            HTable::Slot * slot = 0;
            Node * const   node = table.search(hkey,&key,SameKey,slot);
            if(!node) return 0;
            assert(node->data);
            Knot * const knot = static_cast<Knot *>(node->data);
            return & knot->data;
        }

        inline virtual void gc(const uint8_t amount) noexcept
        {
            table.gc(amount);
            pool.gc(amount);
        }

        inline void swapFor(HashSet &hset) noexcept
        {
            table.swapFor(hset.table);
            list.swapListFor(hset.list);
        }
        
        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________

    private:
        HTable             table; //!< inner hash table
        mutable KEY_HASHER hash;  //!< key hasher

        Y_Disable_Assign(HashSet); //!< discarding

        //! \param lhs knot address \param rhs knot address \return same keys
        static inline bool SameKnot(const void * const lhs, const void * const rhs)
        {
            return static_cast<const Knot *>(lhs)->key() == static_cast<const Knot *>(rhs)->key();
        }

        //! \param lhs key address \param rhs knot address \return same keys
        static inline bool SameKey(const void * const lhs, const void * const rhs)
        {
            return *static_cast<ConstKey *>(lhs)== static_cast<const Knot *>(rhs)->key();
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
