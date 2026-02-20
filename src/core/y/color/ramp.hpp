
//! \file

#ifndef Y_Color_Ramp_Included
#define Y_Color_Ramp_Included

#include "y/color/rgba.hpp"


namespace Yttrium
{
    namespace Color
    {
        typedef RGBA<uint8_t> RGBA32; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! ramp of at least 2 persistent colors
        //
        //
        //______________________________________________________________________
        class Ramp
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            explicit Ramp(const char * const, const RGBA32 * const, const size_t) noexcept;
            virtual ~Ramp()    noexcept; //!< cleanup
            Ramp(const Ramp &) noexcept; //!< duplicate

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param f unit float \return interpolated color
            RGBA32 get(const float f) const noexcept;

            //__________________________________________________________________
            //
            //
            // members
            //
            //__________________________________________________________________
            const char * const   label; //!< persistent label
            const RGBA32 * const table; //!< persistent table
            const size_t         count; //!< at least two colors
            const size_t         idmax; //!< count-1
            
        private:
            Y_Disable_Assign(Ramp); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //
        //! Ramp on extended range for floating point/integer type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class RampOf : public Ramp
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            /**
             \param ramp  precomputed ramp
             \param _vmin minimal value of tyoe
             \param _vmax maximal value of type
             */
            inline explicit RampOf(const Ramp &ramp, const T _vmin=0, const T _vmax=1) noexcept :
            Ramp(ramp),
            vmin(_vmin),
            vmax(_vmax),
            dv(vmax-vmin)
            {}

            //! cleanup
            inline virtual ~RampOf() noexcept {}

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! color interpolation with internal float usage
            /**
             \param x vmin <= x <= vmax \return interpolated color
             */
            inline RGBA32 operator()(const T x) const noexcept
            {
                const float f = x;
                if(f<=vmin) return table[0];
                if(f>=vmax) return table[count-1];
                return get((f-vmin)/dv);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const float vmin; //!< minimum value as float
            const float vmax; //!< maximum value as float
        private:
            const float dv;   //!< vmax-vmin
            Y_Disable_Copy_And_Assign(RampOf); //!< discarding

        };


    }

}

#endif // !Y_Color_Ramp_Included
