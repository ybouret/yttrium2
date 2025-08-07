//! \file

#ifndef Y_Jive_Lexer_Included
#define Y_Jive_Lexer_Included 1

#include "y/jive/lexical/comment/single-line.hpp"
#include "y/jive/lexical/comment/multi-lines.hpp"
#include "y/container/associative/suffix/set.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{

    namespace Jive
    {



        //______________________________________________________________________
        //
        //
        //
        //! Lexeme producer from root scanner and extension
        //
        //
        //______________________________________________________________________
        class Lexer : public Lexical::Design, public Lexical::Scanner, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Lexical::Scanner          Scanner; //!< alias
            typedef Scanner::Pointer          ScanPtr; //!< alias
            typedef SuffixSet<String,ScanPtr> ScanDB;  //!< alias
            typedef Vector<Scanner *>         History; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup a new lexer, with common design and accepting EOF scanner
            /**
             \param lid compatible lexer name
             */
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

            //! cleanup
            virtual ~Lexer() noexcept;

            //! new single line comment
            /**
             \param cid comment name
             \param cxp call expression
             */
            template <typename CID, typename CXP> inline
            void comment(const CID &cid, const CXP &cxp)
            {
                enroll( new Lexical::SingleLineComment(cid,cxp,*this) );
            }


            //! new multi line comment
            /**
             \param cid comment name
             \param cxp call expression
             \param bxp back expression
             */
            template <
            typename CID,
            typename CXP,
            typename BXP> inline
            void comment(const CID &cid, const CXP &cxp, const BXP &bxp)
            {
                enroll( new Lexical::MultiLinesComment(cid,cxp,bxp,*this) );
            }


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void free()       noexcept;
            virtual void onCall(const Token &);
            virtual void onBack(const Token &);

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Lexeme * query(Source &);                //!< \return saved/new lexeme from source
            void     store(Lexeme * const) noexcept; //!< store previously ready lexeme

        private:
            Y_Disable_Copy_And_Assign(Lexer);      //!< discarding
            void initialize();                     //!< self registering
            void record(Scanner * const);          //!< record a new scanner
            void enroll(Lexical::Comment * const); //!< enroll a new comment

            Scanner * scan; //!< current scanner
            Lexemes   lxms; //!< lexeme cache
            History   hist; //!< history
            ScanDB    mydb; //!< recorded scanners
        };
    }

}

#endif

