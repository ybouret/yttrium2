
//! \file

#ifndef Y_Concurrent_Context_Included
#define Y_Concurrent_Context_Included 1

#include "y/concurrent/member.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Context for threads to retrieve info
        //
        //
        //______________________________________________________________________
        class Context : public Member
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup \param sz size \param rk rank
            explicit Context(Lockable &, const size_t sz, const size_t rk) noexcept;
            virtual ~Context() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Lockable &   sync; //!< for local thread access
            


        private:
            Y_Disable_Copy_And_Assign(Context); //!< discarding

        };

    }

}

#endif

