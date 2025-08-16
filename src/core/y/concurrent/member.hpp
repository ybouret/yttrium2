
//! \file

#ifndef Y_Concurrent_Member_Included
#define Y_Concurrent_Member_Included 1

#include "y/core/setup.hpp"
#include "y/ostream-proto.hpp"
namespace Yttrium
{
    namespace Concurrent
    {

        class Member
        {
        public:
            explicit Member(const size_t sz, const size_t k) noexcept;
            virtual ~Member() noexcept;
            Member(const Member &) noexcept;
            Y_OSTREAM_PROTO(Member);
            
            const size_t size; //!< total number of threads
            const size_t rank; //!< local rank
            const size_t indx; //!< local indx=rank+1

        private:
            Y_Disable_Assign(Member);
        };
    }

}

#endif
