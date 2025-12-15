//! \file


#ifndef Y_Concurrent_Subdivision_Included
#define Y_Concurrent_Subdivision_Included 1

#include "y/concurrent/member.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Generic subdivision interface
        //
        //
        //______________________________________________________________________
        class Subdivision : public Member
        {
        public:
            static const char * const Empty; //!< "|empty|";


        protected:
            explicit Subdivision(const size_t, const size_t) noexcept; //!< setup size.rank
            explicit Subdivision(const Member &)             noexcept; //!< setup
            Subdivision(const Subdivision &)                 noexcept; //!< duplicate
        public:

            virtual ~Subdivision() noexcept; //!< cleanup

            //! \return true if empty subdivision
            virtual bool isEmpty() const noexcept = 0;

            void * const entry;
            const size_t bytes;
            
        private:
            Y_Disable_Assign(Subdivision); //!< discarding
        };
    }

}

#endif // !Y_Concurrent_Subdivision_Included
