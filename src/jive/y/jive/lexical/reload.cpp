
#include "y/jive/babel.hpp"

namespace Yttrium
{

    namespace Jive
    {


        Lexer * Lexer:: Load(InputStream &fp)
        {
            static Babel & babel = Babel::Instance();
            return babel.loadLexer(fp);
        }

    }

}


