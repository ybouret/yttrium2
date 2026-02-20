
#include "y/color/ramp.hpp"
#include "y/core/utils.hpp"
#include <cmath>

namespace Yttrium
{
    namespace Color
    {
        Ramp:: ~Ramp() noexcept
        {
        }

        Ramp:: Ramp(const char   * const _label,
                    const RGBA32 * const _table,
                    const size_t         _count) noexcept :
        label(_label),
        table(_table),
        count(_count),
        idmax(count-1)
        {
            assert(label);
            assert(table);
            assert(count>=2);
        }


        Ramp:: Ramp(const Ramp &_) noexcept :
        label(_.label),
        table(_.table),
        count(_.count),
        idmax(_.idmax)
        {
            
        }

        static inline
        uint8_t mix8(const uint8_t ulo, const float wlo,
                     const uint8_t uhi, const float whi) noexcept
        {
            const float vlo = ulo * wlo;
            const float vhi = uhi * whi;
            return (uint8_t)floorf(vlo+vhi+0.5f);
        }

        static inline
        RGBA32 mix32(const RGBA32 clo, const float wlo,
                     const RGBA32 chi, const float whi) noexcept
        {
            const uint8_t r = mix8(clo.r,wlo,chi.r,whi);
            const uint8_t g = mix8(clo.g,wlo,chi.g,whi);
            const uint8_t b = mix8(clo.b,wlo,chi.b,whi);
            return RGBA32(r,g,b);
        }


        RGBA32 Ramp:: get(const float f) const noexcept
        {
            //std::cerr << "get(" << f << ")" << std::endl;
            const float x = Clamp<float>(0,f,1);
            size_t      ilo = (size_t)floorf(x*idmax+0.5f);
            if(ilo>=count) --ilo;
            const float  xlo = (float)ilo;
            const float  whi = Clamp<float>(0,x-xlo,1);
            const float  wlo = 1.0f-whi;
            return mix32(table[ilo],wlo,table[ilo+1],whi);
        }






    }

}

#if 0
#include "y/color/gray.hpp"

namespace Yttrium
{
    namespace Color
    {
        float Ramp:: ToFloat(const float &x) noexcept
        {
            return x;
        }

        float Ramp:: ToFloat(const uint8_t &x) noexcept
        {
            return ByteTo<float>::Unit[x];
        }

    }
}
#endif

