
//! \file

#ifndef Y_Jive_Babel_Included
#define Y_Jive_Babel_Included 1


#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/jive/lexer.hpp"
#include "y/container/associative/hash/map.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! helper to load Jive components
        //
        //
        //______________________________________________________________________
        class Babel : public Singleton<Babel,ClassLockPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Lexical::Scanner * (*LexicalLoader)(InputStream&,Lexer &,TagDB&); //!< alias
            typedef HashMap<uint32_t,LexicalLoader> LexicalDB;                         //!< alias
            static const char * const CallSign;                                        //!< "Jive::Babel"
            static const Longevity    LifeTime = LifeTimeOf::JiveBabel;                //!< life time

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void display(std::ostream &,size_t) const;

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________
            Lexer * loadLexer(InputStream &); //!< \return new lexer from serialized

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            LexicalDB lexicalDB; //!< known uuid+loaded for scanners

        private:
            Y_Disable_Copy_And_Assign(Babel);   //!< discarding
            friend class Singleton<Babel,ClassLockPolicy>;
            explicit Babel();           //!< setup
            virtual ~Babel() noexcept;  //!< cleanup

            void lexicalInit(); //!< initialize built-in scanners

        };

    }
}

#endif

