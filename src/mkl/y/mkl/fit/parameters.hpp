
//! \file

#ifndef Y_Fit_Parameters_Included
#define Y_Fit_Parameters_Included 1

#include "y/mkl/fit/parameter.hpp"
#include "y/container/associative/suffix/set.hpp"
//#include "y/type/ingress.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            typedef SuffixSet<String,Parameter::Pointer> ParameterDB;

            class Parameters : public Ingress< const ParameterDB >
            {
            public:
                static const char * const CallSign; //!< "Fit::Parameters"

                explicit Parameters();
                virtual ~Parameters() noexcept;

                template <typename UID> inline
                Parameters & operator<<(const UID &uid)
                {
                    const Parameter::Pointer p = new Parameter(uid,db.size()+1);
                    return grow(p);
                }

            private:
                Y_Disable_Copy_And_Assign(Parameters);
                Y_Ingress_Decl();
                Parameters & grow(const Parameter::Pointer &);
                ParameterDB db;
            };
        }

    }

}

#endif // !Y_Fit_Parameters_Included

