
//! \file

#ifndef Y_Fit_Optimizer_Included
#define Y_Fit_Optimizer_Included 1

#include "y/mkl/fit/adjustable.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/mkl/numeric.hpp"
#include "y/field/1d.hpp"
#include "y/mkl/api/fcpu.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            class OptimizerCommon
            {
            public:
                static const char * const CallSign;
                explicit OptimizerCommon() noexcept;
                virtual ~OptimizerCommon() noexcept;
            private:
                Y_Disable_Copy_And_Assign(OptimizerCommon);
            };

            template <typename ORDINATE>
            class Optimizer : public OptimizerCommon
            {
            public:
                typedef typename FCPU<ORDINATE>::Type fcpu_t;
                typedef Field::In1D<ORDINATE>         FieldType;

                explicit Optimizer();
                virtual ~Optimizer() noexcept;


                template <typename ABSCISSA> inline
                void run(Adjustable<ABSCISSA,ORDINATE> &                   S,
                         typename Adjustable<ABSCISSA,ORDINATE>::Function &F,
                         typename Adjustable<ABSCISSA,ORDINATE>::Gradient &G,
                         Writable<ORDINATE>   & aorg,
                         const Readable<bool> & used)
                {
                    assert(aorg.size() == used.size() );

                    p   = pini;
                    lam = lambda[p];

                    ORDINATE     D2_org = S.computeD2full(G,aorg,used);
                    const size_t nvar   = S.beta.size();
                    std::cerr << "D2_org=" << D2_org << std::endl;
                    prepare(nvar);
                    alpha.assign(S.alpha);
                    beta.ld(S.beta);
                    getStep();

                }

                template <typename ABSCISSA, typename FUNC, typename GRAD> inline
                void run_(Adjustable<ABSCISSA,ORDINATE> & S,
                          FUNC                          & F,
                          GRAD                          & G,
                          Writable<ORDINATE>            & aorg,
                          const Readable<bool>          & used)
                {
                    FWrapper<FUNC,ABSCISSA,ORDINATE> f(F);
                    GWrapper<GRAD,ABSCISSA,ORDINATE> g(G);
                    run(S,f,g,aorg,used);
                }



            private:
                Y_Disable_Copy_And_Assign(Optimizer); //!< discarding

                void prepare(const size_t nvar);
                bool getStep();

                Matrix<ORDINATE>          alpha;
                Vector<ORDINATE>          beta;
                Matrix<ORDINATE>          curv;
                Vector<ORDINATE>          step;
                LU<ORDINATE>              lu;
                int                       p;      //!< in pmin:pmax
                ORDINATE                  lam;    //!< 10^p
                Cameo::Addition<ORDINATE> xadd;
                const int                 pmin;   //!< min power, lam=0
                const int                 pmax;   //!< max power
                const int                 pini;   //!< initial power
                Field::Format1D           ffmt;   //!< field format
                const FieldType           lambda; //!< lambda[pmin:pmax]
                const ORDINATE            zero;   //!< 0
                const ORDINATE            one;    //!< 1
            };

        }

    }

}

#endif // !Y_Fit_Optimizer_Included

