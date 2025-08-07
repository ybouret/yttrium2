
#include "y/jive/lexical/rule.hpp"
#include "y/stream/libc/output.hpp"
namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            const char * Rule:: HumarReadableDeed(const Demeanor deed) noexcept
            {
                switch(deed)
                {
                        Y_Return_Named_Case(Emit);
                        Y_Return_Named_Case(Drop);
                        Y_Return_Named_Case(Call);
                        Y_Return_Named_Case(Back);
                }
                return Core::Unknown;
            }

            const char * Rule:: HumarReadableAttr(const Attribute attr) noexcept
            {
                switch(attr)
                {
                        Y_Return_Named_Case(Regular);
                        Y_Return_Named_Case(NewLine);

                }
                return Core::Unknown;
            }

            Rule:: Rule(const Tag   &   r,
                        const Motif &   m,
                        const Attribute a,
                        const bool      emit,
                        const Tag      &noData) noexcept :
            Object(),
            name(r),
            motif(m),
            attr(a),
            data(noData),
            deed(emit?Emit:Drop),
            next(0),
            prev(0)
            {
                assert(0 == data->length() );
            }

            Rule:: ~Rule() noexcept
            {
            }

            void Rule:: binaryPattern() const
            {
                const String fileName = *name + ".bin";
                OutputFile   fp(fileName);
                (void) motif->serialize(fp);
            }

            void Rule:: renderPattern() const
            {
                const String fileName = *name + ".dot";
                Vizible::Render(fileName,*motif);
            }


            const char * Rule:: humanReadableDeed() const noexcept
            {
                return HumarReadableDeed(deed);
            }


            const char * Rule:: humanReadableAttr() const noexcept
            {
                return HumarReadableAttr(attr);
            }


        }

    }

}
