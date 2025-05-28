
//! \file

#ifndef Y_Hashing_IBJ64_Included
#define Y_Hashing_IBJ64_Included 1

#include "y/hashing/mix64.hpp"

namespace Yttrium
{
    namespace Hashing
    {

        //______________________________________________________________________
        //
        //
        //
        //! Bob Jenkins' integer hash
        //
        //
        //______________________________________________________________________
        class IBJ64 : public Mix64
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Hashing::IBJ64"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit IBJ64() noexcept; //!< setup
            virtual ~IBJ64() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            virtual const char * callSign()                         const noexcept;
            virtual void         operator()(uint32_t &, uint32_t &) const noexcept;

        private:
            Y_Disable_Copy_And_Assign(IBJ64); //!< discarding
        };

    }

}

#endif

