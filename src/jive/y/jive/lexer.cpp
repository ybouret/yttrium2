
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

        void Lexer:: free() noexcept
        {
            scan = this;
            hist.free();
            lxms.release();
        }


        void Lexer:: store(Lexeme * const lexeme) noexcept
        {
            assert(0!=lexeme);
            lxms.pushHead(lexeme);
        }

        Lexeme * Lexer:: query(Source &source)
        {
            if(lxms.size>0) return lxms.popHead();

            {
                Lexeme *      unit = 0;
                const String *ctrl = 0;
                switch(scan->run(source,unit,ctrl))
                {
                    case Lexical::FoundEOF: assert(Lexical::AcceptEOF == scan->policy); return 0;    // done
                    case Lexical::EmitUnit: assert(0==ctrl); assert(0!=unit);           return unit; // emit
                    default:
                        throw Specific::Exception(name->c_str(), "Not Implemented");
                }
            }
        }


    }

}
