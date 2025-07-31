//! \file

#ifndef Y_HASHING_HMAC_INCLUDED
#define Y_HASHING_HMAC_INCLUDED 1

#include "y/hashing/digest.hpp"
#include "y/hashing/function.hpp"

namespace Yttrium
{
    namespace Hashing
    {
        //______________________________________________________________________
        //
        //
        //! RFC 2104 HMAC
        //
        //______________________________________________________________________
        class HashMAC
        {
        public:
            //__________________________________________________________________
            //
            // types and definitions
            //__________________________________________________________________
            static const char Prefix[]; //!< "HMAC_";

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            virtual ~HashMAC() noexcept; //!< cleanup
            explicit HashMAC(Function &, const void * const, const size_t); //!< setup with key
            explicit HashMAC(Function &, const Memory::ReadOnlyBuffer &);  //!< setup with buffer as key

            //__________________________________________________________________
            //
            // methods
            //__________________________________________________________________
            void                          set(Function &) noexcept; //!< initialize with function
            const Memory::ReadOnlyBuffer &get(Function &) noexcept; //!< \return inner digest, computed

            //__________________________________________________________________
            //
            // members
            //__________________________________________________________________
            const size_t L; //!< hash function length
            const size_t B; //!< hash function window

        private:
            Y_Disable_Copy_And_Assign(HashMAC); //!< discarding
            void setup(Function &, const void * const, const size_t) noexcept; //!< setup from any key

            const Digest key; //!< precomputed key
            const Digest ikp; //!< input  key pad
            const Digest okp; //!< output key pad
            Digest       tmp; //!< store H(ikp|message)
        };

    }

}

#endif
