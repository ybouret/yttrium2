
//! \file

#ifndef Y_Color_Ramp_Included
#define Y_Color_Ramp_Included

#include "y/color/rgba.hpp"


namespace Yttrium
{
    namespace Color
    {
        typedef RGBA<uint8_t> RGBA32;

        class Ramp
        {
        public:
            explicit Ramp(const char * const, const RGBA32 * const, const size_t) noexcept;
            virtual ~Ramp()    noexcept;
            Ramp(const Ramp &) noexcept;

            RGBA32 get(const float f) const noexcept;
            

            const char * const   label;
            const RGBA32 * const table;
            const size_t         count;

        private:
            Y_Disable_Assign(Ramp);
        };

        template <typename T>
        class RampOf : public Ramp
        {
        public:
            inline explicit RampOf(const Ramp &ramp, const T _vmin=0, const T _vmax=1) noexcept :
            Ramp(ramp),
            vmin(_vmin),
            vmax(_vmax),
            dv(vmax-vmin)
            {}

            inline virtual ~RampOf() noexcept {}

            inline RGBA32 operator()(const T x) const noexcept
            {
                const float f = x;
                if(f<=vmin) return table[0];
                if(f>=vmax) return table[count-1];
                return get((f-vmin)/dv);
            }


        private:
            Y_Disable_Copy_And_Assign(RampOf);
            const float vmin;
            const float vmax;
            const float dv;
        };


    }

}

#endif // !Y_Color_Ramp_Included
