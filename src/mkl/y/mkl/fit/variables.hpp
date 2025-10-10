
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

            class Alias
            {
            public:
                template <typename UID> inline
                Alias(const UID &uid, const Parameter &prm) :
                target(uid),source(prm)
                {
                }

                Alias(const Alias &);
                ~Alias() noexcept;


                const String     target;
                const Parameter &source;

            private:
                Y_Disable_Assign(Alias);
            };

            class Variables : public Ingress<const VariableDB>
            {
            public:
                static const char * const CallSign;
                
                explicit Variables();
                virtual ~Variables() noexcept;

                //! primary
                Variables & operator<<(const Parameter &);

                //! replica
                Variables & operator<<(const Alias &);



            private:
                Y_Disable_Copy_And_Assign(Variables);
                Y_Ingress_Decl();
                VariableDB db;
            };

        }
    }
}

#endif // !Y_Fit_Variables_Included
