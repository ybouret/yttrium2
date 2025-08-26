
#include "y/chemical/species.hpp"
#include "y/chemical/weasel.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Species:: ~Species() noexcept
        {
        }

        Species:: Species(const Formula &f, const size_t top) :
        Formula(f),
        Indexed(top),
        z(0)
        {
            Coerce(name) = text( & Coerce(z) );
        }

        namespace
        {
            static inline
            XNode * StringToFormula(const String &id)
            {
                static Weasel &weasel = Weasel::Instance();
                return weasel.formula1( Jive::Module::OpenData(id,id) );
            }

            static inline
            XNode * StringToFormula(const char * const id)
            {
                const String _(id);
                return StringToFormula(_);
            }


        }

        Species:: Species(const String &id, const size_t top) :
        Formula(StringToFormula(id)),
        Indexed(top),
        z(0)
        {
            Coerce(name) = text( & Coerce(z) );
        }

        Species:: Species(const char * const id, const size_t top) :
        Formula(StringToFormula(id)),
        Indexed(top),
        z(0)
        {
            Coerce(name) = text( & Coerce(z) );
        }

        

    }

}
