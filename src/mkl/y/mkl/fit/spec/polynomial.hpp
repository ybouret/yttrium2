//! \file

#ifndef Y_Fit_Polynomial_Included
#define Y_Fit_Polynomial_Included 1

#include "y/mkl/fit/optimizer.hpp"
#include "y/mkl/fit/sample.hpp"
#include "y/container/cxx/array.hpp"
#include "y/calculus/ipower.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            //__________________________________________________________________
            //
            //
            //! Flexible Polynomial Fit
            //
            //__________________________________________________________________
            struct Polynomial
            {

                //______________________________________________________________
                //
                //
                //
                //! fixed coefficients as "root[0..degree]"
                //
                //
                //______________________________________________________________
                class Coefficients : public Ingress< const Parameters >
                {
                public:
                    //__________________________________________________________
                    //
                    //
                    // C++
                    //
                    //__________________________________________________________

                    //! setup \param name root name for coefficients
                    template <typename NAME> inline
                    explicit Coefficients(const NAME &name) :
                    Ingress<const Parameters>(),
                    root(name), parameters()
                    {
                    }

                    //! duplicate
                    Coefficients(const Coefficients &);

                    //! cleanup
                    virtual ~Coefficients() noexcept;

                    //__________________________________________________________
                    //
                    //
                    // Methods
                    //
                    //__________________________________________________________

                    //! create a new coefficient "root+degree"
                    Coefficients & operator<<(const size_t degree);
                    size_t degreeOf(const Parameter &) const;

                    //__________________________________________________________
                    //
                    //
                    // Members
                    //
                    //__________________________________________________________
                    const String root;

                private:
                    Y_Disable_Assign(Coefficients);
                    Y_Ingress_Decl();
                    Parameters parameters;
                };

                //______________________________________________________________
                //
                //
                //
                //! fit session for a given set of coefficients
                //
                //
                //______________________________________________________________
                template <typename T>
                class Session
                {
                public:
                    typedef Sample<T,T>                        SampleType;
                    typedef typename SampleType::UsualFunction FuncType;
                    typedef typename SampleType::UsualGradient GradType;

                    inline explicit Session(const Coefficients &cf) :
                    coef(cf),
                    zero(0),
                    aorg( (*coef)->size(), zero),
                    aerr( (*coef)->size(), zero),
                    used( (*coef)->size(), true),
                    F( this, & Session<T>::getF),
                    G( this, & Session<T>::getG)
                    {
                    }

                    inline virtual ~Session() noexcept {}

                    inline bool operator()(XMLog        & xml,
                                           Optimizer<T> & fit,
                                           SampleType   & sample)
                    {
                        setup(sample);
                        return fit(xml,sample,F,G,aorg,used,aerr);
                    }

                    inline T D2(SampleType &sample) {
                        setup(sample);
                        return sample.computeD2_(F,aorg);
                    }



                    const Coefficients coef;
                    const T            zero;
                    CxxArray<T>        aorg;
                    CxxArray<T>        aerr;
                    CxxArray<bool>     used;


                private:
                    Y_Disable_Copy_And_Assign(Session);
                    Cameo::Addition<T> xadd;
                    FuncType           F;
                    GradType           G;

                    inline void setup(SampleType &sample)
                    {
                        sample.vars.free();
                        for(Parameters::ConstIterator it=(*coef)->begin();it != (*coef)->end();++it)
                            sample.vars << **it;
                        std::cerr << "vars=" << sample.vars << std::endl;
                    }

                    inline T getF(const T x, const Variables &vars, const Readable<T> &a)
                    {
                        xadd.ldz();
                        for(Variables::ConstIterator it=vars->begin(); it!=vars->end();++it)
                        {
                            const Variable &v = **it;
                            const size_t    d = coef.degreeOf(**it);
                            xadd << ipower(x,d) * a[v.indx];
                        }
                        return xadd.sum();
                    }

                    inline T getG(Writable<T>          &dFda,
                                  const T               x,
                                  const Fit::Variables &vars,
                                  const Readable<T   > &a,
                                  const Readable<bool> &u)
                    {
                        xadd.ldz();
                        for(Variables::ConstIterator it=vars->begin(); it!=vars->end();++it)
                        {
                            const Variable &v = **it;
                            const size_t    d = coef.degreeOf(**it);
                            const size_t    i = v.indx;
                            const T         xd = ipower(x,d);
                            xadd << xd * a[i];
                            if(u[i])
                            {
                                dFda[i] = xd;
                            }
                        }
                        return xadd.sum();
                    }
                };
            };

        };
    }
}

#endif // !Y_Fit_Polynomial_Included

