
//! \file

#ifndef Y_Fit_Optimizer_Included
#define Y_Fit_Optimizer_Included 1

#include "y/mkl/fit/adjustable.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/mkl/numeric.hpp"
#include "y/field/1d.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/stream/libc/output.hpp"
#include "y/core/utils.hpp"
#include "y/mkl/api/almost-equal.hpp"

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

            template <typename ABSCISSA,typename ORDINATE>
            class Phi
            {
            public:
                typedef typename FCPU<ORDINATE>::Type     fcpu_t;    //!< alias
                typedef Adjustable<ABSCISSA,ORDINATE>     AdjustableType;
                typedef typename AdjustableType::Function Function;
                typedef Readable<ORDINATE>                RO_Ordinates;
                typedef Writable<ORDINATE>                RW_Ordinates;

                inline explicit Phi(AdjustableType & S_,
                                    Function       & F_,
                                    const RO_Ordinates & aini_,
                                    const RO_Ordinates & aend_,
                                    RW_Ordinates       & atry_) noexcept :
                S(S_), F(F_), aini(aini_), aend(aend_), atry(atry_), one(1)
                {

                }

                inline ~Phi() noexcept {}

                inline ORDINATE operator()(const ORDINATE u)
                {
                    const ORDINATE v = one - u;
                    for(size_t i=atry.size();i>0;--i)
                    {
                        const ORDINATE cv   = aini[i];
                        const ORDINATE cu   = aend[i];
                        ORDINATE       cmin = cv;
                        ORDINATE       cmax = cu;
                        if(cmin>cmax) Swap(cmin,cmax);
                        assert(cmin<=cmax);
                        atry[i] = Clamp(cmin,cv*v+cu*u,cmax);
                    }
                    return S.computeD2(F,atry);
                }

                template <typename UID> inline
                void save(const UID &fileName, const bool append=false)
                {
                    static const unsigned   np = 100;
                    Phi &phi = *this;
                    OutputFile fp(fileName,append);
                    for(unsigned i=0;i<=np;++i)
                    {
                        const ORDINATE u = (fcpu_t)i/(fcpu_t)np;
                        fp("%.15g %.15g\n", (double)u, (double)phi(u));
                    }
                }

                AdjustableType     & S;
                Function           & F;
                const RO_Ordinates & aini;
                const RO_Ordinates & aend;
                RW_Ordinates       & atry;
                const ORDINATE       one;

            private:
                Y_Disable_Copy_And_Assign(Phi);
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
                bool run(XMLog                                            & xml,
                         Adjustable<ABSCISSA,ORDINATE>                    & S,
                         typename Adjustable<ABSCISSA,ORDINATE>::Function & F,
                         typename Adjustable<ABSCISSA,ORDINATE>::Gradient & G,
                         Writable<ORDINATE>                               & aorg,
                         const Readable<bool>                             & used)
                {
                    Y_XML_Section_Attr(xml,"Fit::Run"," name='" << S.name << "'");

                    assert(aorg.size() == used.size() );

                    size_t cycle=0;
                    //----------------------------------------------------------
                    //
                    // first initialization
                    //
                    //----------------------------------------------------------
                    p   = pini;
                    p   = 0;
                    lam = lambda[p];
                    ORDINATE     D2_ini = S.computeD2full(G,aorg,used);
                    const size_t dims   = aorg.size();   // total dimensions
                    const size_t nvar   = S.beta.size(); // known after computeD2full
                    ORDINATE     sigma  = zero;          // slope, to be computed
                    prepare(dims,nvar);

                    //----------------------------------------------------------
                    //
                    // fetch metrics
                    //
                    //----------------------------------------------------------
                CYCLE:
                    ++cycle;
                    Y_XML_Section_Attr(xml,"Iterate", Y_XML_Attr(cycle) << Y_XML_Attr(p) << Y_XML_Attr(lam) );
                    Y_XMLog(xml,"D2_ini = " << D2_ini);
                    S.display(xml,aorg,"_org");

                    alpha.assign(S.alpha);
                    beta.ld(S.beta);

                    if(false)
                    {
                        std::cerr << "\taorg  = " << aorg  << std::endl;
                        const ORDINATE h(0.001f);
                        for(size_t i=1;i<=dims;++i)
                        {
                            atry.ld(aorg);
                            atry[i] = aorg[i] + h;
                            const ORDINATE Dp = S.computeD2(F,atry);
                            atry[i] = aorg[i] - h;
                            const ORDINATE Dm = S.computeD2(F,atry);
                            const ORDINATE dd = (Dm-Dp)/(h+h);
                            std::cerr << "descent[" << i << "]=" << dd << std::endl;
                        }
                        //return false;
                    }


                    //----------------------------------------------------------
                    //
                COMPUTE_STEP:
                    //
                    //----------------------------------------------------------
                    if(!getStep(sigma))
                    {
                        Y_XMLog(xml, "singular step");
                        return false;
                    }


                    //----------------------------------------------------------
                    //
                    // build ini/end variables
                    //
                    //----------------------------------------------------------
                    setScan(aorg,S);
                    
                    const ORDINATE D2_end = S.computeD2(F,aend);
                    Y_XMLog(xml,"D2_end = " << D2_end);
                    S.display(xml,aend,"_end");


                    Phi<ABSCISSA,ORDINATE> phi(S,F,aini,aend,atry);
                    phi.save( S.name + "-phi.dat" );

                    if(D2_end>D2_ini)
                    {
                        Y_XMLog(xml,"increasing D2:");
                        if(p>=pmax)
                        {
                            Y_XMLog(xml, "-- stalled --");
                            return false;
                        }
                        lam = lambda[++p];
                        Y_XMLog(xml,"-> " << Y_XML_Attr(p)<<Y_XML_Attr(lam));
                        goto COMPUTE_STEP;
                    }

                    if(false)
                    {
                        const ORDINATE h(0.001f);
                        const ORDINATE phi_0 = phi(zero);
                        const ORDINATE phi_p = phi(h);
                        const ORDINATE d_phi = (phi_p-phi_0)/h;
                        std::cerr << "d_phi=" << d_phi << std::endl;
                        (void)phi(one);
                    }

                    assert(D2_end<=D2_ini);
                    if(true)
                    {
                        xadd = D2_end; xadd += sigma; xadd -= D2_ini;
                        const ORDINATE gamma = xadd.sum();
                        Y_XMLog(xml,"sigma=" << sigma);
                        Y_XMLog(xml,"gamma=" << gamma);
                        std::cerr << "\t\t\t" << D2_ini << " -(" << sigma << ")*x+(" << gamma << ")*x*x" << std::endl;
                    }

                    // update and test convergence
                    aorg.ld(aend);

                    if( AlmostEqual<ORDINATE>::Are(D2_end,D2_ini))
                    {
                        Y_XMLog(xml, "converged!");
                        return true;
                    }

                    // upgrade
                    if(--p<pmin) p=pmin;
                    lam = lambda[p];
                    D2_ini = S.computeD2full(G,aorg,used);

                    // next cycle;
                    //if(cycle>4) return false;
                    goto CYCLE;
                }

                template <typename ABSCISSA, typename FUNC, typename GRAD> inline
                bool run_(XMLog                         & xml,
                          Adjustable<ABSCISSA,ORDINATE> & S,
                          FUNC                          & F,
                          GRAD                          & G,
                          Writable<ORDINATE>            & aorg,
                          const Readable<bool>          & used)
                {
                    FWrapper<FUNC,ABSCISSA,ORDINATE> f(F);
                    GWrapper<GRAD,ABSCISSA,ORDINATE> g(G);
                    return run(xml,S,f,g,aorg,used);
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

