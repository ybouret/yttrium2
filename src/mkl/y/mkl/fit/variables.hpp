
//! \file

#ifndef Y_Fit_Variables_Included
#define Y_Fit_Variables_Included 1

#include "y/mkl/fit/variable.hpp"
#include "y/mkl/fit/parameters.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            typedef SuffixSet<String,Variable::Pointer> VariableDB;

            class Variables : public Ingress<const VariableDB>
            {
            public:
                explicit Variables();
                virtual ~Variables() noexcept;
                



            private:
                Y_Disable_Copy_And_Assign(Variables);
                Y_Ingress_Decl();
                VariableDB db;
            };

        }
    }
}

#endif // !Y_Fit_Variables_Included
