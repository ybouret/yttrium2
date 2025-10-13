//! \file

#ifndef Y_Fit_Sample_Included
#define Y_Fit_Sample_Included 1

#include "y/mkl/fit/adjustable.hpp"

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
            //! Sample interface
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA, typename ORDINATE>
            class Sample : public Adjustable<ABSCISSA,ORDINATE>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const unsigned Dimensions = sizeof(ORDINATE) / sizeof(ABSCISSA); //!< alias
                typedef Keyed<String,ArcPtr<Sample>>       Pointer;                     //!< alias
                typedef Adjustable<ABSCISSA,ORDINATE>      AdjustableType;
                typedef typename AdjustableType::XAddition XAddition;
                typedef typename AdjustableType::Function  Function;
                using AdjustableType::xadd;
                using AdjustableType::D2;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param id  name
                 \param _X  input abscissae
                 \param _Y  input ordinates
                 \param _Yf ouput ordinates
                 */
                template <typename UID> inline
                explicit Sample(const UID                & id,
                                const Readable<ABSCISSA> & _X,
                                const Readable<ORDINATE> & _Y,
                                Writable<ORDINATE>       & _Yf):
                AdjustableType(id), X(_X), Y(_Y), Yf(_Yf), vars()
                {
                }

                //! cleanup
                inline virtual ~Sample() noexcept {}

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                inline virtual size_t count() const noexcept
                {
                    assert( X.size() == Y.size() );
                    assert( X.size() == Yf.size() );
                    return X.size();
                }

                virtual ORDINATE computeD2(Function                 & F,
                                           const Readable<ORDINATE> & aorg)
                {

                    xadd.ldz();
                    const size_t n = X.size();
                    for(size_t i=1;i<=n;++i)
                    {
                        const ORDINATE delta = Y[i] - (Yf[i] =  F(X,i,vars,aorg));
                        xadd << delta*delta;
                    }
                    return (D2=xadd.sum());
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Readable<ABSCISSA> & X;    //!< input  abscissae
                const Readable<ABSCISSA> & Y;    //!< input  ordinates
                Writable<ABSCISSA>       & Yf;   //!< output ordinates
                Variables                  vars; //!< fitting variables

            private:
                Y_Disable_Copy_And_Assign(Sample); //!< discarding
            };
        }
        
    }
}


#endif // !Y_Fit_Sample_Included

