//! \file

#ifndef Y_Fit_Polynomial_Included
#define Y_Fit_Polynomial_Included 1

#include "y/mkl/fit/optimizer.hpp"
#include "y/mkl/fit/sample.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            struct Polynomial
            {
                class Coefficients : public Ingress< const Parameters >
                {
                public:
                    template <typename NAME> inline
                    explicit Coefficients(const NAME &name) :
                    Ingress<const Parameters>(),
                    root(name), parameters()
                    {
                    }

                    Coefficients(const Coefficients &);
                    virtual ~Coefficients() noexcept;

                    Coefficients & operator<<(const size_t degree);
                    size_t degreeOf(const Parameter &) const;

                    const String root;

                private:
                    Y_Disable_Assign(Coefficients);
                    Y_Ingress_Decl();
                    Parameters parameters;
                };


                template <typename T>
                class Session
                {
                public:
                    inline explicit Session(const Coefficients &cf) :
                    coef(cf),
                    zero(0),
                    aorg( (*coef)->size(), zero),
                    aerr( (*coef)->size(), zero),
                    used( (*coef)->size(), zero)
                    {
                    }

                    inline virtual ~Session() noexcept {}

                    inline void run(Optimizer<T> &fit ,
                                    Sample<T,T>  &sample)
                    {
                        // create primary variables from named parameters
                        Variables &vars = sample.vars;
                        vars.free();
                        for(Parameters::ConstIterator it=(*coef)->begin();it != (*coef)->end();++it)
                        {
                            vars << **it;
                        }
                    }



                    const Coefficients coef;
                    const T            zero;
                    CxxArray<T>        aorg;
                    CxxArray<T>        aerr;
                    CxxArray<bool>     used;


                private:
                    Y_Disable_Copy_And_Assign(Session);
                };
            };

        };
    }
}

#endif // !Y_Fit_Polynomial_Included

