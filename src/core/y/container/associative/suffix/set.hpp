
#ifndef Y_Associative_SuffixSet_Included
#define Y_Associative_SuffixSet_Included 1

#include "y/container/associative/glossary.hpp"
#include "y/container/tree/suffix.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"

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
        class Knot
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
            inline ~Knot() noexcept {}

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
    class SuffixSet : public Glossary<KEY,T>, public Collectable
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

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit SuffixSet() : tree(), list(), pool() {}

        //! cleanup
        inline virtual ~SuffixSet() noexcept { purge(); }

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
        KList      list; //!< data list
        KPool      pool; //!< data pool

        Y_Disable_Copy_And_Assign(SuffixSet); //!< discarding

        //! free
        inline void clear() noexcept {
            tree.free();
            while(list.size) pool.banish( list.popTail() );
        }

        //! release
        inline void purge() noexcept
        {
            tree.release();
            while(list.size) pool.remove( list.popTail() );
        }

    };

}

#endif
