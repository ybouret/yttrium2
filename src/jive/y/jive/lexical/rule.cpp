
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
                        Y_Return_Named_Case(Send);
                        Y_Return_Named_Case(Halt);
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

            const char * HumanReadablePpty(const Property ppty)  noexcept
            {
                switch(ppty)
                {
                        Y_Return_Named_Case(SpawnUnit);
                        Y_Return_Named_Case(DropToken);
                        Y_Return_Named_Case(SendToken);
                        Y_Return_Named_Case(BadSyntax);
                }
                return Core::Unknown;
            }

            namespace {

                static inline Demeanor DemeanorFrom(const Property property) noexcept
                {
                    switch(property)
                    {
                        case SpawnUnit: return Emit;
                        case DropToken: return Drop;
                        case SendToken: return Send;
                        case BadSyntax: break;
                    }
                    return Halt;
                }

            }
            Rule:: Rule(const Tag   &   r,
                        const Motif &   m,
                        const Attribute a,
                        const Property  property,
                        const Tag      &noData) noexcept :
            Object(),
            name(r),
            motif(m),
            attr(a),
            data(noData),
            deed(DemeanorFrom(property)),
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

            size_t Rule:: serialize(OutputStream &fp) const
            {
                size_t res = name->serialize(fp);
                res       += motif->serialize(fp);
                { const unsigned _ = attr; res += fp.emitVBR(_); }
                res += data->serialize(fp);
                { const unsigned _ = deed; res += fp.emitVBR(_); }
                return res;
            }




        }

    }

}

#include "y/jive/tagdb.hpp"
#include "y/stream/input.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            Rule:: Rule(const Tag       &n,
                        const Motif     &m,
                        const Attribute  a,
                        const Tag       &x,
                        const Demeanor   d) :
            name(n),
            motif(m),
            attr(a),
            data(x),
            deed(d),
            next(0),
            prev(0)
            {
            }

            Rule * Rule:: Load(InputStream &fp, TagDB &db)
            {
                const Tag      ruleName  = db.read(fp,"rule.name");
                const Motif    ruleMotif = Pattern::ReadFrom(fp);
                const unsigned ruleAttr  = fp.readVBR<unsigned>("rule.attr");

                if(ruleAttr>=NewLine)
                    throw Specific::Exception("Jive::Rule","invalid attribute");

                const Tag      ruleData  = db.read(fp,"rule.data");
                const unsigned ruleDeed  = fp.readVBR<unsigned>("rule.deed");

                if(ruleDeed>=Back)
                    throw Specific::Exception("Jive::Rule","invalid demeanor");

                return new Rule(ruleName,
                                ruleMotif,
                                Attribute(ruleAttr),
                                ruleData,
                                Demeanor(ruleDeed)
                                );
            }

        }

    }

}
