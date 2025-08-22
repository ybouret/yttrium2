
//! \file

#ifndef Y_Ink_ZeroFlux_Included
#define Y_Ink_ZeroFlux_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        class ZeroFlux
        {
        public:

            ZeroFlux(const size_t n)  noexcept;
            ZeroFlux(const ZeroFlux&) noexcept;

            ~ZeroFlux() noexcept;

            const unit_t count; //!< length
            const unit_t twice; //!< 2*count-1

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

        private:
            Y_Disable_Assign(ZeroFlux);
        };
    }
}

#endif

