#include "y/mkl/fit/parameters.hpp"
#include "y/exception.hpp"

#include "y/string/tokenizer.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/algorithm/crop.hpp"
#include <cctype>


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Parameters:: ~Parameters() noexcept
            {
            }

            Parameters:: Parameters() :
            Ingress<const ParameterDB>(),
            Assembly(),
            db()
            {
            }

            Parameters:: Parameters(const Parameters &p) :
            Ingress<const ParameterDB>(),
            Assembly(p),
            db(p.db)
            {
            }
            

            Parameters:: Parameters(const String &plist) : Ingress<const ParameterDB>(), db()
            {
                setup(plist);
            }

            Parameters:: Parameters(const char * const plist) : Ingress<const ParameterDB>(), db()
            {
                const String _(plist);
                setup(_);
            }


            Y_Ingress_Impl(Parameters,db)


            const char * const Parameters:: CallSign = "Fit::Parameters";

            Parameters & Parameters:: grow(const Parameter::Pointer &p)
            {
                if(!db.insert(p))
                    throw Specific::Exception(CallSign,"multiple parameter '%s'", p->name.c_str());
                admit(*p);
                return *this;
            }

            void Parameters:: setup(const String &plist)
            {
                Vector<String>      uid;
                Tokenizer::AppendTo(uid,plist,' ');
                for(size_t i=1;i<=uid.size();++i)
                    (*this) <<Algo::Crop(uid[i],isspace);
                
            }


            const Parameter & Parameters:: operator[](const String &uid) const
            {
                const Parameter::Pointer *pp = db.search(uid);
                if(!pp) throw Specific::Exception(CallSign,"missing parameter '%s'", uid.c_str());
                assert((*pp)->quantity()>=1);
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
                    used[p.indx] = p.queryEnv();
                }
            }

            
        }
    }

}
