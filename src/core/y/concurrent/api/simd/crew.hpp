
//! \file

#ifndef Y_Concurrent_Crew_Included
#define Y_Concurrent_Crew_Included 1

#include "y/concurrent/api/simd.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Threaded SIMD
        //
        //
        //______________________________________________________________________
        class Crew : public SIMD
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Crew"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Crew(const size_t); //!< setup
            virtual ~Crew()    noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign()       const noexcept;
            virtual void         operator()( Kernel & ) noexcept;

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Crew); //!< discarding
            Code * const code;               //!< inner code
        };
    }

}

#endif
