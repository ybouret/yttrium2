
#include "y/chemical/weasel.hpp"
#include "y/chemical/weasel/parser.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        const char * const Weasel::CallSign = "Weasel";

        const char * const Weasel::Coef     = "COEF";
        const char * const Weasel::RegExp   = "RegExp";
        const char * const Weasel::StringID = "String";


        namespace
        {
            class WeaselCode : public Weasel::Parser
            {
            public:
                inline WeaselCode()
                {

                }

                inline ~WeaselCode()
                {

                }


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
            Jive::Source source(m);
            return code->parse(source);
        }


    }
}
