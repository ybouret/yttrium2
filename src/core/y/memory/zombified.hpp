
//! \file

#ifndef Y_Memory_Zombified_Included
#define Y_Memory_Zombified_Included 1

#include "y/memory/object/guild.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Memory management of blank memory space for a given type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Zombified
        {
        public:

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            inline explicit Zombified() : provider(sizeof(T)) {}  //!< initialize internal provider
            inline virtual ~Zombified() noexcept              {}  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! summon a new zombi \return clear memory block
            inline T *  summon()
            {
                return static_cast<T *>(provider.acquireBlock());
            }

            //! banish a summoned zombi \param zombi previously acquired block
            inline void banish( T * const zombi ) noexcept
            {
                assert(0!=zombi);
                provider.releaseBlock(zombi);
            }

        private:
            Y_Disable_Copy_And_Assign(Zombified); //!< discaeding
            Object::Guild provider;               //!< alias to memory
        };
    }

}

#endif
