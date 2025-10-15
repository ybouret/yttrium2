#include "y/fltk/axis.hpp"
//#include "y/type/aliasing.hpp"

namespace Yttrium
{
    namespace FLTK 
    {
        Axis:: Axis() throw() : vmin(0),vmax(1),length(vmax-vmin)
        {
            
        }
        
        Axis:: ~Axis() throw()
        {
        }
        
        void Axis:: set_min( double amin ) 
        {
            Coerce(vmin)   = amin;
            Coerce(length) = vmax - vmin;
        }
        
        void Axis:: set_max(double amax)
        {
            Coerce(vmax)   = amax;
            Coerce(length) = vmax - vmin;
        }
        
        void Axis:: set_range(double amin, double amax)
        {
            Coerce(vmin)   = amin;
            Coerce(vmax)   = amax;
            Coerce(length) = vmax - vmin;
        }

        void Axis:: autoscaleX( const Curve &C, const double extra )
        {
            autoscale_(C,1,extra);
        }

        void Axis:: autoscaleY( const Curve &C, const double extra )
        {
            autoscale_(C,2,extra);
        }

        void Axis:: autoscale_( const Curve &C,  const size_t indx, const double extra)
        {
            if( C.size() > 0 )
            {
                double cmin = C[1][indx];
                double cmax = cmin;
                for( size_t i=2; i <= C.size(); ++i )
                {
                    const double tmp = C[i][indx];
                    if( tmp < cmin )
                        cmin = tmp;
                    if( tmp > cmax )
                        cmax = tmp;
                }
                const double amplitude = cmax - cmin;
                const double delta     = amplitude * extra;
                set_range( cmin - delta, cmax + delta );
            }
        }


        
    }
}
