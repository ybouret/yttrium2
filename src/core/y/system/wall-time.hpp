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
            void        waitFor(const double seconds);             //!< \param seconds to wait for

        private:
            Y_Disable_Copy_And_Assign(WallTime); //!< discarding
            Code * const code;                   //!< internal code
        };
    }
}

//! helper to setup a walltime mark
#define Y_WallTime_Mark(U64PTR) \
const bool     Y_WallTime_DoMark = (0!=(U64PTR)); \
const uint64_t Y_WallTime_Mark64 = (Y_WallTime_DoMark ? Yttrium::System::WallTime::Ticks() : 0)


//! helper to update probe with ellapsed ticks from last mark
#define Y_WallTime_Gain(U64PTR) \
do { if(Y_WallTime_DoMark) (*U64PTR) += Yttrium::System::WallTime::Ticks() - Y_WallTime_Mark64; } while(false)

#define Y_WallTime_Update(VAR,CODE) \
/**/    do { \
/**/        const uint64_t __mark__ = Yttrium::System::WallTime::Ticks(); \
/**/        do { CODE; } while(false);                                    \
/**/        (VAR) += Yttrium::System::WallTime::Ticks() - __mark__;       \
/**/    } while(false)

#endif // !Y_System_WallTime_Included


