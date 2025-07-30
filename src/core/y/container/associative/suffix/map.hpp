//! \file

#ifndef Y_Associative_SuffixMap_Included
#define Y_Associative_SuffixMap_Included 1

#include "y/container/associative/knot/master.hpp"
#include "y/container/associative/lexicon.hpp"
#include "y/container/tree/suffix.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! management for SuffixMap
    //
    //
    //__________________________________________________________________________
    struct SuffixMapAPI
    {
        typedef SuffixTree::Node Node; //!< alias

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
            typedef Protean::WarpedCacheOf<Knot,SingleThreadedClass> Pool; //!< alias
            typedef Core::ListOf<Knot>                               List; //!< alias

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            //! setup \param k key \param v value
            inline  Knot(ParamKey k, ParamType v) : key(k), data(v), next(0), prev(0) { }

            //! duplicate \param knot another knot
            inline  Knot(const Knot &knot) : key(knot.key), data(knot.data), next(0), prev(0) {}

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
            ConstKey key;  //!< current key
            Type     data; //!< data
            Knot *   next; //!< for list
            Knot *   prev; //!< for list

        private:
            Y_Disable_Assign(Knot); //!< discarding
            inline virtual ConstType & locus() const noexcept { return data; }
        };
    };


    //__________________________________________________________________________
    //
    //
    //
    //! Suffix Map
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class SuffixMap :
    public Lexicon<KEY,T>,
    public Core::MasterOf< SuffixMapAPI::Knot<KEY,T> >,
    public Collectable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);  //!< aliases
        Y_Args_Declare(KEY,Key); //!< aliases
        typedef typename SuffixMapAPI::Node        Node;  //!< alias
        typedef typename SuffixMapAPI::Knot<KEY,T> Knot;  //!< alias
        typedef typename Knot::Pool                KPool; //!< alias
        typedef typename Knot::List                KList; //!< alias
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
        inline explicit SuffixMap() : Base(), tree()
        {
        }

        //! cleanup
        inline virtual ~SuffixMap() noexcept
        {
            purge();
        }

        //! duplicate \param other another map
        inline SuffixMap(const SuffixMap &other) :
        Lexicon<KEY,T>(), Base(), Collectable(), tree()
        {
            try {
                for(const Knot *knot = other.list.head;knot;knot=knot->next)
                    (void) insert(knot->key,knot->data);
            }
            catch(...) { purge(); throw; }
        }


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void free()    noexcept { clear(); }
        inline virtual void release() noexcept { purge(); }

        virtual void gc(const uint8_t amount) noexcept
        {
            tree.gc(amount);
            pool.gc(amount);
        }


        inline bool insert(ParamKey key, ParamType value)
        {
            Knot * const knot = pool.summon(key,value);
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

        
        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    private:
        SuffixTree tree; //!< inner tree
        Y_Disable_Assign(SuffixMap); //!< discarding

        //! clean content
        inline void clear() noexcept {
            tree.free();
            clearList();
        }

        //! release content
        inline void purge() noexcept
        {
            tree.release();
            purgeList();
        }

    };

}

#endif
