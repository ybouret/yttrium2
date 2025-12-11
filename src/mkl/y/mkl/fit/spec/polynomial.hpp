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

                    virtual ~Coefficients() noexcept;

                    Coefficients & operator<<(const size_t degree);
                    size_t degreeOf(const Parameter &) const;

                    const String root;

                private:
                    Y_Disable_Copy_And_Assign(Coefficients);
                    Y_Ingress_Decl();
                    Parameters parameters;
                };

            };

        };
    }
}

#endif // !Y_Fit_Polynomial_Included

