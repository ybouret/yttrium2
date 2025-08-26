
#include "y/chemical/weasel.hpp"
#include "y/chemical/weasel/parser.hpp"
#include "y/chemical/weasel/formula/translator.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        const char * const Weasel::CallSign = "Weasel";

        const char * const Weasel::Coef     = "Coef";
        const char * const Weasel::RegExp   = "RegExp";
        const char * const Weasel::StringID = "String";


        namespace
        {
            class WeaselCode : public Weasel::Parser
            {
            public:
                inline WeaselCode() :
                Weasel::Parser(),
                translator(*this)
                {

                }

                inline ~WeaselCode()
                {

                }

                Weasel::FormulaTranslator translator;

            private:
                Y_Disable_Copy_And_Assign(WeaselCode);
            };


            static void *       WeaselImpl[ Alignment::WordsFor<WeaselCode>::Count ];
            static WeaselCode * code = 0;
        }

        Weasel:: ~Weasel() noexcept
        {
            assert(0!=code);
            Destruct(code);
            code = 0 ;
            Y_Memory_BZero(WeaselImpl);
        }

        Weasel:: Weasel()
        {
            assert(0==code);
            try {
                code = new ( Y_Memory_BZero(WeaselImpl) ) WeaselCode();
            }
            catch(...) { code = 0; throw; }
        }


        void Weasel:: display(std::ostream &os, size_t indent) const
        {
            init(os,indent);

            quit(os,indent);
        }

        XNode * Weasel:: parse( Jive::Module *m )
        {
            Jive::Source   source(m);
            AutoPtr<XNode> node = code->parse(source);

            return node.yield();
        }

        String  Weasel:: formulaToText(const Formula &f, int * const z)
        {
            return code->translator.decode(f,z,false);
        }

        String  Weasel:: formulaToHTML(const Formula &f)
        {
            return code->translator.decode(f,0,true);
        }

    }
}
