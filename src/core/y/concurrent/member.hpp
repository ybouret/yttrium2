
//! \file

#ifndef Y_Concurrent_Member_Included
#define Y_Concurrent_Member_Included 1

#include "y/calculus/integer-pow10.hpp"
#include "y/ability/legacy-string.hpp"
#include <cassert>

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
            void updateLogo() noexcept; //!< make logo from current size and indx

            //! partition algorithm
            /**
             \param mySize mySize>0
             \param myIndx 1<=myIndx<=mySize
             \param extent total extent
             \param travel cumulative extent so far, updated
             \return length
             */
            template <typename T> static inline
            T Part(const size_t mySize,
                   const size_t myIndx,
                   T            extent,
                   T          & travel) noexcept
            {
                assert(mySize>0); assert(myIndx>=1); assert(myIndx<=mySize);
                size_t divide = mySize;
                T      length = 0;
                for(size_t i=myIndx;i>0;--i)
                {
                    travel += length;
                    length  = (T)(extent / divide--);
                    extent -= length;
                }
                return length;
            }

            //! partition algorithm for this member
            /**
             \param extent total extent
             \param travel cumulative extent so far, updated
             \return length
             */
            template <typename T> inline
            T part(T extent, T &travel) const noexcept
            {
                return Part(size,indx,extent,travel);
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
            const char   logo[TagSize]; //!< store tag

        };
    }

}

#endif // !Y_Concurrent_Member_Included
