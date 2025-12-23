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
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const Empty; //!< "|empty|";


        protected:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Subdivision(const size_t, const size_t) noexcept; //!< setup size.rank
            explicit Subdivision(const Member &)             noexcept; //!< setup
            Subdivision(const Subdivision &)                 noexcept; //!< duplicate
        public:
            virtual ~Subdivision() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // interface
            //
            //__________________________________________________________________

            //! \return true if empty subdivision
            virtual bool isEmpty() const noexcept = 0;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! aliasing helper \return cast to user's type
            template <typename T> inline
            T & as() noexcept
            {
                assert(bytes>=sizeof(T));
                assert(entry);
                return *static_cast<T *>(entry);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            void * const entry; //!< local memory
            const size_t bytes; //!< local bytes

            


        private:
            Y_Disable_Assign(Subdivision); //!< discarding
        };
    }

}

#endif // !Y_Concurrent_Subdivision_Included
