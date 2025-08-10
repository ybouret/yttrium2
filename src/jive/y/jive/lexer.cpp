
#include "y/jive/lexer.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{

    namespace Jive
    {
        
        Lexer:: ~Lexer() noexcept
        {
            mydb.release();
            (void) liberate();
        }

        void Lexer:: initialize()
        {
            withhold();
            const ScanPtr self = this;
            try
            {
                if(!mydb.insert(self)) throw Specific::Exception( name->c_str(), "unexpected self registration failure");
            }
            catch(...)
            {
                (void) liberate();
                throw;
            }
        }

        void Lexer:: record(Scanner * const newScanner)
        {
            assert(0!=newScanner);
            const ScanPtr p = newScanner;
            if(!mydb.insert(p)) throw Specific::Exception( name->c_str(), "multiple '%s'", p->name->c_str());
        }

        void Lexer:: enroll(Lexical::Extension * const comment)
        {
            record(comment);
            try { call(comment->name,*comment->join); }
            catch(...) { mydb.remove(*comment->name); }
        }



        void Lexer:: free() noexcept
        {
            scan = this;
            hist.free();
            lxms.release();
        }


        void Lexer:: onCall(Token &token)
        {
            forbidden("Lexer::onCall",token);
        }

        void Lexer:: onBack(Token &token)
        {
            forbidden("Lexer::onBack",token);
        }

        void Lexer:: onSent(Token &token)
        {
            forbidden("Lexer::onSent",token);
        }

        void Lexer:: store(Lexeme * const lexeme) noexcept
        {
            assert(0!=lexeme);
            lxms.pushHead(lexeme);
        }

#define Y_PRINT(MSG) \
do { if(Scanner::Verbose) { std::cerr << "<" << scan->name <<  "> " << MSG << std::endl; } } while(false)


        Lexeme * Lexer:: query(Source &source)
        {
            assert(0!=scan);


        QUERY:
            //Y_PRINT("query");
            assert(0!=scan);
            {
                if(lxms.size>0) return lxms.popHead();
                AutoPtr<Lexeme> unit;
                const String *  ctrl = 0;
                switch(scan->run(source,unit,ctrl))
                {
                    case Lexical::FoundEOF:
                        assert(Lexical::AcceptEOF == scan->policy);
                        return 0;            // done

                    case Lexical::EmitUnit:
                        assert(0==ctrl);
                        assert(unit.isValid());
                        return unit.yield(); // emit

                    case Lexical::CtrlBack:
                        // onBack(...) was carried out during run()
                        assert(0==ctrl);
                        assert(unit.isEmpty());
                        if(hist.size()<=0) throw Specific::Exception(name->c_str(),"no previous call for '%s'", scan->name->c_str());
                        scan = hist.pullTail();
                        goto QUERY;

                    case Lexical::CtrlCall: {
                        assert(0!=ctrl);
                        assert(unit.isValid());
                        {
                            ScanPtr * const ppScan = mydb.search(*ctrl);
                            if(!ppScan) throw Specific::Exception(name->c_str(), "no '%s' to call from '%s'", ctrl->c_str(),scan->name->c_str());
                            hist << scan;
                            scan = & **ppScan;
                        }
                        scan->onCall(*unit);
                    } goto QUERY;
                }

                throw Specific::Exception(name->c_str(),"*** corrupted query");
            }


        }


    }

}


#include "y/stream/output.hpp"

namespace Yttrium
{

    namespace Jive
    {
        size_t Lexer:: serialize(OutputStream &fp) const noexcept
        {

            size_t res = name->serialize(fp);

            // save extensions
            {
                assert(mydb.size()>0);
                const size_t nx = mydb.size()-1;
                res += fp.emitVBR(nx);
                for(ScanDB::ConstIterator it=mydb.begin();it!=mydb.end();++it)
                {
                    const Scanner &sub = **it;
                    const uint32_t uid = sub.uuid;
                    if(UUID==uid) { assert(&sub == this); continue; }
                    res += sub.serialize(fp);
                }
            }

            // save specific rules
            {
                const Scanner &self = *this;
                res += fp.emitVBR(self->size);
                for(const Lexical::Rule *r=self->head;r;r=r->next)
                {
                    res += r->serialize(fp);
                }
            }

            return res;
        }
    }
}

