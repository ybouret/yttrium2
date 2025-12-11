

//! \file


#ifndef Y_Concurrent_Divide_Box_Included
#define Y_Concurrent_Divide_Box_Included 1

#include "y/core/setup.hpp"
#include <iostream>

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
            //! Box[2|3|4]D
            //
            //
            //__________________________________________________________________
            template <typename VERTEX>
            class Box
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef               VERTEX         vertex_t;           //!< alias
                typedef typename      VERTEX::Type   scalar_t;           //!< alias
                static const unsigned DIMENSIONS   = VERTEX::DIMENSIONS; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param lo lower coordinate \param up upper coordinate
                inline Box(const vertex_t lo,
                           const vertex_t up) :
                lower(lo),
                upper(up),
                width(),
                shift(),
                count( Setup(Coerce(lower),Coerce(upper),Coerce(width),Coerce(shift)) )
                {
                }

                //! duplicate \param b another box
                inline Box(const Box &b) noexcept :
                lower(b.lower),
                upper(b.upper),
                width(b.width),
                shift(b.shift),
                count(b.count)
                {
                }

                //! cleanup
                inline virtual ~Box() noexcept
                {
                }

                //! display
                inline friend std::ostream & operator<< (std::ostream &os, const Box &box)
                {
                    return os << "|" << box.lower << "->" << box.upper << "; w=" << box.width << "; s=" << box.shift << " |=" << box.count;
                }

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! \param v vertex \return true if vertex is in box
                inline bool includes(const vertex_t &v) const noexcept
                {
                    for(unsigned i=1;i<=DIMENSIONS;++i)
                    {
                        if(v[i]<lower[i]||v[i]>upper[i]) return false;
                    }
                    return true;
                }

                //! \param n 0<=n<count \return n-th vertex
                inline vertex_t at(scalar_t n) const noexcept
                {
                    assert(n<count);
                    vertex_t  v;
                    for(unsigned i=DIMENSIONS;i>1;--i)
                    {
                        const scalar_t d = shift[i];
                        const scalar_t q = v[i] = n / d;
                        n -= q * d;
                    }
                    v[1] = n;
                    assert(includes(v+lower));
                    return  v + lower;
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const vertex_t lower; //!< lower coordinate
                const vertex_t upper; //!< upper coordinate
                const vertex_t width; //!< width
                const vertex_t shift; //!< shift per dimension
                const scalar_t count; //!< total items



            private:
                Y_Disable_Assign(Box); //!< discarding

                //! full setup
                /**
                 \param lo lower
                 \param up upper
                 \param sz width
                 \param sh shift
                 \return count
                 */
                static scalar_t Setup(vertex_t &lo,
                                      vertex_t &up,
                                      vertex_t &sz,
                                      vertex_t &sh) noexcept
                {
                    static const scalar_t one(1);

                    // update metrics and product
                    scalar_t prod = 1;
                    for(unsigned i=1;i<=DIMENSIONS;++i)
                    {
                        if(lo[i]>up[i]) Swap(lo[i],up[i]);
                        prod *= (sz[i] = one + up[i] - lo[i]);
                    }

                    // compute shift
                    sh[1] = 1;
                    for(unsigned i=2;i<=DIMENSIONS;++i)
                        sh[i] = sh[i-1] * sz[i-1];

                    return prod;
                }
            };

        }

    }

}

#endif // !Y_Concurrent_Divide_Box_Included

