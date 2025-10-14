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

#define Y_Fit_Adjustable_API

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


#define Y_Fit_Sample_Store(VALUE) do { (*node) << (VALUE); node=node->next; } while(false)
#define Y_Fit_Sample_Query(VNAME)   do { VNAME = node->sum();  node=node->next; } while(false)

                virtual ORDINATE computeD2full(Gradient                 & F,
                                               const Readable<ORDINATE> & aorg,
                                               const Readable<bool>     & used)
                {
                    // initializing
                    const ORDINATE zero(0);
                    const ORDINATE one(1);
                    const size_t nvar = vars->size();
                    dFda.adjust(nvar,zero);
                    beta.adjust(nvar,zero);
                    cadd.adjust( (nvar*(nvar+3)) >> 1);
                    alpha.make(nvar,nvar);
                    alpha.diagonal(one,zero);

                    // collecting
                    xadd.ldz();
                    cadd.ldz();
                    {
                        const size_t n = X.size();
                        for(size_t i=1;i<=n;++i)
                        {
                            dFda.ld(zero);
                            const ORDINATE delta = Y[i] - (Yf[i] =  F(dFda,X,i,vars,aorg,used));
                            xadd << delta*delta;

                            // dispatching
                            {
                                Variables::ConstIterator jter = vars->begin();
                                XAddition               *node = cadd.head;
                                for(size_t j=nvar;j>0;--j,++jter)
                                {
                                    const Variable &var  = **jter; if( !used[var.global.indx] ) continue;
                                    const size_t    J    = var.indx;
                                    const ORDINATE &dF_j = dFda[J];
                                    //(*node) << delta * dF_j; node=node->next;
                                    Y_Fit_Sample_Store(delta*dF_j);

                                    // alpha diagonal term
                                    Y_Fit_Sample_Store(dF_j * dF_j);

                                    {
                                        Variables::ConstIterator kter = jter;
                                        ++kter; // skip diagonal
                                        for(size_t k=j-1;k>0;--k,++kter)
                                        {
                                            const Variable &sub  = **kter; if( !used[sub.global.indx] ) continue;
                                            Y_Fit_Sample_Store(dF_j * sub(dFda) );
                                        }
                                    }

                                }
                            }
                        }
                    }



                    // reduction
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
                                for(size_t k=j-1;k>0;--k,++kter)
                                {
                                    const Variable &sub  = **kter; if( !used[sub.global.indx] ) continue;
                                    Y_Fit_Sample_Query(sub(alpha[J]));
                                }
                            }
                        }
                        for(size_t i=1;i<=nvar;++i)
                        {
                            for(size_t j=1;j<i;++j) alpha[i][j] = alpha[j][i];
                        }
                    }



                    return (D2=xadd.sum());
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
                const Readable<ABSCISSA> & Y;    //!< input  ordinates
                Writable<ABSCISSA>       & Yf;   //!< output ordinates
                Variables                  vars; //!< fitting variables

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

