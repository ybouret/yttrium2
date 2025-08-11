//! \file

#ifndef Y_Associative_SuffixSet_Included
#define Y_Associative_SuffixSet_Included 1

#include "y/container/associative/knot/master.hpp"
#include "y/container/associative/glossary.hpp"
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
    //! management for SuffixSet
    //
    //
    //__________________________________________________________________________
    struct SuffixSetAPI
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
            Y_Args_Declare(T,Type);   //!< aliases
            Y_Args_Declare(KEY,Key);  //!< aliases
            typedef Protean::WarpedCacheOf<Knot,SingleThreadedClass> Pool; //!< alias
            typedef Core::ListOf<Knot>                               List; //!< alias

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! setup \param arg value
            inline  Knot(ParamType arg) : data(arg), next(0), prev(0) { }

            //! duplicate \param knot another knot
            inline  Knot(const Knot &knot) : data(knot.data), next(0), prev(0) {}

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

            //! \return current key
            ConstKey & key() const noexcept { return data.key(); }


            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            Type   data; //!< data with data.key()
            Knot * next; //!< for list
            Knot * prev; //!< for list

        private:
            Y_Disable_Assign(Knot); //!< discard
            inline virtual ConstType & locus() const noexcept { return data; }
        };
    };


    //__________________________________________________________________________
    //
    //
    //
    //! SuffixSet
    //
    //
    //__________________________________________________________________________
    template <typename KEY, typename T>
    class SuffixSet :
    public Glossary<KEY,T>,
    public Core::MasterOf< SuffixSetAPI::Knot<KEY,T> >,
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
        typedef typename SuffixSetAPI::Node        Node;  //!< alias
        typedef typename SuffixSetAPI::Knot<KEY,T> Knot;  //!< alias
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
        inline explicit SuffixSet() : Base(), tree()  {}

        //! cleanup
        inline virtual ~SuffixSet() noexcept { purge(); }

        //! duplicate \param other another set
        inline SuffixSet(const SuffixSet &other) :
        Glossary<KEY,T>(),
        Base(),
        Collectable(),
        tree()
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

        inline virtual void free()                   noexcept { clear(); }
        inline virtual void release()                noexcept { purge(); }
        inline virtual void gc(const uint8_t amount) noexcept
        {
            tree.gc(amount);
            pool.gc(amount);
        }

        inline bool insert(ParamType value)
        {
            Knot * const knot = pool.summon(value);
            try {
                ConstKey &   key  = knot->key();
                Node * const node = tree.insert(key.begin(), key.size(), knot);
                if(!node) { pool.banish(knot); return false; }
                list.pushTail(knot);
                assert(knot == node->addr);
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
            std::cerr << "search '" << key << "'" << std::endl;
            const Node * const node = tree.search( key.begin(), key.size() );
            if(!node||!node->addr) return 0;
            return & static_cast<const Knot *>(node->addr)->data;
        }

        inline  Type * search(ParamKey key) noexcept
        {
            Node * const node = tree.search( key.begin(), key.size() );
            if(!node||!node->addr) return 0;
            return & static_cast<Knot *>(node->addr)->data;
        }



        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
    private:
        SuffixTree tree; //!< inner tree


        Y_Disable_Assign(SuffixSet); //!< discarding

        //! free
        inline void clear() noexcept {
            tree.free();
            clearList();
        }

        //! release
        inline void purge() noexcept
        {
            tree.release();
            purgeList();
        }

    };

}

#endif
