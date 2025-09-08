
#include "y/jive/babel.hpp"

#include "y/jive/lexical/comment/single-line.hpp"
#include "y/jive/lexical/comment/multi-lines.hpp"

#include "y/jive/lexical/plugin/jstring.hpp"
#include "y/jive/lexical/plugin/rstring.hpp"
#include "y/jive/lexical/plugin/bstring.hpp"

#include "y/exception.hpp"

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
            Y_Jive_Babel(Lexical::MultiLinesComment);
            Y_Jive_Babel(Lexical::JString);
            Y_Jive_Babel(Lexical::RString);
            Y_Jive_Babel(Lexical::BString);

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

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {
            Scanner * MultiLinesComment:: Load(InputStream &fp, Lexer &lexer, TagDB &db)
            {
                const String cid = FourCC(UUID).c_str();
                const String jid = cid + ".join";
                const String qid = cid + ".quit";
                const Tag    sid = db.read(fp,cid.c_str());
                const Tag    cxp = db.read(fp,jid.c_str());
                const Tag    qxp = db.read(fp,qid.c_str());
                return new MultiLinesComment(sid,cxp,qxp,lexer);
            }
        }

    }

}



namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            Scanner * JString:: Load(InputStream &fp, Lexer &lexer, TagDB &db)
            {
                const Tag sid = db.read(fp,"JString.name");
                return new JString(sid,lexer);
            }

            Scanner * RString:: Load(InputStream &fp, Lexer &lexer, TagDB &db)
            {
                const Tag sid = db.read(fp,"JString.name");
                return new RString(sid,lexer);
            }

            Scanner * BString:: Load(InputStream &fp, Lexer &lexer, TagDB &db)
            {
                const Tag sid = db.read(fp,"JString.name");
                return new BString(sid,lexer);
            }
        }
    }

}

#include "y/stream/input.hpp"
#include <iomanip>

namespace Yttrium
{
    namespace Jive
    {

#define Y_PRINT(MSG) \
do { if(Lexical::Scanner::Verbose) { std::cerr << "<" << CallSign <<  "> " << MSG << std::endl; } } while(false)

        Lexer * Babel:: loadLexer(InputStream &fp)
        {
            TagDB     db;
            const Tag theName = db.read(fp,"name");
            Y_PRINT("loading <" << theName  << ">");
            AutoPtr<Lexer> lexer = new Lexer(theName);

            // reloading extensions
            {
                const size_t nx = fp.readVBR<size_t>(theName->c_str(),"#extensions");
                Y_PRINT("loading <" << theName << "> #extensions="<< nx);
                for(size_t i=1;i<=nx;++i)
                {
                    const uint32_t        xid = fp.readCBR<uint32_t>("extension","uuid");
                    const FourCC          fcc(xid);
                    Y_PRINT(theName << ".extension #" << std::setw(2) << i << " [" << fcc << "]");
                    LexicalLoader * const pfn = lexicalDB.search(xid);
                    if(!pfn)
                        throw Specific::Exception(CallSign,"no registered '%s",fcc.c_str());
                    lexer->record( (*pfn)(fp,*lexer,db) );
                }
            }

            // reloading rules
            {
                const size_t nr = fp.readVBR<size_t>(theName->c_str(),"#rules");
                Y_PRINT("loading <" << theName << "> #rules="<< nr);
                for(size_t i=1;i<=nr;++i)
                    (void) lexer->add( Lexical::Rule::Load(fp,db) );
            }

            Y_PRINT(" loaded <" << theName  << ">");

            return 0;
        }

    }

}


