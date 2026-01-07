
//! \file


#ifndef Y_Concurrent_Divide_HSegment_Included
#define Y_Concurrent_Divide_HSegment_Included 1


#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        namespace Divide
        {
            //__________________________________________________________________
            //
            //
            //
            //! Generic Horizontal Segment
            //
            //
            //__________________________________________________________________
            template <typename T>
            class HSegment
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef T      scalar_t; //!< alias
                typedef V2D<T> vertex_t; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param v start \param w width > 0
                inline HSegment(const vertex_t v, const scalar_t w) noexcept :
                start(v),
                width(w)
                {
                    assert(w>0);
                }


                //! duplicate \param hs another segment
                inline HSegment(const HSegment &hs) noexcept :
                start(hs.start),
                width(hs.width)
                {
                }

                //! cleanup
                inline ~HSegment() noexcept {}

                //! display
                inline friend std::ostream & operator<<(std::ostream &os, const HSegment &self)
                {
                    vertex_t end = self.start; end.x += self.width; --end.x;
                    return os << "#" << self.width << ": " << self.start << "->" << end;
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \return rightmost coordinate
                inline vertex_t right() const noexcept { vertex_t _(start.x+width,start.y); --_.x; return _; }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const vertex_t  start; //!< starting point
                const scalar_t  width; //!< width

            private:
                Y_Disable_Assign(HSegment); //!< discarding
            };
        }

    }

}

#endif // !Y_Concurrent_Divide_HSegment_Included
