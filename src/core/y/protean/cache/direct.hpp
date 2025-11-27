
//! \file

#ifndef Y_Protean_DirectCache_Included
#define Y_Protean_DirectCache_Included 1

#include "y/memory/small/guild.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{

    namespace Protean
    {
        //______________________________________________________________________
        //
        //
        //
        //! no local memory, direct I/O with Small::Blocks as global cache
        /**
         no threading policy since it is always behind List::Lock
         */
        //
        //______________________________________________________________________
        template <typename NODE>
        class DirectCacheOf
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef          NODE                NodeType;  //!< alias
            typedef typename NodeType::ParamType ParamType; //!< alias


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup, query proper guild
            inline DirectCacheOf() : guild( sizeof(NODE) )
            {
                assert( guild.getBlockSize() >= sizeof(NODE) );
            }

            //! cleanup
            inline ~DirectCacheOf() noexcept
            {
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            
            //! zombi node to live node
            /**
             \param args passed to node constructor
             \return live node
             */
            inline NodeType * summon(ParamType args) {
                void * const addr = guild.acquireBlock();
                try { return new (addr) NodeType(args); }
                catch(...) { guild.releaseBlock(addr); throw; }
            }


            //! zombi node to live node with two args
            /**
             \param u first arg
             \param v second arg
             \return live node
             */
            template <typename U, typename V>
            inline NodeType * summon( U &u, V &v) {
                void * const addr = guild.acquireBlock();
                try { return new (addr) NodeType(u,v); }
                catch(...) { guild.releaseBlock(addr); throw; }
            }

            //! live node to zombi node \param node conjured node
            inline void banish(NodeType * const node) noexcept
            {
                guild.releaseBlock( Destructed(node) );
            }

            //! equivalent to banish \param node conjured node
            inline void remove(NodeType * const node) noexcept
            {
                banish(node);
            }

            //! duplicate
            /**
             \param node conjured node
             \return copy of conjured node
             */
            inline NodeType * mirror(const NodeType * const node)
            {
                assert(0!=node);
                void * const addr = guild.acquireBlock();
                try { return new (addr) NodeType(*node); }
                catch(...) { guild.releaseBlock(addr); throw; }
            }

            //! compatibility with WarpedCache
            inline void release() noexcept
            {
                // do nothing
            }

        private:
            Y_Disable_Copy_And_Assign(DirectCacheOf); //!< discarding
            Memory::Small::Guild guild; //!< directly to Small::Blocks
        };

    }

}

#endif // !Y_Protean_DirectCache_Included
