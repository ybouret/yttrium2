
//! \file

#ifndef Y_Concurrent_Member_Included
#define Y_Concurrent_Member_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"
namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Member of a group with size and rank
        //
        //
        //______________________________________________________________________
        class Member
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param sz size \param rk rank
            explicit Member(const size_t sz, const size_t rk) noexcept;
            virtual ~Member()      noexcept; //!< cleanup
            Member(const Member &) noexcept; //!< duplicate
            Y_OSTREAM_PROTO(Member);         //!< display

            const size_t size; //!< total number of threads
            const size_t rank; //!< local rank
            const size_t indx; //!< local indx=rank+1

        private:
            Y_Disable_Assign(Member); //!< disarding
        };
    }

}

#endif
