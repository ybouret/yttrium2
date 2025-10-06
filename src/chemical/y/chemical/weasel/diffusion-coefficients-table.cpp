
#include "diffusion-coefficients-table.hpp"
#include "y/json/compiler.hpp"
#include "y/chemical/db/diffusion-coefficients.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Weasel:: DiffusionCoefficientsTable:: ~DiffusionCoefficientsTable() noexcept
        {
        }

        Weasel:: DiffusionCoefficientsTable:: DiffusionCoefficientsTable() :
        DiffusionCoefficientsDB()
        {
            static const char fn[] = "DiffusionCoefficients";
            JSON::Value    jv;
            {
                JSON::Compiler json;
                Jive::Source   source( Jive::Module::OpenData(fn,DiffusionCoefficients::JSDict,DiffusionCoefficients::Length) );
                json(jv,source);
            }

            if( JSON::IsObject != jv.type )
            {
                throw Specific::Exception(fn,"JSDict is not a JSON::Object!!");
            }

            {
                const JSON::Object &obj = jv.as<JSON::Object>();
                for(JSON::Object::ConstIterator it=obj.begin();it!=obj.end();++it)
                {
                    const JSON::Pair & pair = **it;
                    const String &     name = pair.k;
                    if( JSON::IsNumber != pair.v.type )            throw Specific::Exception(fn,"value of '%s' is not a Number", name.c_str());
                    if( !insert(name,pair.v.as<JSON::Number>() ) ) throw Specific::Exception(fn,"couldn't insert '%s' value...", name.c_str());
                }
            }

            std::cerr << *this << std::endl;

        }
    }
}
