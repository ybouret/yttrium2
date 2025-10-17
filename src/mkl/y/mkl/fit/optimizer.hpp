
//! \file

#ifndef Y_Fit_Optimizer_Included
#define Y_Fit_Optimizer_Included 1

#include "y/mkl/fit/adjustable.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/mkl/numeric.hpp"
#include "y/field/1d.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/stream/libc/output.hpp"

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
            //! Common parts for Optimizers
            //
            //
            //__________________________________________________________________
            class OptimizerCommon
            {
            public:
                static const char * const CallSign;  //!< "Fit::Optimizer"
                explicit OptimizerCommon() noexcept; //!< setup
                virtual ~OptimizerCommon() noexcept; //!< cleanup
            private:
                Y_Disable_Copy_And_Assign(OptimizerCommon); //!< discarding
            };


            //__________________________________________________________________
            //
            //
            //
            //! Optimizer 
            //
            //
            //__________________________________________________________________
            template <typename ORDINATE>
            class Optimizer : public OptimizerCommon
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef typename FCPU<ORDINATE>::Type fcpu_t;    //!< alias
                typedef Field::In1D<ORDINATE>         FieldType; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Optimizer();          //!< setup
                virtual ~Optimizer() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________


                template <typename ABSCISSA> inline
                bool run(Adjustable<ABSCISSA,ORDINATE> &                   S,
                         typename Adjustable<ABSCISSA,ORDINATE>::Function &F,
                         typename Adjustable<ABSCISSA,ORDINATE>::Gradient &G,
                         Writable<ORDINATE>   & aorg,
                         const Readable<bool> & used)
                {
                    assert(aorg.size() == used.size() );

                    p   = pini;
                    lam = lambda[p];
                    ORDINATE     D2_ini = S.computeD2full(G,aorg,used);
                    const size_t dims   = aorg.size();
                    const size_t nvar   = S.beta.size();
                    ORDINATE     sigma  = zero;
                    std::cerr << "D2_ini=" << D2_ini << std::endl;
                    prepare(dims,nvar);

                    // fetch metrics
                    alpha.assign(S.alpha);
                    beta.ld(S.beta);

                COMPUTE_STEP:
                    // build step
                    if(!getStep(sigma))
                        return false;


                    // build ini/end variables
                    setScan(aorg,S);

                    const ORDINATE D2_end = S.computeD2(F,aend);
                    std::cerr << "D2_end=" << D2_end << std::endl;

                    struct Phi
                    {
                        Adjustable<ABSCISSA,ORDINATE>                    &S;
                        typename Adjustable<ABSCISSA,ORDINATE>::Function &F;
                        const Readable<ORDINATE> &aini;
                        const Readable<ORDINATE> &aend;
                        Writable<ORDINATE>       &atry;
                        const ORDINATE            one;
                        ORDINATE operator()(const ORDINATE u)
                        {
                            const ORDINATE v = one - u;
                            for(size_t j=aini.size();j>0;--j)
                            {
                                atry[j] = aini[j] * v + aend[j] * u;
                            }
                            return S.computeD2(F,atry);
                        }
                    };

                    Phi phi = { S, F, aini, aend, atry, one };

                    {
                        static const unsigned   np = 100;
                        OutputFile fp( S.name + "-phi.dat");
                        for(unsigned i=0;i<=np;++i)
                        {
                            const ORDINATE u = (fcpu_t)i/(fcpu_t)np;
                            fp("%.15g %.15g\n", (double)u, (double)phi(u));
                        }
                    }

                    if(D2_end>D2_ini)
                    {
                        if(p>=pmax) return false;
                        lam = lambda[++p];
                        goto COMPUTE_STEP;
                    }


                    return false;
                }

                template <typename ABSCISSA, typename FUNC, typename GRAD> inline
                bool run_(Adjustable<ABSCISSA,ORDINATE> & S,
                          FUNC                          & F,
                          GRAD                          & G,
                          Writable<ORDINATE>            & aorg,
                          const Readable<bool>          & used)
                {
                    FWrapper<FUNC,ABSCISSA,ORDINATE> f(F);
                    GWrapper<GRAD,ABSCISSA,ORDINATE> g(G);
                    return run(S,f,g,aorg,used);
                }



            private:
                Y_Disable_Copy_And_Assign(Optimizer); //!< discarding

                //! prepare memory \param dims aorg size \param nvar sample variables
                void prepare(const size_t dims, const size_t nvar);

                //! compute step \return true if not singular
                bool getStep(ORDINATE &sigma);

                //! compute scan line \param aorg original value \param S engine to scatter step
                void setScan(const Readable<ORDINATE>         &aorg,
                             const AdjustableEngine<ORDINATE> &S) noexcept;


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Matrix<ORDINATE>          alpha;  //!< hessian
                Vector<ORDINATE>          beta;   //!< -gradient
                Matrix<ORDINATE>          curv;   //!< curvature
                Vector<ORDINATE>          step;   //!< step
                Vector<ORDINATE>          aini;   //!< initial values
                Vector<ORDINATE>          aend;   //!< final values
                Vector<ORDINATE>          atry;   //!< trial values
                LU<ORDINATE>              lu;     //!< linear algenra
                int                       p;      //!< in pmin:pmax
                ORDINATE                  lam;    //!< 10^p
                Cameo::Addition<ORDINATE> xadd;   //!< internal additions
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

