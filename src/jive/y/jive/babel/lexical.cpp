
#include "y/jive/babel.hpp"

#include "y/jive/lexical/comment/single-line.hpp"
#include "y/jive/lexical/comment/multi-lines.hpp"

#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {

#define Y_Jive_Babel(CLASS) \
/**/    do { \
/**/        if( !lexicalDB.insert(CLASS::UUID,CLASS::Load) )\
/**/            throw Specific::Exception(CallSign,"failed to insert '%s'", #CLASS);\
/**/    } while(false)

        void Babel:: lexicalInit()
        {
            Y_Jive_Babel(Lexical::SingleLineComment);
        }
    }
}

#include "y/jive/tagdb.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Scanner * SingleLineComment:: Load(InputStream &fp, Lexer &lexer, TagDB &db)
            {
                const String cid = FourCC(UUID).c_str();
                const String jid = cid + ".join";
                const Tag    sid = db.read(fp,cid.c_str());
                const Tag    cxp = db.read(fp,jid.c_str());
                return new SingleLineComment(sid,cxp,lexer);
            }
        }

    }

}

#include "y/stream/input.hpp"
namespace Yttrium
{
    namespace Jive
    {

#define Y_PRINT(MSG) \
do { if(Lexical::Scanner::Verbose) { std::cerr << "<" << CallSign <<  "> " << MSG << std::endl; } } while(false)

        Lexer * Babel:: LoadLexer(InputStream &fp)
        {
            TagDB     db;
            const Tag theName = db.read(fp,"name");
            Y_PRINT("loading <" << theName  << ">");
            AutoPtr<Lexer> lexer = new Lexer(theName);

            {
                const size_t nx = fp.readVBR<size_t>(theName->c_str(),"#extensions");
                Y_PRINT("loading #extensions="<< nx);
                for(size_t i=1;i<=nx;++i)
                {
                    const uint32_t xid = fp.loadCBR<uint32_t>("extension","uuid");
                    Y_PRINT("extension #" << i << " [" << FourCC(xid) << "]");
                }
            }

            return 0;
        }

    }

}


