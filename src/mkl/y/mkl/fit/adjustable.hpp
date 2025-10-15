
//! \file

#ifndef Y_Fit_Adjustable_Included
#define Y_Fit_Adjustable_Included 1

#include "y/mkl/fit/adjustable/engine.hpp"
#include "y/mkl/fit/type/fwrapper.hpp"
#include "y/mkl/fit/type/gwrapper.hpp"

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
            //! Interface for Sample[s]
            //
            //
            //__________________________________________________________________
            template <typename ABSCISSA,typename ORDINATE>
            class Adjustable : public AdjustableEngine<ORDINATE>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Y_Fit_Function             Function;  //!< alias
                typedef Y_Fit_Gradient             Gradient;  //!< alias
                typedef AdjustableEngine<ORDINATE> Engine;    //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param uid name
                template <typename UID>
                inline explicit Adjustable(const UID &uid) :
                Engine(uid)
                {
                }


                //! cleanup
                inline virtual ~Adjustable() noexcept {}


                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________

                //! simple D2 evaluation
                /**
                 \param F    adjustable function
                 \param aorg current values
                 \return D2 at aorg w.r.t F
                 */
                virtual ORDINATE computeD2(Function &F, const Readable<ORDINATE> &aorg) = 0;

                //! simple D2 wrapper evaluation
                /**
                 \param func compatible function
                 \param aorg current parameters
                 \return D2 at aorg w.r.t F
                 */
                template <typename FUNC> inline
                ORDINATE computeD2_(FUNC &func, const Readable<ORDINATE> &aorg)
                {
                    FWrapper<FUNC,ABSCISSA,ORDINATE> F(func);
                    return computeD2(F,aorg);
                }


                //! full D2/derivatives evaluation
                /**
                 \param F    adjustable gradient (+function)
                 \param aorg current values
                 \param used current used values flags
                 \return D2 at aorg w.r.t F
                 */
                virtual ORDINATE computeD2full(Gradient                 & F,
                                               const Readable<ORDINATE> & aorg,
                                               const Readable<bool>     & used) = 0;


                //! full D2/derivatives evaluation
                /**
                 \param grad adjustable gradient (+function)
                 \param aorg current values
                 \param used current used values flags
                 \return D2 at aorg w.r.t F
                 */
                template <typename GRAD> inline
                ORDINATE computeD2full_(GRAD                     & grad,
                                        const Readable<ORDINATE> & aorg,
                                        const Readable<bool>     & used)
                {
                    GWrapper<GRAD,ABSCISSA,ORDINATE> G(grad);
                    return computeD2full(G,aorg,used);
                }

            private:
                Y_Disable_Copy_And_Assign(Adjustable); //!< discarding

            };


        }

    }

}

#endif // !Y_Fit_Adjustable_Included
