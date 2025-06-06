//! \file
//!
#ifndef Y_System_WallTime_Included
#define Y_System_WallTime_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace System
    {
        //______________________________________________________________________
        //
        //
        //
        //! Wall Time
        //
        //
        //______________________________________________________________________
        class WallTime
        {
        public:
            class Code;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit WallTime();          //!< initialize inner data
            virtual ~WallTime() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            static uint64_t Ticks(); //!< unlocked \return system ticks
            long double operator()(const uint64_t) const noexcept; //!< convert ticks \return seconds
            long double since(const uint64_t start) const;         //!< ellapsed time \param start origin \return seconds

        private:
            Y_Disable_Copy_And_Assign(WallTime); //!< discarding
            Code * const code;                   //!< internal code
        };
    }
}

#endif


