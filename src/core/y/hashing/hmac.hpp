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
            explicit HashMAC(Function &H, const void * const key_addr, const size_t key_size); //!< setup
            explicit HashMAC(Function &H, const Memory::ReadOnlyBuffer &);                     //!< setup

            //__________________________________________________________________
            //
            // methods
            //__________________________________________________________________
            void                          set(Function &) noexcept; //!< initialize with function
            const Memory::ReadOnlyBuffer &get(Function &) noexcept; //!< finalize

            //__________________________________________________________________
            //
            // members
            //__________________________________________________________________
            const size_t L; //!< hash function length
            const size_t B; //!< hash function window

        private:
            Y_Disable_Copy_And_Assign(HashMAC); //!< discarding
            void setup(Function &H, const void * const key_addr, const size_t key_size) noexcept;

            const Digest key; //!< precomputed key
            const Digest ikp; //!< input  key pad
            const Digest okp; //!< output key pad
            Digest       tmp; //!< store H(ikp|message)
        };

    }

}

#endif
