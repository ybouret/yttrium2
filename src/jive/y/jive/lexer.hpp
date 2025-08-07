//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/scanner.hpp"
#include "y/jive/lexical/design.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{

    namespace Jive
    {



        class Lexer : public Lexical::Design, public Lexical::Scanner, public Recyclable
        {
        public:
            
            typedef Lexical::Scanner          Scanner;
            typedef Scanner::Pointer          ScanPtr;
            typedef SuffixSet<String,ScanPtr> ScanDB;
            typedef Vector<Scanner *>         History;

            template <typename LID> inline
            explicit Lexer(const LID &lid) :
            Lexical::Design(),
            Scanner(lid,*this,Lexical::AcceptEOF),
            scan(this),
            lxms(),
            hist(),
            mydb()
            {
                initialize();
            }

            virtual ~Lexer() noexcept;

#if 0
            template <typename SCANNER>
            SCANNER & operator()(SCANNER * const addr)
            {
                const Scanner::Pointer p = addr;
                record(p);
                return *addr;
            }
#endif
            




            virtual void free() noexcept;
            virtual void onCall(const Token &);
            virtual void onBack(const Token &);

            Lexeme * query(Source &);
            void     store(Lexeme * const) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Lexer);
            void initialize();
            void record(const Scanner::Pointer &);

            Scanner * scan;
            Lexemes   lxms;
            History   hist;
            ScanDB    mydb;
        };
    }

}

#endif

