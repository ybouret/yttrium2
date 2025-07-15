//! \file

#ifndef Y_Random_In3D_Included
#define Y_Random_In3D_Included 1

#include "y/random/bits.hpp"
#include "y/mkl/numeric.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Random
    {

        //! three points on the unit sphere
        /**
         \param x first coord
         \param y second coord
         \param z third coord
         \param ran bits
         */
        template <typename T> inline
        void OnSphere(T &x, T &y, T &z, Random::Bits &ran)
        {
            typedef typename Alea<T>::Type CoreType;
            static const CoreType one = 1;
            CoreType x1 = ran.symm<CoreType>();
            CoreType x2 = ran.symm<CoreType>();
            CoreType sq = x1*x1 + x2*x2;
            while( sq >= one)
            {
                x1 = ran.symm<CoreType>();
                x2 = ran.symm<CoreType>();
                sq = x1*x1 + x2*x2;
            }
            const CoreType fac = std::sqrt(one-sq);
            x = Twice( x1*fac );
            y = Twice( x2*fac );
            z = one - Twice(sq);
        }


        //! \param ran bits \return vertex on the unit sphere
        template <typename VTX> inline
        VTX OnSphere(Random::Bits &ran)
        { VTX v; OnSphere(v[1],v[2],v[3],ran); return v; }

        //! three points within the unit ball
        /**
         \param x first coord
         \param y second coord
         \param z third coord
         \param ran bits
         */
        template <typename T> inline
        void InBall(T &x, T &y, T &z, Random::Bits &ran)
        {
            static const T one = 1;
            do
            {
                x = ran.symm<T>();
                y = ran.symm<T>();
                z = ran.symm<T>();
            } while( x*x + y*y + z*z > one );
        }

        //! \param ran bits \return vertex within the unit ball
        template <typename VTX> inline
        VTX InBall(Random::Bits &ran)
        { VTX v; InBall(v[1],v[2],v[3],ran); return v; }

    }

}

#endif

