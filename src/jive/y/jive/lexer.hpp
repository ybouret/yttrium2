//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/jive/lexical/base.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{

    namespace Jive
    {



        class Lexer : public Lexical::Base, public Lexical::Scanner, public Recyclable
        {
        public:
            
            typedef Lexical::Scanner          Scanner;
            typedef Scanner::Pointer          ScanPtr;
            typedef SuffixSet<String,ScanPtr> ScanDB;
            typedef Vector<Scanner *>         History;

            template <typename LID> inline
            explicit Lexer(const LID &lid) :
            Lexical::Base(),
            Scanner(lid,pdb,nil,Lexical::AcceptEOF),
            scan(this),
            lxms(),
            hist(),
            mydb()
            {
                initialize();
            }

            virtual ~Lexer() noexcept;

            virtual void free() noexcept;

            Lexeme * query(Source &);
            void     store(Lexeme * const) noexcept;

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

