#include "y/jive/syntax/node/terminal.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/utest/run.hpp"

#include "y/jive/syntax/rule/internal.hpp"
#include "y/jive/syntax/rule/terminal.hpp"


namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            class Synthetic : public Internal
            {
            public:
                static const uint32_t UUID = Y_FOURCC('S', 'N', 'T', 'H');

                explicit Synthetic() :
                Internal("synthetic",UUID)
                {
                }

                virtual ~Synthetic() noexcept
                {
                }

                virtual bool accepts(Y_Jive_XRule_Args) const
                {
                    return false;
                }
                virtual OutputStream & vizDecl(OutputStream &fp)    const { return fp; }
                virtual OutputStream & vizPost(OutputStream &fp)    const { return fp; }

            private:
                Y_Disable_Copy_And_Assign(Synthetic);
            };
        }
    }
}


using namespace Yttrium;
using namespace Jive;

Y_UTEST(xnode)
{
    

    const Syntax::Synthetic synth;
    const Syntax::Terminal  word("word",Syntax::Regular,true);

    const Context ctx("dummy");
    Token         tkn;
    Lexeme       *lex = new Lexeme(word.name,ctx,tkn);

    AutoPtr<XNode> tNode = Syntax::Node::Make(word,lex);
    AutoPtr<XNode> iNode = Syntax::Node::Make(synth);


    AutoPtr<XNode> tCopy = tNode->clone();
    AutoPtr<XNode> iCopy = iNode->clone();


    Y_CHECK( *tCopy == *tNode );
    Y_CHECK( *iCopy == *iNode );

}
Y_UDONE()

