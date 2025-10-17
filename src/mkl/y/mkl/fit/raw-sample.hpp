
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
                Xh((ABSCISSA *)x,n),
                Yh((ORDINATE *)y,n)
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
                const LightArray<ABSCISSA> Xh; //!< holding x
                const LightArray<ORDINATE> Yh; //!< holding y

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
                typedef RawSampleData<ABSCISSA,ORDINATE> RawSampleDataType; //!< alias
                using RawSampleDataType::Xh;
                using RawSampleDataType::Yh;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param uid name
                 \param x c-style abscissae
                 \param y c-style ordinates
                 \param n number of parameters
                 \param Yf_ fit destination
                 */
                template <typename UID> inline
                explicit RawSample(const UID &           uid,
                                    const ABSCISSA * const x,
                                    const ORDINATE * const y,
                                    const size_t           n,
                                    Writable<ORDINATE> &   theYf) :
                RawSampleDataType(x,y,n),
                Sample<ABSCISSA,ORDINATE>(uid,Xh,Yh,theYf)
                {
                }

                //! cleanup
                inline virtual ~RawSample() noexcept {}
                
            private:
                Y_Disable_Copy_And_Assign(RawSample); //!< discarding
            };

        }

    }
}

#endif // !Y_Fit_RawSample_Included
