

//! \file


#ifndef Y_Concurrent_Split2D_Included
#define Y_Concurrent_Split2D_Included 1

#include "y/concurrent/split/1d.hpp"
#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            template <typename T>
            class Metrics2D
            {
            public:
                typedef V2D<T>      Coord;
                typedef V2D<size_t> Count;
                explicit Metrics2D(Coord lo, Coord up) noexcept :
                lower(lo),
                upper(up),
                width(),
                items(0)
                {
                    setup();
                }

                inline virtual ~Metrics2D() noexcept {}

                const Coord  lower;
                const Coord  upper;
                const Count  width;
                const size_t items;
            private:
                Y_Disable_Copy_And_Assign(Metrics2D);
                inline void setup() noexcept
                {
                    if(lower.x>upper.x) CoerceSwap(lower.x,upper.x);
                    if(lower.y>upper.y) CoerceSwap(lower.y,upper.y);
                    ++(Coerce(width.x) = upper.x - lower.x);
                    ++(Coerce(width.y) = upper.y - lower.y);
                    Coerce(items) = width.x * width.y;
                }
            };

            template <typename T>
            class In2D : public Metrics2D<T>
            {
            public:
                typedef Metrics2D<T>                MetricsType;
                typedef typename MetricsType::Coord Coord;
                typedef typename MetricsType::Count Count;
                using MetricsType::items;

                explicit In2D(Coord lo, Coord up) noexcept :
                MetricsType(lo,up),
                in1d(items)
                {
                }

                void boot(const size_t numProcessors) noexcept
                {
                    in1d.boot(numProcessors,0);
                }

                bool next()
                {
                    if(!in1d.next()) return false;
                    
                    return true;
                }


                virtual ~In2D() noexcept
                {

                }


            private:
                In1D in1d;
                Y_Disable_Copy_And_Assign(In2D);
            };



        }


    }

}

#endif

