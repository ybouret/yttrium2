
//! \file

#ifndef Y_Concurrent_SIMD_Included
#define Y_Concurrent_SIMD_Included 1

#include "y/concurrent/api/parallel.hpp"
#include "y/concurrent/api/kernel.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Single Instruction Multiple Data
        //
        //
        //______________________________________________________________________
        class SIMD : public Parallel
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static bool Verbose; //!< helper

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            explicit SIMD() noexcept;

        public:
            //cleanup
            virtual ~SIMD() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void operator()( Kernel & ) noexcept = 0; //!< execute kernel for each context

        private:
            Y_Disable_Copy_And_Assign(SIMD); //!< discarding
        };

    }

}

#endif // !Y_Concurrent_SIMD_Included

