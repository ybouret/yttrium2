
#include "y/jive/lexer.hpp"
#include "y/stream/output.hpp"
#include "y/jive/tagdb.hpp"

namespace Yttrium
{

    namespace Jive
    {
        static const char fn[] = "Lexer::Load";

#define Y_PRINT(MSG) \
do { if(Scanner::Verbose) { std::cerr << "<" << fn <<  "> " << MSG << std::endl; } } while(false)

        Lexer * Lexer:: Load(InputStream &fp)
        {
            TagDB     db;
            const Tag theName = db.read(fp,"name");
            Y_PRINT("loading <" << theName  << ">");
            AutoPtr<Lexer> lexer = new Lexer(theName);

            {
                const size_t nx = fp.readVBR<size_t>(theName->c_str(),"#extensions");
                Y_PRINT("loading #extensions="<< nx);
            }

            return 0;
        }

    }

}


