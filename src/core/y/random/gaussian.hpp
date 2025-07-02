
// \file

#ifndef Y_Random_Gaussian_Included
#define Y_Random_Gaussian_Included 1

#include "y/random/bits.hpp"
#include "y/mkl/numeric.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Random
    {


        //______________________________________________________________________
        //
        //
        //
        //! Guassian Random values
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Gaussian : public SharedBits
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename Alea<T>::Type CoreType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param sharedBits bits producer
            inline explicit Gaussian(const SharedBits &sharedBits) noexcept :
            SharedBits(sharedBits), i0(true), g0(0), g1(0)
            { BoxMuller(); }

            //! cleanup
            inline virtual ~Gaussian() noexcept {}

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \return next Gaussian value
            inline T operator()(void) noexcept
            {
                if(i0)
                {
                    i0 = false;
                    return g0;
                }
                else
                {
                    i0 = true;
                    const CoreType g = g1;
                    BoxMuller();
                    return g;
                }
            }


        private:
            Y_Disable_Copy_And_Assign(Gaussian); //!< discarding
            bool       i0;        //!< indicator
            CoreType   g0;        //!< generated
            CoreType   g1;        //!< generated

            //! compute two succesive values
            inline void BoxMuller() noexcept
            {
                Random::Bits &ran = **this;
                CoreType r = ran.to<CoreType>();
                while(r <= MKL::Numeric<CoreType>::EPSILON ) r = ran.to<CoreType>();
                const CoreType theta = MKL::Numeric<T>::PI * ran.symm<CoreType>();
                const CoreType ampli = std::sqrt(-Twice( std::log(r) ));
                g0 = ampli * std::sin(theta);
                g1 = ampli * std::cos(theta);
            }


        };
    }

}

#endif

