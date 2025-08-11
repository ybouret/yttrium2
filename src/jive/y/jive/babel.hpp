
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
        
        class Babel : public Singleton<Babel,ClassLockPolicy>
        {
        public:
            typedef Lexical::Scanner * (*LexicalLoader)(InputStream&,Lexer &,TagDB&);
            typedef HashMap<uint32_t,LexicalLoader> LexicalDB;

            static const char * const CallSign; //!< "Jive::Babel"
            static const Longevity    LifeTime = LifeTimeOf::JiveBabel;


            virtual void display(std::ostream &,size_t) const;

            Lexer * loadLexer(InputStream &fp);

            LexicalDB lexicalDB;

        private:
            Y_Disable_Copy_And_Assign(Babel);
            friend class Singleton<Babel,ClassLockPolicy>;
            explicit Babel();
            virtual ~Babel() noexcept;

            void lexicalInit();

        };

    }
}

#endif

