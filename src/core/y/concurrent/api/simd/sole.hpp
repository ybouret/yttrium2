

//! \file

#ifndef Y_Concurrent_Sole_Included
#define Y_Concurrent_Sole_Included 1

#include "y/concurrent/api/simd.hpp"
#include "y/concurrent/fake-lock.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Sole SIMD, sequential
        //
        //
        //______________________________________________________________________
        class Sole : public SIMD
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Sole"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Sole() noexcept; //!< setup with size=1
            virtual ~Sole() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign()       const noexcept;
            virtual void         operator()( Kernel & ) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Sole); //!< discarding
            FakeLock mutex;   //!< sequential mutex
            Context  context; //!< 1.0
        };
    }

}

#endif
