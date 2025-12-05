
//! \file

#ifndef Y_Concurrent_Member_Included
#define Y_Concurrent_Member_Included 1

#include "y/calculus/integer-pow10.hpp"
#include "y/ability/legacy-string.hpp"

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
        class Member : public LegacyString
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned TagSize = 16;                                //!< alias
            static const unsigned Digits  = (TagSize-2)/2;                     //!< alias
            static const size_t   MaxSize = Integer10ToThe<Digits>::Value - 1; //!< alias


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

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * c_str() const noexcept;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void updateTag() noexcept; //!< make tag from current size and indx


            template <typename T> inline
            T part(T extent, T &travel) const noexcept
            {
                size_t divide = size;
                T      length = 0;
                for(size_t i=indx;i>0;--i)
                {
                    travel += length;
                    length  = extent / divide--;
                    extent -= length;
                }
                return length;
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t size;      //!< total number of threads
            const size_t rank;      //!< local rank
            const size_t indx;      //!< local indx=rank+1

        private:
            Y_Disable_Assign(Member);  //!< disarding
            const char   tag[TagSize]; //!< store tag

        };
    }

}

#endif // !Y_Concurrent_Member_Included
