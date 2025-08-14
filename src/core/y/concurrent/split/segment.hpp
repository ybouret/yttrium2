
//! \file


#ifndef Y_Concurrent_Split_Segment_Included
#define Y_Concurrent_Split_Segment_Included 1

#include "y/format/decimal.hpp"
#include <iostream>
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            //__________________________________________________________________
            //
            //
            //
            //! Segment from Split operation
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Segment
            {
            public:

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param first offset \param count length \param olast last offset
                inline explicit Segment(const T      first,
                                        const size_t count ) noexcept :
                offset(first),
                length(count)
                {
                }

                //! cleanup
                inline virtual ~Segment() noexcept {}

                //! duplicate \param s another segment
                Segment(const Segment &s) noexcept :
                offset(s.offset),
                length(s.length)
                {
                }

                Segment & operator=(const Segment &s) noexcept
                {
                    Coerce(offset) = s.offset;
                    Coerce(length) = s.length;
                    return *this;
                }

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const Segment &self)
                {
                    return os << '@' << Decimal(self.offset) << '+' << Decimal(self.length);
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const T      offset; //!< initial offset
                const size_t length; //!< length


            };

        }

    }

}

#endif

