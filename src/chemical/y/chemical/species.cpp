
#include "y/chemical/species.hpp"
#include "y/chemical/weasel.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Species:: ~Species() noexcept
        {
        }

#define Y_Species(FORMULA) \
Indexed(top),     \
Formula(FORMULA), \
z(0),             \
tex( laTeX() )

        Species:: Species(const Formula &f, const size_t top) :
        Y_Species(f)
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
        Y_Species(StringToFormula(id))
        {
            Coerce(name) = text( & Coerce(z) );
        }

        Species:: Species(const char * const id, const size_t top) :
        Y_Species(StringToFormula(id))
        {
            Coerce(name) = text( & Coerce(z) );
        }

        OutputStream & Species:: viz(OutputStream &     fp,
                                     const String &     color,
                                     const char * const style) const
        {
            assert(style);
            nodeName(fp) << "[";
            fp << "label = < " << html() << " >,shape=ellipse,color=" << color << ",fontcolor=" << color << ",style=" << style;
            return Endl(fp << "]");
        }

    }

}
