#include "y/mkl/fit/variables.hpp"
#include "y/exception.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Alias:: ~Alias() noexcept {}

            Alias:: Alias(const Alias & _) : target(_.target), source(_.source) {}


            Variables:: ~Variables() noexcept
            {
            }


            Variables:: Variables() : Ingress<const VariableDB>(), db()
            {
            }

            Y_Ingress_Impl(Variables,db)

            const char * const Variables:: CallSign = "Fit::Variables";

            Variables & Variables:: operator<<(const Parameter &p)
            {
                const Variable::Pointer var = new Variable(p.name,db.size()+1,p);
                if(!db.insert(var))
                    throw Specific::Exception(CallSign,"multiple '%s'",var->name.c_str());
                
                return *this;
            }


            Variables & Variables:: operator<<(const Alias &a)
            {
                const Variable::Pointer var = new Variable(a.target,db.size()+1,a.source);
                if(!db.insert(var))
                    throw Specific::Exception(CallSign,"multiple '%s' (alias '%s')",var->name.c_str(), a.source.name.c_str());
                return *this;
            }


            const Variable & Variables:: get(const String &id)  const
            {
                const Variable::Pointer *ppv = db.search(id);
                if(!ppv)
                    throw Specific::Exception(CallSign,"no variable '%s'", id.c_str());
                return **ppv;
            }

            const Variable & Variables:: get(const char * const id) const
            {
                const String _(id); return get(_);
            }

            const Variable & Variables:: get(const char id) const
            {
                const String _(id); return get(_);
            }

            size_t Variables:: width() const noexcept
            {
                size_t w = 0;
                for(ConstIterator it=db.begin();it!=db.end();++it)
                {
                    InSituMax(w, (**it).global.name.size() );
                }
                return w;
            }

        }

    }

}
