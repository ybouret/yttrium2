#ifndef Y_FLTK_AXIS_INCLUDED
#define Y_FLTK_AXIS_INCLUDED 1

#include "y/fltk/curve.hpp"

namespace Yttrium
{
    namespace FLTK
    {
        class Axis
        {
        public:
            explicit Axis() throw(); //!< 0-1
            virtual ~Axis() throw();
            
            const double vmin;
            const double vmax;
            const double length;
            
            void set_min( double );
            void set_max( double );
            void set_range( double amin, double amax );
            
            void autoscaleX( const Curve &C, const double extra = 0.0 );
            void autoscaleY( const Curve &C, const double extra = 0.0 );

        private:
            Y_Disable_Copy_And_Assign(Axis);
            void autoscale_( const Curve &C,  const size_t indx, const double extra);

        };
        
    }
}

#endif // !Y_FLTK_AXIS_INCLUDED
