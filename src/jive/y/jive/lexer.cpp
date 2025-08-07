
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


        void Lexer:: onCall(const Token &)
        {
        }

        void Lexer:: onBack(const Token&)
        {
        }


        void Lexer:: store(Lexeme * const lexeme) noexcept
        {
            assert(0!=lexeme);
            lxms.pushHead(lexeme);
        }

        Lexeme * Lexer:: query(Source &source)
        {
            assert(0!=scan);
            if(lxms.size>0) return lxms.popHead();


        QUERY:
            assert(0!=scan);
            {
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
