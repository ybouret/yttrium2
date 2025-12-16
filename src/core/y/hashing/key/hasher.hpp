
//! \file

#ifndef Y_HASHING_TO_HASH_KEY_INCLUDED
#define Y_HASHING_TO_HASH_KEY_INCLUDED 1


#include "y/hashing/key/to.hpp"

namespace Yttrium
{

    namespace Hashing
    {

        //______________________________________________________________________
        //
        //
        //! key hasher prototype
        //
        //______________________________________________________________________
        template <typename FUNCTION>
        class KeyWith  : public ToKey<size_t,FUNCTION>
        {
        public:
            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            inline explicit KeyWith() noexcept : ToKey<size_t,FUNCTION>() {} //!< setup
            inline virtual ~KeyWith() noexcept {}                            //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(KeyWith); //!< discarding
        };
    }

}

#endif // !Y_HASHING_TO_HASH_KEY_INCLUDED
