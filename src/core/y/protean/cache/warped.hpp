
//! \file

#ifndef Y_Protean_WarpedCache_Included
#define Y_Protean_WarpedCache_Included 1

#include "y/memory/io/zombies.hpp"
#include "y/threading/must-lock.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    class Lockable;

    namespace Protean
    {
        //______________________________________________________________________
        //
        //
        //
        //! using local cache
        /**
         always behind List::Lock, but should have its own Threading
         when shared
         */
        //______________________________________________________________________
        template <typename NODE, typename CacheThreading>
        class WarpedCacheOf : public CacheThreading, public Caching
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef          NODE                 NodeType;  //!< alias
            typedef typename NodeType::ParamType  ParamType; //!< alias
            typedef typename CacheThreading::Lock Lock;      //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline WarpedCacheOf() :
            CacheThreading(),
            Caching(),
            zpool( sizeof(NODE) )
            {
            }

            //! setup with locking \param handle persistent lockable
            inline WarpedCacheOf(Lockable &handle) :
            CacheThreading(handle),
            Caching(),
            zpool( sizeof(NODE) )
            {
            }


            //! shared copy of zombies \param other another cache
            inline WarpedCacheOf( const WarpedCacheOf &other ) :
            CacheThreading(),
            Caching(),
            zpool(other.zpool)
            {

            }

            //! cleanup
            inline ~WarpedCacheOf() noexcept
            {
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            

            //! summon a live node
            /**
             \param args passed to node constructor
             \return a new live node
             */
            inline NodeType * summon(ParamType args) {
                Y_Must_Lock();
                void * const addr = zpool.query();
                try { return new (addr) NodeType(args); }
                catch(...) { zpool.store(addr); throw; }
            }


            //! summon a live node with 2 arguments
            /**
             \param arg1 passed to node constructor
             \param arg2 passed to node constructor
             \return a new live node
             */
            template <typename ARG1, typename ARG2> inline
            NodeType * summon(ARG1 &arg1, ARG2 &arg2)
            {
                Y_Must_Lock();
                void * const addr = zpool.query();
                try { return new (addr) NodeType(arg1,arg2); }
                catch(...) { zpool.store(addr); throw; }
            }


            //! summon a live node with 3 arguments
            /**
             \param arg1 passed to node constructor
             \param arg2 passed to node constructor
             \param arg3 passed to node constructor
             \return a new live node
             */
            template <typename ARG1, typename ARG2, typename ARG3> inline
            NodeType * summon(ARG1 &arg1, ARG2 &arg2, ARG3 &arg3)
            {
                Y_Must_Lock();
                void * const addr = zpool.query();
                try { return new (addr) NodeType(arg1,arg2,arg3); }
                catch(...) { zpool.store(addr); throw; }
            }




            //! send back to zombies (local cache)
            /**
             \param node a summoned node
             */
            inline void banish(NodeType * const node) noexcept
            {
                Y_Must_Lock();
                zpool.store( Destructed(node) );
            }

            //! send back to Small::Blocks (global cache)
            /**
             \param node a summoned node
             */
            inline void remove(NodeType * const node) noexcept
            {
                Y_Must_Lock();
                zpool.purge( Destructed(node) );
            }

            //! duplicate
            /**
             \param node conjured node
             \return copy of conjured node
             */
            inline NodeType * mirror(const NodeType * const node)
            {
                Y_Must_Lock();
                assert(0!=node);
                void * const addr = zpool.query();
                try { return new (addr) NodeType(*node); }
                catch(...) { zpool.store(addr); throw; }
            }


            //! [Caching] collect garbage \param amount amout to collect
            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                zpool.gc(amount);
            }

            //! [Caching] \return current store
            inline virtual size_t count() const noexcept
            {
                Y_Must_Lock();
                return zpool.count();
            }

            //! [Caching] reserve \param n number of extra objects
            inline void cache(const size_t n)
            {
                Y_Must_Lock();
                zpool.cache(n);
            }

        private:
            Y_Disable_Assign(WarpedCacheOf); //!< discarding
            Memory::Zombies zpool; //!< (shared) local cache
        };

    }

}

#endif

