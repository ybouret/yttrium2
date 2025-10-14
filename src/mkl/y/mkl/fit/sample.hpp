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


                virtual ORDINATE computeD2full(Gradient                 & F,
                                               const Readable<ORDINATE> & aorg,
                                               const Readable<bool>     & used)
                {
                    // initializing
                    const ORDINATE zero(0);
                    const size_t nvar = vars->size();
                    dFda.adjust(nvar,zero);
                    beta.adjust(nvar,zero);
                    cadd.adjust(nvar);

                    // collecting
                    xadd.ldz();
                    cadd.ldz();
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
                            for(size_t j=nvar;j>0;--j,node=node->next,++jter)
                            {
                                const Variable &var = **jter;
                                if( !used[var.global.indx] ) continue;
                                (*node) << delta * var(dFda);
                                
                            }
                        }
                    }

                    // reduction

                    {
                        Variables::ConstIterator iter = vars->begin();
                        XAddition               *node = cadd.head;
                        for(size_t j=nvar;j>0;--j,node=node->next,++iter)
                        {
                            const Variable &var = **iter;
                            if( !used[var.global.indx] ) continue;
                            var(beta) = node->sum();
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

