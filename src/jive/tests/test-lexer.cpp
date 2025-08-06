


#include "y/jive/lexer.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;
using namespace Jive;

namespace
{
    class MyLexer : public Lexer
    {
    public:
        explicit MyLexer() : Lexer("MyLexer")
        {
            
        }

        virtual ~MyLexer() noexcept
        {

        }

    private:
        Y_Disable_Copy_And_Assign(MyLexer);
    };
}

Y_UTEST(lexer)
{

    Lexer lexer("MyLexer");

}
Y_UDONE()
