//! \file

#ifndef Y_Fit_Sample_Included
#define Y_Fit_Sample_Included 1

#include "y/mkl/fit/variables.hpp"
#include "y/functor.hpp"

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
            class Sample : public Entity, public Container
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const unsigned Dimensions = sizeof(ORDINATE) / sizeof(ABSCISSA); //!< alias
                

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param id name
                 \param _X input abscissae
                 \param _Y input ordinates
                 \param _Z ouput ordinates
                 */
                template <typename UID> inline
                explicit Sample(const UID                & id,
                                const Readable<ABSCISSA> & _X,
                                const Readable<ORDINATE> & _Y,
                                Writable<ORDINATE>       & _Yf):
                Entity(id), X(_X), Y(_Y), Yf(_Yf), vars()
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
                inline virtual size_t size() const noexcept
                {
                    assert( X.size() == Y.size() );
                    assert( X.size() == Yf.size() );
                    return X.size();
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

