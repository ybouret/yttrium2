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
                    /**
                     \param degree degree to create
                     \return *this
                     */
                    Coefficients & operator<<(const size_t degree);

                    //! \return degree from named parameter
                    size_t degreeOf(const Parameter &) const;

                    //__________________________________________________________
                    //
                    //
                    // Members
                    //
                    //__________________________________________________________
                    const String root; //!< base name for coefficients

                private:
                    Y_Disable_Assign(Coefficients); //!< discarding
                    Y_Ingress_Decl();               //!< helper
                    Parameters parameters;          //!< specific parameters
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
                    //__________________________________________________________
                    //
                    //
                    // Definitions
                    //
                    //__________________________________________________________
                    typedef Sample<T,T>                        SampleType; //!< alias
                    typedef typename SampleType::UsualFunction FuncType;   //!< alias
                    typedef typename SampleType::UsualGradient GradType;   //!< alias

                    //__________________________________________________________
                    //
                    //
                    // C++
                    //
                    //__________________________________________________________

                    //! setup \param cf duplicated coefficients
                    inline explicit Session(const Coefficients &cf) :
                    coef(cf),
                    zero(0),
                    aorg( (*coef)->size(), zero),
                    aerr( (*coef)->size(), zero),
                    used( (*coef)->size(), true),
                    xadd(),
                    F( my(), & Session<T>::getF),
                    G( my(), & Session<T>::getG)
                    {
                    }

                    //! cleanup
                    inline virtual ~Session() noexcept {}

                    //__________________________________________________________
                    //
                    //
                    // Methods
                    //
                    //__________________________________________________________

                    //! perform fit session
                    /**
                     \param  xml    for output
                     \param  fit    optimizer
                     \param  sample sample to fit
                     \return fit success
                     */
                    inline bool operator()(XMLog        & xml,
                                           Optimizer<T> & fit,
                                           SampleType   & sample)
                    {
                        setup(sample);
                        return fit(xml,sample,F,G,aorg,used,aerr);
                    }

                    //! intialize sample fit value
                    /**
                     \param sample sample to evaluate
                     \return D2
                     */
                    inline T D2(SampleType &sample) {
                        setup(sample);
                        return sample.computeD2_(F,aorg);
                    }


                    //__________________________________________________________
                    //
                    //
                    // Members
                    //
                    //__________________________________________________________
                    const Coefficients coef; //!< named coefficients
                    const T            zero; //!< scalar value
                    CxxArray<T>        aorg; //!< coefficient values
                    CxxArray<T>        aerr; //!< coefficient errors
                    CxxArray<bool>     used; //!< tunable use


                private:
                    Y_Disable_Copy_And_Assign(Session); //!< discading
                    Cameo::Addition<T> xadd;            //!< inner sums
                    FuncType           F;               //!< usual function
                    GradType           G;               //!< usual gradient

                    Session * my() noexcept { return this; }

                    //! setup variables of sample \param sample target sample
                    inline void setup(SampleType &sample)
                    {
                        sample.vars.free();
                        for(Parameters::ConstIterator it=(*coef)->begin();it != (*coef)->end();++it)
                            sample.vars << **it;
                    }

                    //! usual function
                    /**
                     \param x    abscissa
                     \param vars coeffs
                     \param a    values
                     \return polynomial at x
                     */
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

                    //! usual gradient
                    /**
                     \param dFda gradient to fill
                     \param x    abscissa
                     \param vars coeffs
                     \param a    values
                     \param u    used values
                     \return polynomial at x
                     */
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

