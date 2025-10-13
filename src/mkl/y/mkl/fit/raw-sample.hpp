
//! \file

#ifndef Y_Fit_RawSample_Included
#define Y_Fit_RawSample_Included 1

#include "y/mkl/fit/sample.hpp"
#include "y/container/light-array.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            //__________________________________________________________________
            //
            //
            //
            //! Holding Data
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA,typename ORDINATE>
            class RawSampleData
            {
            protected:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param x PERSISTENT C-type abscissae
                 \param y PERSISTENT C-type ordinates
                 \param n number of data
                 */
                inline explicit RawSampleData(const ABSCISSA * const x,
                                              const ORDINATE * const y,
                                              const size_t           n) noexcept :
                X_((ABSCISSA *)x,n),
                Y_((ORDINATE *)y,n)
                {
                }

            public:
                //! cleanup
                inline virtual ~RawSampleData() noexcept {}

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const LightArray<ABSCISSA> X_; //!< holding x
                const LightArray<ORDINATE> Y_; //!< holding y

            private:
                Y_Disable_Copy_And_Assign(RawSampleData); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! Sample interface
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class RawSample :
            public RawSampleData<ABSCISSA,ORDINATE>,
            public Sample<ABSCISSA,ORDINATE>
            {
            public:
                typedef RawSampleData<ABSCISSA,ORDINATE> RawSampleDataType;
                using RawSampleDataType::X_;
                using RawSampleDataType::Y_;

                template <typename UID> inline
                explicit RawSample(const UID &           uid,
                                    const ABSCISSA * const x,
                                    const ORDINATE * const y,
                                    const size_t           n,
                                    Writable<ORDINATE> &   Yf_) :
                RawSampleDataType(x,y,n),
                Sample<ABSCISSA,ORDINATE>(uid,X_,Y_,Yf_)
                {
                }

                inline virtual ~RawSample() noexcept {}
            private:
                Y_Disable_Copy_And_Assign(RawSample);
            };

        }

    }
}

#endif // !Y_Fit_RawSample_Included
