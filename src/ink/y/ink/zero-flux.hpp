
//! \file

#ifndef Y_Ink_ZeroFlux_Included
#define Y_Ink_ZeroFlux_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //______________________________________________________________________
        //
        //
        //
        //! ZeroFlux addressing
        //
        //
        //______________________________________________________________________
        class ZeroFlux
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            ZeroFlux(const size_t n)  noexcept; //!< setup \param n length in one dimension
            ZeroFlux(const ZeroFlux&) noexcept; //!< duplicate
            ~ZeroFlux() noexcept;               //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            unit_t operator[](const unit_t indx) const noexcept
            {
                if(indx<0)
                    return (*this)[-indx];
                else
                {
                    if(indx>=count)
                    {
                        return (*this)[twice-indx];
                    }
                    else
                        return indx;
                }
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const unit_t count; //!< length
            const unit_t twice; //!< 2*count-1

        private:
            Y_Disable_Assign(ZeroFlux);
        };
    }
}

#endif

