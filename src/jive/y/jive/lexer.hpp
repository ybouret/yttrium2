//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{

    namespace Jive
    {

        class LexerBase
        {
        public:
            explicit LexerBase();
            virtual ~LexerBase() noexcept;

            Dictionary::Pointer   pdb;
        protected:
            const Lexical::NoData nil;

        private:
            Y_Disable_Copy_And_Assign(LexerBase);
        };

        class Lexer : public LexerBase, public Lexical::Scanner, public Recyclable
        {
        public:
            
            typedef Lexical::Scanner          Scanner;
            typedef Scanner::Pointer          ScanPtr;
            typedef SuffixSet<String,ScanPtr> ScanDB;
            typedef Vector<Scanner *>         History;

            template <typename LID> inline
            explicit Lexer(const LID &lid) :
            LexerBase(),
            Scanner(lid,pdb,nil,Lexical::AcceptEOF),
            scan(this),
            lxms(),
            hist()
            {
                initialize();
            }

            virtual ~Lexer() noexcept;

            virtual void free() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Lexer);
            void initialize();
            
            Scanner * scan;
            Lexemes   lxms;
            History   hist;
            ScanDB    mydb;
        };
    }

}

#endif

