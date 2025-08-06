
#include "y/jive/lexer.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{

    namespace Jive
    {

        LexerBase:: LexerBase() :
        pdb( new Dictionary() ),
        nil()
        {
        }

        LexerBase:: ~LexerBase() noexcept
        {
        }



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
    }

}
