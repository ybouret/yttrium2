//! \file

#ifndef Y_Fit_Sample_Included
#define Y_Fit_Sample_Included 1

#include "y/mkl/fit/adjustable.hpp"
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
                static const unsigned Dimensions = sizeof(ABSCISSA) / sizeof(ORDINATE); //!< alias
                typedef Keyed<String,ArcPtr<Sample>>       Pointer;                     //!< alias

                typedef Adjustable<ABSCISSA,ORDINATE>      AdjustableType;              //!< alias
                typedef typename AdjustableType::XAddition XAddition;                   //!< alias
                typedef typename AdjustableType::Function  Function;                    //!< alias
                typedef typename AdjustableType::Gradient  Gradient;                    //!< alias
                using AdjustableType::D2;
                using AdjustableType::xadd;
                using AdjustableType::dFda;
                using AdjustableType::beta;
                using AdjustableType::cadd;
                using AdjustableType::alpha;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                /**
                 \param id    name
                 \param theX  input abscissae
                 \param theY  input ordinates
                 \param theYf ouput ordinates
                 */
                template <typename UID> inline
                explicit Sample(const UID                & id,
                                const Readable<ABSCISSA> & theX,
                                const Readable<ORDINATE> & theY,
                                Writable<ORDINATE>       & theYf):
                AdjustableType(id), X(theX), Y(theY), Yf(theYf), vars(), half(0.5)
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


                virtual void scatter(Writable<ORDINATE>       &a_global,
                                     const Readable<ORDINATE> &a_local) const noexcept
                {

                    for(Variables::ConstIterator it=vars->begin();it!=vars->end();++it)
                    {
                        const Variable &v = **it;
                        a_global[v.global.indx] = a_local[v.indx];
                    }


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
                    return (D2=xadd.sum()*half);
                }


                //! helper to store value in xaddition
#define Y_Fit_Sample_Store(VALUE)     do { (*node) << (VALUE);        node=node->next; } while(false)

                //! helper to query value from xaddition
#define Y_Fit_Sample_Query(VNAME)     do { VNAME = node->sum();       node=node->next; } while(false)

                virtual ORDINATE computeD2full(Gradient                 & F,
                                               const Readable<ORDINATE> & aorg,
                                               const Readable<bool>     & used)
                {
                    //----------------------------------------------------------
                    //
                    // initializing
                    //
                    //----------------------------------------------------------
                    const ORDINATE zero(0);
                    const ORDINATE one(1);
                    const size_t   nvar = vars->size();
                    dFda.adjust(nvar,zero);
                    beta.adjust(nvar,zero);
                    cadd.adjust( (nvar*(nvar+3)) >> 1);
                    alpha.make(nvar,nvar);
                    alpha.diagonal(one,zero);




                    //----------------------------------------------------------
                    //
                    // collecting
                    //
                    //----------------------------------------------------------
                    xadd.ldz();
                    cadd.ldz();
                    {
                        const size_t n = X.size();
                        for(size_t i=1;i<=n;++i)
                        {
                            dFda.ld(zero);
                            const ORDINATE delta = Y[i] - (Yf[i] =  F(dFda,X,i,vars,aorg,used));
                            xadd << delta*delta;

                            //--------------------------------------------------
                            // dispatching
                            //--------------------------------------------------
                            {
                                Variables::ConstIterator jter = vars->begin();
                                XAddition               *node = cadd.head;
                                for(size_t j=nvar;j>0;--j,++jter)
                                {
                                    const Variable &var  = **jter; if( !used[var.global.indx] ) continue;
                                    const size_t    J    = var.indx;
                                    const ORDINATE  dF_j = dFda[J];

                                    // accumulate beta[J]
                                    Y_Fit_Sample_Store(delta*dF_j);

                                    // alpha diagonal term alpha[J][J]
                                    Y_Fit_Sample_Store(dF_j * dF_j);

                                    {
                                        Variables::ConstIterator kter = jter;
                                        ++kter; // skip diagonal
                                        for(size_t k=j-1;k>0;--k,++kter)
                                        {
                                            const Variable &sub  = **kter; if( !used[sub.global.indx] ) continue;
                                            Y_Fit_Sample_Store(dF_j * dFda[sub.indx] );
                                        }
                                    }

                                }
                            }
                        }
                    }


                    //----------------------------------------------------------
                    //
                    // reduction
                    //
                    //----------------------------------------------------------
                    {
                        Variables::ConstIterator jter = vars->begin();
                        XAddition               *node = cadd.head;
                        for(size_t j=nvar;j>0;--j,++jter)
                        {
                            const Variable &var = **jter; if( !used[var.global.indx] ) continue;
                            const size_t    J    = var.indx;
                            Y_Fit_Sample_Query(beta[J]);

                            // fetch diagonal
                            Y_Fit_Sample_Query(alpha[J][J]);

                            {
                                Variables::ConstIterator kter = jter;
                                ++kter; // skip diagonal

                                // extra-diagonal
                                for(size_t k=j-1;k>0;--k,++kter)
                                {
                                    const Variable &sub  = **kter; if( !used[sub.global.indx] ) continue;
                                    Y_Fit_Sample_Query(alpha[J][sub.indx]);
                                }
                            }
                        }
                    }
                    this->symmetrize();


                    return (D2=xadd.sum()*half);
                }

                inline virtual
                void display(XMLog &xml, const Readable<ORDINATE> &arr, const char * const sfx) const
                {
                    const size_t w = vars.maxNameSize;
                    for(Variables::ConstIterator iv=vars->begin();iv!=vars->end();++iv)
                        (**iv).display(xml,arr,sfx,w);
                }


                inline virtual
                size_t active(const Readable<bool> &used) const noexcept
                {
                    size_t res = 0;
                    for(Variables::ConstIterator iv=vars->begin();iv!=vars->end();++iv)
                    {
                        if( used[ (**iv).global.indx] ) ++res;
                    }
                    return res;
                }

                virtual void flatten(Matrix<ORDINATE>     &localMatrix,
                                     const Readable<bool> &globalUsed) const noexcept
                {
                    const ORDINATE zero(0);
                    for(Variables::ConstIterator iv=vars->begin();iv!=vars->end();++iv)
                    {
                        const Variable &v = **iv;
                        if( globalUsed[ v.global.indx] ) continue;
                        const size_t i = v.indx;
                        localMatrix[i][i] = zero;
                    }
                }

                //! quick save to file
                /**
                 \param fileName file name
                 \param append optional append flag
                 */
                template <typename FILENAME> inline
                void save(const FILENAME &fileName, const bool append=false) const
                {
                    OutputFile fp(fileName,append);
                    const size_t n = X.size();
                    for(size_t i=1;i<=n;++i)
                    {
                        Emit(fp,X[i]);
                        Emit(fp << ' ', Y[i]);
                        Emit(fp << ' ', Yf[i]);
                        fp << '\n';
                    }
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Readable<ABSCISSA> & X;    //!< input  abscissae
                const Readable<ORDINATE> & Y;    //!< input  ordinates
                Writable<ORDINATE>       & Yf;   //!< output ordinates
                Variables                  vars; //!< fitting variables
                const ORDINATE             half; //!< 0.5

            private:
                Y_Disable_Copy_And_Assign(Sample); //!< discarding

                //! \param fp output \param v ordinate \return fp(v)
                static inline OutputStream & Emit(OutputStream &fp, const ORDINATE v)
                {
                    return fp("%.15g", (double)v );
                }


            };
        }

    }
}


#endif // !Y_Fit_Sample_Included

