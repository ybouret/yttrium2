#include "y/mkl/fit/parameters.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Parameters:: ~Parameters() noexcept
            {
            }

            Parameters:: Parameters() : Ingress<const ParameterDB>(), db()
            {
            }

            Y_Ingress_Impl(Parameters,db)


            const char * const Parameters:: CallSign = "Fit::Parameters";

            Parameters & Parameters:: grow(const Parameter::Pointer &p)
            {
                if(!db.insert(p))
                    throw Specific::Exception(CallSign,"multiple parameter '%s'", p->name.c_str());
                return *this;
            }

            const Parameter & Parameters:: operator[](const String &uid) const
            {
                const Parameter::Pointer *pp = db.search(uid);
                if(!pp) throw Specific::Exception(CallSign,"missing parameter '%s'", uid.c_str());
                return **pp;
            }

            const Parameter & Parameters:: operator[](const char * const uid) const
            {
                const String _(uid); return (*this)[_];
            }

            const Parameter & Parameters:: operator[](const char uid) const
            {
                const String _(uid); return (*this)[_];
            }


            void  Parameters:: queryEnv(Writable<bool> &used) const
            {
                for(ConstIterator it=db.begin();it!=db.end();++it)
                {
                    const Parameter &p = **it;
                    p(used) = p.queryEnv();
                }
            }
        }
    }

}
