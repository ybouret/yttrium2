//! \file

#ifndef Y_Fit_Polynomial_Included
#define Y_Fit_Polynomial_Included 1

#include "y/mkl/fit/optimizer.hpp"
#include "y/mkl/fit/sample.hpp"

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
                    root(name)
                    {
                    }

                    virtual ~Coefficients() noexcept;

                    Coefficients & operator<<(const size_t degree);
                    size_t degreeOf(const Parameter &) const;

                    const String root;

                private:
                    Y_Disable_Copy_And_Assign(Coefficients);
                    Y_Ingress_Decl();
                    Parameters parameters;
                };

                template <typename T>
                class Model : public Coefficients
                {
                public:
                    template <typename NAME>
                    explicit Model(const NAME &name) : Coefficients(name)
                    {

                    }

                    inline virtual ~Model() noexcept
                    {

                    }

                    inline void operator()(Optimizer<T> &optim,
                                           Sample<T,T>  &sample)
                    {

                        const Parameters &prms = **this;
                        Variables &       vars = sample.vars;
                        const size_t      nvar = prms->size();
                        //aorg.adjust(n,0);
                    }

                    Vector<T> aorg;
                    Vector<T> aerr;
                    



                private:
                    Y_Disable_Copy_And_Assign(Model);
                };

            };

        };
    }
}

#endif // !Y_Fit_Polynomial_Included

