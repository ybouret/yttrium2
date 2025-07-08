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

#define Y_WallTime_Mark(U64PTR) \
const bool     Y_WallTime_DoMark = (0!=(U64PTR)); \
const uint64_t Y_WallTime_Mark64 = (Y_WallTime_DoMark ? Yttrium::System::WallTime::Ticks() : 0)


#define Y_WallTime_Gain(U64PTR) \
do { if(Y_WallTime_DoMark) (*U64PTR) += Yttrium::System::WallTime::Ticks() - Y_WallTime_Mark64; } while(false)

#endif


