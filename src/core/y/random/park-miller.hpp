
// \file

#ifndef Y_Random_Park_Miller_Included
#define Y_Random_Park_Miller_Included 1

#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Random
    {

        //______________________________________________________________________
        //
        //
        //
        //! Park And Miller minimal PRNG
        //
        //
        //______________________________________________________________________
        class ParkMiller : public Bits
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "ParkMiller"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit         ParkMiller(const int32_t) noexcept; //!< setup with seed
            explicit         ParkMiller();                       //!< setup with system seed
            virtual         ~ParkMiller() noexcept;              //!< cleanup

            //__________________________________________________________________
            //
            //
            // Inteface
            //
            //__________________________________________________________________
            virtual uint32_t     next32()         noexcept;
            virtual const char * callSign() const noexcept;

        private:
            Y_Disable_Copy_And_Assign(ParkMiller); //!< discarding
            int32_t state; //!< internal state
        };
    }

}

#endif

